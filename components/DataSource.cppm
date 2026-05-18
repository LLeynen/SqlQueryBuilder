// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:DataSource;

import std;

import :BuilderTypes;
import :Component;

namespace DataAccessLayer::SqlQueryBuilder
{
    class DataSourceImpl;

    export class DataSource : public Component
    {
    public:
        DataSource() noexcept;
        DataSource(ComponentId componentId);
        ~DataSource() override;

        DataSource(const DataSource& other);
        DataSource& operator=(const DataSource& other);
        DataSource(DataSource&& other) noexcept ;
        DataSource& operator=(DataSource&& other) noexcept ;

        [[nodiscard]] AliasPtr aliasPtr() const;
        [[nodiscard]] const String& alias() const;
        void setAlias(std::optional<Alias> alias) const;
        [[nodiscard]] bool hasAlias() const noexcept;

        [[nodiscard]] virtual DataSourcePtr clone() const = 0;

    protected:
        String toSql(const IBuilder* builderPtr) const override = 0;
        std::unique_ptr<DataSourceImpl> impl_;
    };
}
