#pragma once

#include <utility>

#include "Object.h"
#include "Utility.h"

namespace Parsers
{
    template<typename T>
    class Wrapper : public Object
    {
    public:
        Wrapper();
        explicit Wrapper(T value);

        bool equals(const Object& rhs) const override;
        std::string toString() const override;

    protected:
        Ptr<T> value_;
    };

    template<typename T>
    Wrapper<T>::Wrapper() :
        value_(alloc<T>())
    {}

    template<typename T>
    Wrapper<T>::Wrapper(T value) :
        value_(alloc<T>(std::forward<T>(value)))
    {}

    template<typename T>
    bool Wrapper<T>::equals(const Object& rhs) const
    {
        auto rv = false;

        if (isSameType(rhs))
        {
            try
            {
                // Для большего быстродействия возможна замена на static_cast.
                rv = *this->value_ == *dynamic_cast<Wrapper<T>>(rhs).value_;
            }
            catch (...)
            {
                // rv остается таким же...
            }
        }

        return rv;
    }

    template<typename T>
    std::string Wrapper<T>::toString() const
    {
        return show(*value_);
    }
}
