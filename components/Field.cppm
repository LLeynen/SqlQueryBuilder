// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:Field;

import std;

import :BuilderTypes;
import :Selectable;
import :Alias;

namespace DataAccessLayer::SqlQueryBuilder
{
    class FieldImpl;

    export class Field : public Selectable
    {
    public:
        Field() noexcept;
        explicit Field(String columnName, std::optional<Alias> alias = std::nullopt);
        Field(String tableName, String columnName, std::optional<Alias> alias = std::nullopt);
        ~Field() override;

        Field(const Field&);
        Field& operator=(const Field&);
        Field(Field&&) noexcept;
        Field& operator=(Field&&) noexcept;

        [[nodiscard]] const String& tableName() const noexcept;
        void setTableName(const String& tableName) const;
        [[nodiscard]] const String& columnName() const noexcept;
        void setColumnName(const String& columnName) const;
        [[nodiscard]] const Variant& value() const noexcept;
        void setValue(const Variant& value) const;
        [[nodiscard]] bool isNull() const noexcept;

        [[nodiscard]] SelectablePtr clone() const override;

    protected:
        String toSql(const IBuilder* builderPtr) const override;

    private:
        std::unique_ptr<FieldImpl> impl_;
    };

    export class FieldRef
    {
    public:
        template <typename... Args>
            requires std::is_constructible_v<Field, Args...>
        FieldRef(Args&&... args)
            : field_(std::forward<Args>(args)...)
        {}

        [[nodiscard]] const Field& get() const noexcept
        {
            return field_;
        }

        [[nodiscard]] Field move() const noexcept
        {
            return std::move(field_);
        }

    private:
        Field field_;
    };
}
