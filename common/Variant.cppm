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

    // VariantValue
    using VariantValue = std::variant
        <
        std::nullptr_t,
        int,
        long,
        double,
        String,
        bool
        >;

    template<typename T>
    struct VariantConverter
    {
        // Type nullptr_t
        T operator()(const std::nullptr_t&) const
        {
            // Convert to string
            if constexpr (std::is_same_v<T, String>)
            {
                return "NULL";
            }
            throw std::bad_variant_access();
        }

        // Type int
        T operator()(const int& v) const
        {
            // Convert to string
            if constexpr (std::is_same_v<T, String>)
            {
                return toString(v);
            }
            // Return int directly
            else if constexpr (std::is_same_v<T, int>)
            {
                return v;
            }
            throw std::bad_variant_access();
        }

        // Type long
        T operator()(const long& v) const
        {
            // Convert to string
            if constexpr (std::is_same_v<T, String>)
            {
                return toString(v);
            }
            // Return long directly
            else if constexpr (std::is_same_v<T, long>)
            {
                return v;
            }
            throw std::bad_variant_access();
        }

        // Type double
        T operator()(const double& v) const
        {
            // Convert to string
            if constexpr (std::is_same_v<T, String>)
            {
                return toString(v);
            }
            // Return double directly
            else if constexpr (std::is_same_v<T, double>)
            {
                return v;
            }
            throw std::bad_variant_access();
        }

        // Type string
        T operator()(const String& v) const
        {
            // Return string directly
            if constexpr (std::is_same_v<T, String>)
            {
                return v;
            }
            throw std::bad_variant_access();
        }

        // Type bool
        T operator()(const bool& v) const
        {
            // Convert to string
            if constexpr (std::is_same_v<T, String>)
            {
                return v ? "TRUE" : "FALSE";
            }
            // Return bool directly
            else if constexpr (std::is_same_v<T, bool>)
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
        ~Variant();

        Variant(const Variant& other);
        Variant& operator=(const Variant& other);
        Variant(Variant&& other) noexcept;
        Variant& operator=(Variant&& other) noexcept;

        [[nodiscard]] const VariantValue& value() const noexcept;
        void setValue(const VariantValue& sqlValue);

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
        std::unique_ptr<VariantImpl> impl_;
    };

    // get
    template<typename T>
    T Variant::get() const
    {
        return std::visit(VariantConverter<T>{}, value());
    }

    // isType
    template<typename T>
    bool Variant::isType() const
    {
        return std::holds_alternative<T>(value());
    }

    export using VariantList = std::vector<Variant>;
}
