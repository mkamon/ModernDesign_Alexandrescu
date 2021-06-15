#include <gtest/gtest.h>

#include "chapter_2/CTAssert.hpp"
#include <limits>

TEST(CompileTimeAssert, SafeReinterpretCompilationTest)
{
    //given
    using From = unsigned;
    using To = unsigned char;
    auto num = std::numeric_limits<From>::max();
    //when
    auto p = ctassert::safe_reinterpret_cast<To *>(&num);
    //then
    for(From i=0; i<sizeof(num)/sizeof(To); i++){
        ASSERT_EQ(*(p+i), std::numeric_limits<To>::max());
    }
}
//
//TEST(CompileTimeAssert, SafeReinterpretShouldNotCompileTest)
//{
//    //given
//    using From = unsigned;
//    using To = unsigned char;
//    From num = std::numeric_limits<From>::max();
//    //when
//    To p = ctassert::safe_reinterpret_cast<To>(num);
//    //then
//    FAIL() << "Compilation should not succeed";
//}
//

TEST(CompileTimeAssert, SafeReinterpretWithMessageCompilationTest)
{
    //given
    using From = unsigned;
    using To = unsigned char;
    auto num = std::numeric_limits<From>::max();
    //when
    auto p = ctassert::safe_reinterpret_cast_with_msg<To *>(&num);
    //then
    for(From i=0; i<sizeof(num)/sizeof(To); i++){
        ASSERT_EQ(*(p+i), std::numeric_limits<To>::max());
    }
}

// TEST(CompileTimeAssert, SafeReinterpretWithMessageShouldNotCompileTest)
// {
//    //given
//    using From = unsigned;
//    using To = unsigned char;
//    From num = std::numeric_limits<From>::max();
//    //when
//    To p = ctassert::safe_reinterpret_cast_with_msg<To>(num);
//    //then
//    FAIL() << "Compilation should not succeed";
// }
