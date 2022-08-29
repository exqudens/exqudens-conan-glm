cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/name-version.txt" INFO)
string(REPLACE ":" ";" INFO_LIST "${INFO}")
list(GET INFO_LIST 0 RAW_NAME)
list(GET INFO_LIST 1 RAW_VERSION)
string(STRIP "${RAW_NAME}" NAME)
string(STRIP "${RAW_VERSION}" VERSION)
project("${NAME}" VERSION "${VERSION}" LANGUAGES "NONE")

message("project: '${PROJECT_NAME}-${PROJECT_VERSION}'")

cmake_path(CONVERT "$ENV{HOME}" TO_CMAKE_PATH_LIST HOME NORMALIZE)
if(NOT EXISTS "${HOME}" OR NOT IS_DIRECTORY "${HOME}")
    message(FATAL_ERROR "HOME: '${HOME}' not exists or not directory.")
endif()
set(CMAKE_HOME "${HOME}/.cmake")
if(NOT EXISTS "${CMAKE_HOME}")
    file(MAKE_DIRECTORY "${CMAKE_HOME}")
endif()
if(NOT EXISTS "${CMAKE_HOME}" OR NOT IS_DIRECTORY "${CMAKE_HOME}")
    message(FATAL_ERROR "CMAKE_HOME: '${CMAKE_HOME}' not exists or not directory.")
endif()
set(CMAKE_DOWNLOADS "${CMAKE_HOME}/downloads")
if(NOT EXISTS "${CMAKE_DOWNLOADS}")
    file(MAKE_DIRECTORY "${CMAKE_DOWNLOADS}")
endif()
if(NOT EXISTS "${CMAKE_DOWNLOADS}" OR NOT IS_DIRECTORY "${CMAKE_DOWNLOADS}")
    message(FATAL_ERROR "CMAKE_DOWNLOADS: '${CMAKE_DOWNLOADS}' is not directory.")
endif()
if(NOT EXISTS "${CMAKE_DOWNLOADS}/${PROJECT_NAME}-${PROJECT_VERSION}.zip")
    message("download ...")
    file(DOWNLOAD
        #"https://github.com/g-truc/${PROJECT_NAME}/releases/download/${PROJECT_VERSION}/${PROJECT_NAME}-${PROJECT_VERSION}.zip"
        "https://github.com/g-truc/${PROJECT_NAME}/archive/refs/tags/${PROJECT_VERSION}.zip"
        "${CMAKE_DOWNLOADS}/${PROJECT_NAME}-${PROJECT_VERSION}.zip"
        EXPECTED_MD5 "a421a37d1896ab74765c3f94431ca0f6"
    )
    message("... done")
endif()
if(NOT EXISTS "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-${PROJECT_VERSION}.zip")
    message("copy from downloads ...")
    file(COPY "${CMAKE_DOWNLOADS}/${PROJECT_NAME}-${PROJECT_VERSION}.zip" DESTINATION "${PROJECT_BINARY_DIR}")
    message("... done")
endif()
if(NOT EXISTS "${PROJECT_BINARY_DIR}/VulkanSDK-${PROJECT_VERSION}")
    file(ARCHIVE_EXTRACT INPUT "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-${PROJECT_VERSION}.zip")
endif()
if(NOT EXISTS "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-${PROJECT_VERSION}/conanfile.py")
    message("copy 'conanfile.py' ...")
    file(COPY "${PROJECT_SOURCE_DIR}/conanfile.py" DESTINATION "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-${PROJECT_VERSION}")
    message("... done")
endif()
if(NOT EXISTS "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-${PROJECT_VERSION}/name-version.txt")
    message("copy 'name-version.txt' ...")
    file(COPY "${PROJECT_SOURCE_DIR}/name-version.txt" DESTINATION "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-${PROJECT_VERSION}")
    message("... done")
endif()

find_program(CONAN_COMMAND NAMES "conan.exe" "conan" REQUIRED)

execute_process(
    COMMAND "${CONAN_COMMAND}" "search" "${PROJECT_NAME}/${PROJECT_VERSION}"
    OUTPUT_VARIABLE "CONAN_SEARCH_RESULT"
    COMMAND_ECHO "STDOUT"
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ENCODING "UTF-8"
    COMMAND_ERROR_IS_FATAL ANY
)

if("${CONAN_SEARCH_RESULT}" MATCHES "Existing package recipes.+")
    string(REPLACE ":" ";" CONAN_SEARCH_RESULT "${CONAN_SEARCH_RESULT}")
    list(GET CONAN_SEARCH_RESULT 1 CONAN_SEARCH_RESULT)
    string(STRIP ${CONAN_SEARCH_RESULT} CONAN_SEARCH_RESULT)
    message("Existing package recipes: ${CONAN_SEARCH_RESULT}")
    return()
endif()

execute_process(
    COMMAND "${CONAN_COMMAND}"
            export
            "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-${PROJECT_VERSION}/conanfile.py"
            #${CONAN_PACKAGE_USER_CHANNEL}
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
)

execute_process(
        COMMAND "${CONAN_COMMAND}"
        export-pkg
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-${PROJECT_VERSION}/conanfile.py"
        #${CONAN_PACKAGE_USER_CHANNEL}
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
)

execute_process(
    COMMAND "${CMAKE_COMMAND}" -E echo "BUILD_SUCCESSFUL"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
)
