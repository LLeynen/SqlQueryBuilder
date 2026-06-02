// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:Variant;

import std;

import :BuilderTypes;

namespace DataAccessLayer::SqlQueryBuilder
{
    class VariantImpl;

    using VariantValue = std::variant
        <
        std::nullptr_t,
        int,
        long,
        double,
        String,
        bool,
        Date
        >;

    template<typename T>
    struct VariantConverter
    {
        T operator()(const std::nullptr_t&) const
        {
            if constexpr (std::is_same_v<T, String>)
            {
                return "NULL";
            }
            throw std::bad_variant_access();
        }


        T operator()(const int& v) const
        {
            if constexpr (std::is_same_v<T, String>)
            {
                return toString(v);
            }
            else if constexpr (std::is_same_v<T, int>)
            {
                return v;
            }
            throw std::bad_variant_access();
        }


        T operator()(const long& v) const
        {
            if constexpr (std::is_same_v<T, String>)
            {
                return toString(v);
            }
            else if constexpr (std::is_same_v<T, long>)
            {
                return v;
            }
            throw std::bad_variant_access();
        }


        T operator()(const double& v) const
        {
            if constexpr (std::is_same_v<T, String>)
            {
                return toString(v);
            }
            else if constexpr (std::is_same_v<T, double>)
            {
                return v;
            }
            throw std::bad_variant_access();
        }


        T operator()(const String& v) const
        {
            if constexpr (std::is_same_v<T, String>)
            {
                return v;
            }
            throw std::bad_variant_access();
        }


        T operator()(const bool& v) const
        {
            if constexpr (std::is_same_v<T, String>)
            {
                return v ? "TRUE" : "FALSE";
            }
            else if constexpr (std::is_same_v<T, bool>)
            {
                return v;
            }
            throw std::bad_variant_access();
        }

        T operator()(const Date& v) const
        {
            if constexpr (std::is_same_v<T, String>)
            {
                return std::format("{}", v);
            }
            else if constexpr (std::is_same_v<T, Date>)
            {
                return v;
            }
            throw std::bad_variant_access();
        }
    };

    export class Variant
    {
    public:
        Variant() noexcept;
        Variant(std::nullptr_t val) noexcept;
        Variant(int val) noexcept;
        Variant(long val) noexcept;
        Variant(double val) noexcept;
        Variant(const char* val);
        Variant(const String& val);
        Variant(bool val) noexcept;
        Variant(Date val) noexcept;
        ~Variant();

        Variant(const Variant& other);
        Variant& operator=(const Variant& other);
        Variant(Variant&& other) noexcept;
        Variant& operator=(Variant&& other) noexcept;

        [[nodiscard]] const VariantValue& value() const noexcept;
        void setValue(const VariantValue& sqlValue) const;

        template<typename T>
        T get() const;

        [[nodiscard]] int toInt() const;
        [[nodiscard]] long toLong() const;
        [[nodiscard]] double toDouble() const;
        [[nodiscard]] bool toBool() const;
        [[nodiscard]] String toString() const;
        [[nodiscard]] String sqlFormat() const;

        [[nodiscard]] bool isNull() const noexcept;
        [[nodiscard]] bool isInteger() const noexcept;
        [[nodiscard]] bool isLong() const noexcept;
        [[nodiscard]] bool isDouble() const noexcept;
        [[nodiscard]] bool isString() const noexcept;
        [[nodiscard]] bool isBoolean() const noexcept;

        template<typename T>
        [[nodiscard]] bool isType() const;

    private:
        std::unique_ptr<VariantImpl> impl_{};
    };


    template<typename T>
    T Variant::get() const
    {
        return std::visit(VariantConverter<T>{}, value());
    }


    template<typename T>
    bool Variant::isType() const
    {
        return std::holds_alternative<T>(value());
    }

    export using VariantList = std::vector<Variant>;
}
