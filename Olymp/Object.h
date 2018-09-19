#pragma once

#include "Utility.h"

namespace Parsers
{
    class Object
    {
    public:
        Object();
        virtual ~Object() = default;
        Object(const Object& rhs) = default;
        Object(Object&& rhs) noexcept = default;
        Object& operator=(const Object& rhs) = default;
        Object& operator=(Object&& rhs) noexcept = default;

        virtual bool equals(const Object& rhs) const;
        virtual std::string toString() const;

    protected:
        bool isSameType(const Object& rhs) const;

    private:
        Ptr<char> id_;
    };
}
