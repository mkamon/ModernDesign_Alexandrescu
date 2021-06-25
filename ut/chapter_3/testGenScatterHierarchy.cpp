#include <gtest/gtest.h>

#include "chapter_3/ScatteredHierarchy.hpp"
#include "Widgets/ExampleWidgets.hpp"

namespace ScatterTest
{
    template <typename T>
    struct Holder
    {
        T value;
    };
}

TEST(ScatterHierarchyTest, examleScatterHierarchyGenerationTest)
{
    //given
    using TestTypes = TYPELIST_3(int, std::string, widgets::ConcreteWidget);
    //when
    GenScatterHierarchy<TestTypes, ScatterTest::Holder> bigHolder;
    //then 
    ASSERT_TRUE(static_cast<ScatterTest::Holder<std::string>&>(bigHolder).value.empty() );
    ASSERT_EQ(widgets::defaultWidgetXValue, static_cast<ScatterTest::Holder<widgets::ConcreteWidget>&>(bigHolder).value.getX());
}


