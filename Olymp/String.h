#pragma once

#include <string>

#include "Wrapper.h"

namespace Parsers
{
    class String : Wrapper<std::string>
    {
    public:
        String() = default;
        explicit String(const std::string& value);
        explicit String(std::string&& value);
    };
}
