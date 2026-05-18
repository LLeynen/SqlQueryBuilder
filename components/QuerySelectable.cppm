// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:QuerySelectable;

import std;

import :BuilderTypes;
import :Selectable;
import :Query;
import :Alias;

namespace DataAccessLayer::SqlQueryBuilder
{
    class QuerySelectableImpl;

    export class QuerySelectable : public Selectable
    {
    public:
        QuerySelectable() noexcept;

        QuerySelectable(const QueryBuilder& queryBuilder, std::optional<Alias> alias = std::nullopt);
        QuerySelectable(std::shared_ptr<QueryBuilder> queryBuilder, std::optional<Alias> alias = std::nullopt);
        QuerySelectable(const String& rawSql, std::optional<Alias> alias = std::nullopt);

        ~QuerySelectable() override;

        QuerySelectable(const QuerySelectable&);
        QuerySelectable& operator=(const QuerySelectable&);
        QuerySelectable(QuerySelectable&&) noexcept;
        QuerySelectable& operator=(QuerySelectable&&) noexcept;

        [[nodiscard]] QueryPtr query() const;
        void setQuery(const Query& query) const;

        [[nodiscard]] SelectablePtr clone() const override;

    protected:
        String toSql(const IBuilder* builderPtr) const override;

    private:
        std::unique_ptr<QuerySelectableImpl> impl_;
    };
}
