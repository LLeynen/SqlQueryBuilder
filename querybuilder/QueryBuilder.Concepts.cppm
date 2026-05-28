// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:Concepts;

import std;

import :BuilderTypes;

namespace DataAccessLayer::SqlQueryBuilder
{
    /*
    template<typename T>
    concept ConvertibleToConditionValue =
        std::convertible_to<T, std::nullptr_t> ||
        std::convertible_to<T, Variant> ||
        std::convertible_to<T, ParameterValue> ||
        std::convertible_to<T, Parameter> ||
        std::convertible_to<T, Field> ||
        std::convertible_to<T, ListOfValues> ||
        std::convertible_to<T, QueryDataSource> ||
        std::convertible_to<T, String> ||
        std::convertible_to<T, int> ||
        std::convertible_to<T, double> ||
        std::convertible_to<T, bool> ||
        std::convertible_to<T, const char*>;
*/

    template<typename T>
    concept ConvertibleToString =
        std::convertible_to<T, String>;

    template<typename T>
    concept ConvertibleToInt =
        std::convertible_to<T, int>;

    template<typename T>
    concept ConvertibleToDouble =
        std::convertible_to<T, double>;

    template<typename T>
    concept ConvertibleToBool =
        std::convertible_to<T, bool>;

    template<typename T>
    concept ConvertibleToNullptr_t =
        std::convertible_to<T, std::nullptr_t>;

    template <typename T>
    concept ConvertibleToFilterValue =
        requires(T&& val) { FilterValue{ std::forward<T>(val) }; };

    template <typename T>
    concept ConvertibleToFormulaValue =
        requires(T&& val) { FormulaValue{ std::forward<T>(val) }; };

    template<typename T, typename... Args> std::shared_ptr<T>& ensureSharedPtr(std::shared_ptr<T>& slot, Args&&... args)
    {
        if (!slot)
        {
            slot = std::make_shared<T>(std::forward<Args>(args)...);
        }
        return slot;
    }

    template<typename T, typename... Args> std::shared_ptr<T>& ensureUniquePtr(std::shared_ptr<T>& slot, Args&&... args)
    {
        if (!slot)
        {
            slot = std::make_unique<T>(std::forward<Args>(args)...);
        }
        return slot;
    }
}
