#include <gtest/gtest.h>
#include "Dummy.hpp"

TEST(Dummy, dummy)
{
    ASSERT_TRUE(dummy::hello());
}