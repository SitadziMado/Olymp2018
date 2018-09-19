#pragma once
#include "Wrapper.h"

namespace Parsers
{
    class Float : Wrapper<double>
    {
    public:
        Float() = default;
        Float(double value);
    };
}
