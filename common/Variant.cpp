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

    // Variant::Variant
    Variant::Variant() noexcept
        : impl_{ std::make_unique<VariantImpl>() }
    {}

    // Variant::Variant(nullptr_t)
    Variant::Variant(std::nullptr_t val) noexcept
        : impl_{ std::make_unique<VariantImpl>() }
    {
        impl_->value_ = val;
    }

    // Variant::Variant(int);
    Variant::Variant(int val) noexcept
        : impl_{ std::make_unique<VariantImpl>() }
    {
        impl_->value_ = val;
    }

    // Variant::Variant(long);
    Variant::Variant(long val) noexcept
        : impl_{ std::make_unique<VariantImpl>() }
    {
        impl_->value_ = val;
    }

    // Variant::Variant(double);
    Variant::Variant(double val) noexcept
        : impl_{ std::make_unique<VariantImpl>() }
    {
        impl_->value_ = val;
    }

    // Variant::Variant(const char*);
    Variant::Variant(const char* val)
        : impl_{ std::make_unique<VariantImpl>() }
    {
        impl_->value_ = String{ val };
    }

    // Variant::Variant(const String&);
    Variant::Variant(const String& val)
        : impl_{ std::make_unique<VariantImpl>() }
    {
        impl_->value_ = val;
    }

    // Variant::Variant(bool);
    Variant::Variant(bool val) noexcept
        : impl_{ std::make_unique<VariantImpl>() }
    {
        impl_->value_ = val;
    }

    // Variant::~Variant
    Variant::~Variant() = default;

    // Variant::Variant(Variant&)
    Variant::Variant(const Variant& other)
        : impl_{ std::make_unique<VariantImpl>(*other.impl_) }
    {}

    // Variant::operator=(Variant&)
    Variant& Variant::operator=(const Variant& other)
    {
        if (this != &other)
        {
            impl_ = std::make_unique<VariantImpl>(*other.impl_);
        }

        return *this;
    }

    // Variant::Variant(Variant&&)
    Variant::Variant(Variant&& other) noexcept = default;

    // Variant::operator=(Variant&&)
    Variant& Variant::operator=(Variant&& other) noexcept = default;

    // Variant::value
    const VariantValue& Variant::value() const noexcept
    {
        return impl_->value_;
    }

    // Variant::setValue
    void Variant::setValue(const VariantValue& sqlValue)
    {
        impl_->value_ = sqlValue;
    }

    // Variant::toInt
    int Variant::toInt() const
    {
        return get<int>();
    }

    // Variant::toLong
    long Variant::toLong() const
    {
        return get<long>();
    }

    // Variant::toDouble
    double Variant::toDouble() const
    {
        return get<double>();
    }

    // Variant::toBool
    bool Variant::toBool() const
    {
        return get<bool>();
    }

    // Variant::toString
    String Variant::toString() const
    {
        return get<String>();
    }

    // VariantFormatter, visitor for formatting values as SQL strings
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
    };

    // Variant::sqlFormat
    String Variant::sqlFormat() const
    {
        return std::visit(VariantFormatter{}, impl_->value_);
    }

    // Variant::isNull
    bool Variant::isNull() const noexcept
    {
        return std::holds_alternative<std::nullptr_t>(impl_->value_);
    }

    // Variant::isInteger
    bool Variant::isInteger() const noexcept
    {
        return std::holds_alternative<int>(impl_->value_);
    }

    // Variant::isLong
    bool Variant::isLong() const noexcept
    {
        return std::holds_alternative<long>(impl_->value_);
    }

    // Variant::isDouble
    bool Variant::isDouble() const noexcept
    {
        return std::holds_alternative<double>(impl_->value_);
    }

    // Variant::isString
    bool Variant::isString() const noexcept
    {
        return std::holds_alternative<String>(impl_->value_);
    }

    // Variant::isBoolean
    bool Variant::isBoolean() const noexcept
    {
        return std::holds_alternative<bool>(impl_->value_);
    }
}
