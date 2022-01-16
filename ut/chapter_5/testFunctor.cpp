#include <gtest/gtest.h>
#include <iostream>
#include "chapter_5/Functor.hpp"

struct TestFunctor
{
    int operator()(int i, double d)
    {
        return i * d;
    }
};

TEST(TestFunctorBaseFunctionality, shallSuccessfullyCreateAndExecuteFunctorsBracketOperator)
{
    //given
    TestFunctor f;
    constexpr auto input1{10};
    constexpr auto input2{2.5};
    constexpr auto expected{25};
    Functor<int, TYPELIST_2(int, double)> cmd(f);
    //when & then
    ASSERT_EQ(expected, cmd(input1, input2));
}
