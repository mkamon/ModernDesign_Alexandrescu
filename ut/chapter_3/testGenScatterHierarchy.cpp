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

TEST(ScatterHierarchyTest, scatterHierarchyGenerationTest)
{
    //given
    using TestTypes = TYPELIST_3(int, std::string, widgets::ConcreteWidget);
    //when
    using ScatteredHolder = GenScatterHierarchy<TestTypes, ScatterTest::Holder>;
    ScatteredHolder bigHolder;
    //then 
    ASSERT_TRUE(static_cast<ScatterTest::Holder<std::string>&>(bigHolder).value.empty());
    ASSERT_EQ(widgets::defaultWidgetXValue, static_cast<ScatterTest::Holder<widgets::ConcreteWidget>&>(bigHolder).value.getX());
}

TEST(ScatterHierarchyTest, accesingScatteredHierarchyByFieldType)
{
    //given
    using TestTypes = TYPELIST_3(int, std::string, widgets::ConcreteWidget);
    //when
    using ScatteredHolder = GenScatterHierarchy<TestTypes, ScatterTest::Holder>;
    ScatteredHolder bigHolder;
    auto &stringValue = Field<std::string>(bigHolder).value; 
    auto &widgetValue = Field<widgets::ConcreteWidget>(bigHolder).value;
    //then 
    ASSERT_TRUE(stringValue.empty());
    ASSERT_EQ(widgets::defaultWidgetXValue, widgetValue.getX());
}

TEST(ScatterHierarchyTest, accessingScatteredHierarcyByIndex)
{
    //given
    using TestTypes = TYPELIST_3(int, std::string, widgets::ConcreteWidget);
    constexpr int stringIndex = 1;
    constexpr int widgetIndex = 2;
    //when
    using ScatteredHolder = GenScatterHierarchy<TestTypes, ScatterTest::Holder>;
    ScatteredHolder bigHolder;
    auto &stringValue = Field<stringIndex>(bigHolder).value; 
    auto &widgetValue = Field<widgetIndex>(bigHolder).value;
    //then 
    ASSERT_TRUE(stringValue.empty());
    ASSERT_EQ(widgets::defaultWidgetXValue, widgetValue.getX()); 
}
