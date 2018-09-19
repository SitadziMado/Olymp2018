#pragma once

#include <cinttypes>

#include "Wrapper.h"

namespace Parsers
{
    class Integer : public Wrapper<int64_t>
    {
    public:
        Integer() = default;
        explicit Integer(int64_t value);
    };
}
