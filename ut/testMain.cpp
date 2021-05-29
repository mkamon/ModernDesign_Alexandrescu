#include <gtest/gtest.h>
#include "Dummy.hpp"
#include "Widgets/ExampleWidgets.hpp"

TEST(Dummy, dummy)
{
    ASSERT_TRUE(dummy::hello());
}