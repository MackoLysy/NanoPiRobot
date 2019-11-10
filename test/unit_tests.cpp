#include <gtest/gtest.h>
#include "helpers.hpp"
#include <string>
using namespace std;

TEST(Helpers_console_output, Simple)
{
    string result = exec("echo test");
    ASSERT_EQ("test\n", result);
}