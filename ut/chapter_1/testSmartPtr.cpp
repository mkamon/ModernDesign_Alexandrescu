#include <gtest/gtest.h>

#include "chapter_1/CreatorPolicies.hpp"
#include "chapter_1/CheckingPolicies.hpp"
#include "chapter_1/ThreadingModelPolicies.hpp"
#include "chapter_1/SmartPtr.hpp"
#include "Widgets/ExampleWidgets.hpp"


TEST(SmartPointerTest, testSingleThreadNoCheckingPolicesUninitialized)
{
    //given
    using SmartPtrWithSingleThreadNoChecking = widgets::SmartPtr<widgets::ConcreteWidget, policy::NoChecking, policy::SingleThreadModel, policy::OpNewCreator>;
    SmartPtrWithSingleThreadNoChecking smartPtr;
    //when
    auto pointer = smartPtr.operator->();
    //then
    ASSERT_EQ(pointer, nullptr);
}

TEST(SmartPointerTest, testSingleThreadNoCheckingPolicesInitialized)
{
    //given
    using SmartPtrWithSingleThreadNoChecking = widgets::SmartPtr<widgets::ConcreteWidget, policy::NoChecking, policy::SingleThreadModel, policy::OpNewCreator>;
    SmartPtrWithSingleThreadNoChecking smartPtr;
    //when
    smartPtr.createPointer();
    auto pointer = smartPtr.operator->();
    //then
    ASSERT_NE(pointer, nullptr);
}

TEST(SmartPointerTest, testMultiThreadNoCheckingPolicesUninitialized)
{
    //given
    using SmartPtrWithSingleThreadNoChecking = widgets::SmartPtr<widgets::ConcreteWidget, policy::NoChecking, policy::MultiThreadModel, policy::OpNewCreator>;
    SmartPtrWithSingleThreadNoChecking smartPtr;
    //when
    auto pointer = smartPtr.operator->();
    //then
    ASSERT_EQ(pointer, nullptr);
}

TEST(SmartPointerTest, testMultiThreadNoCheckingPolicesInitialized)
{
    //given
    using SmartPtrWithSingleThreadNoChecking = widgets::SmartPtr<widgets::ConcreteWidget, policy::NoChecking, policy::MultiThreadModel, policy::OpNewCreator>;
    SmartPtrWithSingleThreadNoChecking smartPtr;
    //when
    smartPtr.createPointer();
    auto pointer = smartPtr.operator->();
    //then
    ASSERT_NE(pointer, nullptr);
}

TEST(SmartPointerTest, testSingleThreadEnforceNotNullUninitialized)
{
    //given
    using SmartPtrWithSingleThreadNoChecking = widgets::SmartPtr<widgets::ConcreteWidget, policy::EnforceNotNull, policy::SingleThreadModel, policy::OpNewCreator>;
    SmartPtrWithSingleThreadNoChecking smartPtr;
    widgets::ConcreteWidget *pointer = nullptr;
    //when
    try {
        pointer = smartPtr.operator->();
        FAIL() << "SmartPtr.operator->() should throw an error\n";
    } catch (policy::EnforceNotNull<widgets::ConcreteWidget>::NullPointerException& exception) {}
    //then
    ASSERT_EQ(pointer, nullptr);
}

TEST(SmartPointerTest, testSingleThreadEnforceNotNullInitialized)
{
    //given
    using SmartPtrWithSingleThreadNoChecking = widgets::SmartPtr<widgets::ConcreteWidget, policy::EnforceNotNull, policy::SingleThreadModel, policy::OpNewCreator>;
    SmartPtrWithSingleThreadNoChecking smartPtr;
    //when
    smartPtr.createPointer();
    auto pointer = smartPtr.operator->();
    //then
    ASSERT_NE(pointer, nullptr);
}

TEST(SmartPointerTest, testSingleThreadEnsureNotNullPolicesUninitialized)
{
    //given
    using SmartPtrWithSingleThreadNoChecking = widgets::SmartPtr<widgets::ConcreteWidget, policy::EnsureNotNull, policy::SingleThreadModel, policy::OpNewCreator>;
    SmartPtrWithSingleThreadNoChecking smartPtr;
    //when
    auto pointer = smartPtr.operator->();
    //then
    ASSERT_NE(pointer, nullptr) << "EnsureNotNull policy should enforce that SmartPointer is initialized";
}

TEST(SmartPointerTest, testSingleThreadEnsureNotNullPolicesInitialized)
{
    //given
    using SmartPtrWithSingleThreadNoChecking = widgets::SmartPtr<widgets::ConcreteWidget, policy::EnsureNotNull, policy::SingleThreadModel, policy::OpNewCreator>;
    SmartPtrWithSingleThreadNoChecking smartPtr;
    //when
    smartPtr.createPointer();
    auto pointer = smartPtr.operator->();
    //then
    ASSERT_NE(pointer, nullptr);
}
