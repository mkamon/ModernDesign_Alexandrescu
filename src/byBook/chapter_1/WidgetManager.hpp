#pragma once

#include "CreatorPolicies.hpp"

namespace widgets
{
    template< template<typename> typename CreationPolicy, typename Widget>
    class WidgetManager : public CreationPolicy<Widget>
    {
        void switchPrototype(Widget *newPrototype)
        {
            CreationPolicy<Widget> &myPolicy = *this;
            myPolicy.setPrototype(newPrototype);
        }
    };
}