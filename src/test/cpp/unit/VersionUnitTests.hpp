#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include <iostream>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <exqudens/Log.hpp>
#include <exqudens/log/api/Logging.hpp>

#include "TestUtils.hpp"
#include "glm/glm.hpp"

class VersionUnitTests: public testing::Test {

    public:

        inline static const char* LOGGER_ID = "VersionUnitTests";

    protected:

        static void log(
            const std::string& file,
            const size_t& line,
            const std::string& function,
            const std::string& id,
            const unsigned short& level,
            const std::string& message
        ) {
            exqudens::log::api::Logging::Writer(file, line, function, id, level) << message;
        }

};

TEST_F(VersionUnitTests, test_GLM_VERSION_MESSAGE_1) {
    try {
        std::string testGroup = testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();
        std::string testCase = testing::UnitTest::GetInstance()->current_test_info()->name();
        EXQUDENS_LOG_INFO(LOGGER_ID) << "bgn";

        std::filesystem::path projectSourceDir = {};
        std::string nameVersionContent = {};
        std::vector<std::string> nameVersionSplit = {};
        std::string expected = {};
        std::string actual = {};

        projectSourceDir = std::filesystem::path(TestUtils::getProjectSourceDir());
        nameVersionContent = TestUtils::readFileString((projectSourceDir / "name-version.txt").generic_string());
        nameVersionSplit = TestUtils::split(nameVersionContent, ":");

        ASSERT_EQ(2, nameVersionSplit.size());

        expected = std::string("GLM: version ") + TestUtils::trim(nameVersionSplit.at(1));
        EXQUDENS_LOG_INFO(LOGGER_ID) << "expected: '" << expected << "'";

        actual = GLM_VERSION_MESSAGE;
        EXQUDENS_LOG_INFO(LOGGER_ID) << "actual: '" << actual << "'";

        ASSERT_EQ(expected, actual);

        EXQUDENS_LOG_INFO(LOGGER_ID) << "end";
    } catch (const std::exception& e) {
        std::string errorMessage = TestUtils::toString(e);
        std::cout << LOGGER_ID << " ERROR: " << errorMessage << std::endl;
        FAIL() << errorMessage;
    }
}
