# exqudens-conan-glm

## cmake-variables

01. `-DCMAKE_UTIL_ONLY=1` to download `util.cmake` file only.

## how-to-create-github-conan-package

01. `cmake -DCMAKE_UTIL_ONLY=1 --preset windows.ninja.msvc-x64-x64.interface`
01. `cmake -P build/dependencies/direct_deploy/exqudens-cmake/cmake/util.cmake -- conan_export_pkg_zip ZIP_FILE_URL https://github.com/g-truc/glm/archive/refs/tags/1.0.3.zip EXPECTED_MD5 62a0d49dc9db445f077e952e34f13ad2 CHECK_FILE readme.md NAME github-glm VERSION 1.0.3 USER exqudens CHANNEL development CHECK_FILE glm-1.0.3/readme.md`
01. *(optional)* check `conan list 'github-glm/1.0.3:*'`
01. *(optional)* check ``conan cache path 'github-glm/1.0.3:${conan list-output-packages[0]}'``
01. *(optional)* check ``ls -1a ${conan-cache-path-output}``
01. *(optional)* `conan upload github-glm/1.0.3 --remote gitlab`

## list-presets

01. `git clean -xdf`
01. `cmake --list-presets`

## list-ctests

01. `git clean -xdf`
01. `cmake --preset ${preset}`
01. `cmake --build --preset ${preset} --target cmake-test-list`

## vscode

01. `git clean -xdf`
01. `cmake --preset ${preset}`
01. `cmake --build --preset ${preset} --target vscode`

## clion

01. `git clean -xdf`
01. `cmake --preset ${preset}`
01. `cmake --build --preset ${preset} --target clion`

## build-all-presets

01. `git clean -xdf`
01. `cmake --list-presets | cut -d ':' -f2 | xargs -I '{}' echo '{}' | xargs -I '{}' bash -c "cmake --preset {} || exit 255"`
01. `cmake --list-presets | cut -d ':' -f2 | xargs -I '{}' echo '{}' | xargs -I '{}' bash -c "cmake --build --preset {} || exit 255"`

## build-test-all-presets

01. `git clean -xdf`
01. `cmake --list-presets | cut -d ':' -f2 | xargs -I '{}' echo '{}' | xargs -I '{}' bash -c "cmake --preset {} || exit 255"`
01. `cmake --list-presets | cut -d ':' -f2 | xargs -I '{}' echo '{}' | xargs -I '{}' bash -c "cmake --build --preset {} --target test-app || exit 255"`

## test-all-presets

01. `git clean -xdf`
01. `cmake --list-presets | cut -d ':' -f2 | xargs -I '{}' echo '{}' | xargs -I '{}' bash -c "cmake --preset {} || exit 255"`
01. `cmake --list-presets | cut -d ':' -f2 | xargs -I '{}' echo '{}' | xargs -I '{}' bash -c "cmake --build --preset {} --target cmake-test || exit 255"`

## install-all-presets

01. `git clean -xdf`
01. `cmake --list-presets | cut -d ':' -f2 | xargs -I '{}' echo '{}' | xargs -I '{}' bash -c "cmake --preset {} || exit 255"`
01. `cmake --list-presets | cut -d ':' -f2 | xargs -I '{}' echo '{}' | xargs -I '{}' bash -c "cmake --build --preset {} --target cmake-install || exit 255"`

## export-all-presets

01. `git clean -xdf`
01. `conan list "glm/*"`
01. `conan remove -c "glm"`
01. `cmake --list-presets | cut -d ':' -f2 | xargs -I '{}' echo '{}' | xargs -I '{}' bash -c "cmake --preset {} || exit 255"`
01. `cmake --list-presets | cut -d ':' -f2 | xargs -I '{}' echo '{}' | xargs -I '{}' bash -c "cmake --build --preset {} --target conan-export || exit 255"`
