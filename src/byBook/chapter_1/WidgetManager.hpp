#pragma once

#include "CreatorPolicies.hpp"

namespace widgets
{
    template< template<typename> typename Policy, typename Widget>
    class WidgetManager : public Policy<Widget>
    {

    };
}