#include <gtest/gtest.h>
#include <iostream>
#include "chapter_5/Functor.hpp"

namespace testing
{

struct TestFunctor
{
    int operator()(int i, double d)
    {
        return i * d;
    }
};

class TestFunctorBaseFunctionality : public Test
{
protected:
    static constexpr auto input1{10};
    static constexpr auto input2{2.5};
    static constexpr auto expected{25};
};

TEST_F(TestFunctorBaseFunctionality, shallCallFunctorWithFunctorsBracketOperator)
{
    //given
    TestFunctor f;
    Functor<int, TYPELIST_2(int, double)> cmd(f);
    //when & then
    ASSERT_EQ(expected, cmd(input1, input2));
}

int testFunction(int i, double d)
{
    return i * d;
}

TEST_F(TestFunctorBaseFunctionality, shallCallFunction)
{
    //given
    Functor<int, TYPELIST_2(int, double)> cmd(&testFunction);
    //when & then
    ASSERT_EQ(expected, cmd(input1, input2));
}

int testFunction(int i)
{
    return i;
}

TEST_F(TestFunctorBaseFunctionality, shallCallFunctionOverload)
{
    //given
    using Fun = int (*)(int);
    Functor<int, TYPELIST_1(int)> cmd(static_cast<Fun>(&testFunction));
    //when & then
    ASSERT_EQ(input1, cmd(input1));
}


}
