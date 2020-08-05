#include <gtest/gtest.h>
#include "helpers.hpp"
#include <string>
using namespace std;

TEST(HELPERS, console_output_Simple)
{
    string result = exec("echo test");
    ASSERT_EQ("test\n", result);
}

TEST(HELPERS, GetDataFromServer_Simple)
{
    std::string rawData = "+IPD,12,192.168.0.154,4567:Test";
    std::string data;
    GetDataFromServer(rawData, data);
    ASSERT_EQ("Test", data);
}

TEST(HELPERS, GetDataFromServer_Empty)
{
    std::string rawData = "";
    std::string data;
    GetDataFromServer(rawData, data);
    ASSERT_EQ("", data);
}