// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :Variant;

import std;

import :BuilderTypes;

namespace DataAccessLayer::SqlQueryBuilder
{
    class VariantImpl
    {
    public:
        VariantImpl() = default;
        ~VariantImpl() = default;

        VariantImpl(const VariantImpl& other) = default;
        VariantImpl& operator=(const VariantImpl& other) = default;
        VariantImpl(VariantImpl&& other) = default;
        VariantImpl& operator=(VariantImpl&& other) = default;

        VariantValue value_{};
    };


    Variant::Variant() noexcept
        : impl_{ std::make_unique<VariantImpl>() }
    {}


    Variant::Variant(std::nullptr_t val) noexcept
        : impl_{ std::make_unique<VariantImpl>() }
    {
        impl_->value_ = val;
    }


    Variant::Variant(int val) noexcept
        : impl_{ std::make_unique<VariantImpl>() }
    {
        impl_->value_ = val;
    }


    Variant::Variant(long val) noexcept
        : impl_{ std::make_unique<VariantImpl>() }
    {
        impl_->value_ = val;
    }


    Variant::Variant(double val) noexcept
        : impl_{ std::make_unique<VariantImpl>() }
    {
        impl_->value_ = val;
    }


    Variant::Variant(const char* val)
        : impl_{ std::make_unique<VariantImpl>() }
    {
        impl_->value_ = String{ val };
    }


    Variant::Variant(const String& val)
        : impl_{ std::make_unique<VariantImpl>() }
    {
        impl_->value_ = val;
    }


    Variant::Variant(bool val) noexcept
        : impl_{ std::make_unique<VariantImpl>() }
    {
        impl_->value_ = val;
    }


    Variant::Variant(Date val) noexcept
        : impl_{ std::make_unique<VariantImpl>() }
    {
        impl_->value_ = val;
    }


    Variant::~Variant() = default;


    Variant::Variant(const Variant& other)
        : impl_{ std::make_unique<VariantImpl>(*other.impl_) }
    {}


    Variant& Variant::operator=(const Variant& other)
    {
        if (this != &other)
        {
            impl_ = std::make_unique<VariantImpl>(*other.impl_);
        }

        return *this;
    }


    Variant::Variant(Variant&& other) noexcept
        : impl_{ std::move(other.impl_) }
    {}


    Variant& Variant::operator=(Variant&& other) noexcept
    {
        if (this != &other)
        {
            impl_ = std::move(other.impl_);
        }
        return *this;
    }


    const VariantValue& Variant::value() const noexcept
    {
        return impl_->value_;
    }


    void Variant::setValue(const VariantValue& sqlValue) const
    {
        impl_->value_ = sqlValue;
    }


    int Variant::toInt() const
    {
        return get<int>();
    }


    long Variant::toLong() const
    {
        return get<long>();
    }


    double Variant::toDouble() const
    {
        return get<double>();
    }


    bool Variant::toBool() const
    {
        return get<bool>();
    }


    String Variant::toString() const
    {
        return get<String>();
    }


    struct VariantFormatter
    {
        String operator()(std::nullptr_t) const 
        { 
            return "NULL"; 
        }

        String operator()(const int v) const 
        { 
            return toString(v); 
        }

        String operator()(const long v) const 
        { 
            return toString(v); 
        }

        String operator()(const double v) const 
        { 
            return toString(v); 
        }

        String operator()(const String& v) const 
        { 
            return "'" + v + "'"; 
        }

        String operator()(const bool v) const 
        { 
            return v ? "TRUE" : "FALSE"; 
        }

        String operator()(const Date& v) const
        {
            return std::format("'{}'", v);
        }
    };


    String Variant::sqlFormat() const
    {
        return std::visit(VariantFormatter{}, impl_->value_);
    }


    bool Variant::isNull() const noexcept
    {
        return std::holds_alternative<std::nullptr_t>(impl_->value_);
    }


    bool Variant::isInteger() const noexcept
    {
        return std::holds_alternative<int>(impl_->value_);
    }


    bool Variant::isLong() const noexcept
    {
        return std::holds_alternative<long>(impl_->value_);
    }


    bool Variant::isDouble() const noexcept
    {
        return std::holds_alternative<double>(impl_->value_);
    }


    bool Variant::isString() const noexcept
    {
        return std::holds_alternative<String>(impl_->value_);
    }


    bool Variant::isBoolean() const noexcept
    {
        return std::holds_alternative<bool>(impl_->value_);
    }
}
