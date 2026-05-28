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
        Field(String columnName, std::optional<Alias> alias = std::nullopt);
        Field(String tableName, String columnName, std::optional<Alias> alias = std::nullopt);
        ~Field() override;

        Field(const Field&);
        Field& operator=(const Field&);
        Field(Field&&) noexcept;
        Field& operator=(Field&&) noexcept;

        [[nodiscard]] String tableName() const noexcept;
        void setTableName(String tableName) const;
        [[nodiscard]] String columnName() const noexcept;
        void setColumnName(String columnName) const;
        [[nodiscard]] Variant value() const noexcept;
        void setValue(Variant value) const;
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
        FieldRef(Field field)
            : field_(std::move(field))
        {}
/*        // 1. Single Column constructor (matches explicit single strings cleanly)
        FieldRef(String columnName)
            : field_(std::move(columnName))
        {}

        // 2. Single Column + Alias constructor
        FieldRef(String columnName, Alias alias)
            : field_(std::move(columnName), std::move(alias))
        {}*/
        FieldRef(std::initializer_list<const char*> list)
        {
            if (list.size() == 2)
            {
                auto it = list.begin();
                String table = *it++;
                String col = *it;
                field_ = Field{ std::move(table), std::move(col) };
            }
            else
            {
                field_ = Field{ String(list.size() > 0 ? *list.begin() : "") };
            }
        }

        [[nodiscard]] Field get() const noexcept
        {
            return field_;
        }

        [[nodiscard]] Field move() noexcept
        {
            return std::move(field_);
        }

    private:
        Field field_;
    };

    export inline Field field(String columnName, std::optional<Alias> alias = std::nullopt)
    {
        return { columnName, std::move(alias) };
    }

    export inline Field field(String tableName, String columnName, std::optional<Alias> alias = std::nullopt)
    {
        return { tableName, columnName, std::move(alias) };
    }
}
