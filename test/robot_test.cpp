#include <gtest/gtest.h>

#define protected public
#define private public
#include "robot.hpp"
#undef protected
#undef private


TEST(ROBOT, ParseDataSimple)
{
    ASSERT_EQ(1,1);
}

