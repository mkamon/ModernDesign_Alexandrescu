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

const char* testFunction2(char a, char b)
{
    static const char buffer[2]{a, b};
    return buffer;
}

TEST(TestFunctor, shallUseLanguageConversion)
{
    //given
    const char a{'a'}, b{'b'};
    const std::string expected{"ab"};
    Functor<std::string, TYPELIST_2(char, char)> cmd(&testFunction2);
    //when & then
    ASSERT_EQ(expected, cmd(a,b));
}

class TestMemberSubject
{
    constexpr static auto timesTenMultiplier{10};
    constexpr static auto timesHoundredMultiplier{100};
public:
    int multiplyByTen(int x)
    {
        return x * timesTenMultiplier;
    }

    int multiplyByHoundred(int x)
    {
        return x * timesHoundredMultiplier;
    }
};

class TestFunctorWithMember : public Test
{
protected:
    static constexpr auto testInput{4};
    static constexpr auto expectedMultipliedByTen{testInput * 10};
    static constexpr auto expectedMultipliedByHoundred{testInput * 100};
};

TEST_F(TestFunctorWithMember, testCallToMultiplyByTen)
{
    //given
    TestMemberSubject testSubject;
    Functor<int, TYPELIST_1(int)> cmd(&testSubject, &TestMemberSubject::multiplyByTen);
    //when & then
    ASSERT_EQ(expectedMultipliedByTen, cmd(testInput));
}

TEST_F(TestFunctorWithMember, testCallToMultiplyByHoundred)
{
    //given
    TestMemberSubject testSubject;
    Functor<int, TYPELIST_1(int)> cmd(&testSubject, &TestMemberSubject::multiplyByHoundred);
    //when & then
    ASSERT_EQ(expectedMultipliedByHoundred, cmd(testInput));
}
}
