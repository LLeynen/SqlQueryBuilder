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

        QuerySelectable(QueryBuilder queryBuilder, std::optional<Alias> alias = std::nullopt);
        QuerySelectable(QueryBuilderPtr queryBuilderPtr, std::optional<Alias> alias = std::nullopt);
        QuerySelectable(String rawSql, std::optional<Alias> alias = std::nullopt);

        ~QuerySelectable() override;

        QuerySelectable(const QuerySelectable&);
        QuerySelectable& operator=(const QuerySelectable&);
        QuerySelectable(QuerySelectable&&) noexcept;
        QuerySelectable& operator=(QuerySelectable&&) noexcept;

        [[nodiscard]] QueryPtr query() const;
        void setQuery(Query query) const;

        [[nodiscard]] SelectablePtr clone() const override;

    protected:
        String toSql(const IBuilder* builderPtr) const override;

    private:
        std::unique_ptr<QuerySelectableImpl> impl_;
    };
}
