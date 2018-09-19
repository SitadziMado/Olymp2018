#include "Object.h"

#include <iomanip>
#include <typeinfo>
#include <sstream>
#include <string>

namespace Parsers
{
    Object::Object() :
        id_(alloc<char>('O'))
    {}

    bool Object::equals(const Object& rhs) const
    {
        auto rv = false;

        if (isSameType(rhs))
        {
            rv = this->id_.get() == rhs.id_.get();
        }

        return rv;
    }

    std::string Object::toString() const
    {
        std::stringstream ss;
        ss << std::hex << std::setw(8) << std::setfill('0');
        ss << typeid(this).name() << " at 0x" << reinterpret_cast<size_t>(this);

        std::string line;
        std::string rv;

        while (std::getline(ss, line))
        {
            rv += line + "\n";
        }

        if (!rv.empty())
        {
            rv.pop_back();
        }

        return rv;
    }

    bool Object::isSameType(const Object& rhs) const
    {
        return typeid(*this).hash_code() == typeid(rhs).hash_code();
    }
}
