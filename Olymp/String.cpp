#include "String.h"

#include <utility>

namespace Parsers
{
    String::String(const std::string& value) :
        Wrapper<std::string>(value)
    {}

    String::String(std::string&& value) :
        Wrapper<std::string>(std::move(value))
    {}
}
