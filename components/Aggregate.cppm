// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

export module QueryBuilder:Aggregate;

import std;

import :BuilderTypes;
import :Selectable;
import :Alias;

namespace DataAccessLayer::SqlQueryBuilder
{
    class AggregateImpl;

    export class Aggregate : public Selectable
    {
    public:
        Aggregate();
        Aggregate(AggregateFunction aggregateFunction, const SelectablePtr& selectablePtr, std::optional<Alias> alias = std::nullopt);
        ~Aggregate() override;

        Aggregate(const Aggregate& other);
        Aggregate& operator=(const Aggregate& other);
        Aggregate(Aggregate&&) noexcept;
        Aggregate& operator=(Aggregate&&) noexcept;

        [[nodiscard]] AggregateFunction aggregateFunction() const noexcept;
        void setAggregateFunction(AggregateFunction aggregateFunction) const noexcept;

        [[nodiscard]] SelectablePtr selectable() const noexcept;
        void setSelectable(const FieldPtr& fieldPtr) const;
        void setSelectable(const ExpressionPtr& expressionPtr) const;

        [[nodiscard]] SelectablePtr clone() const override;

    protected:
        String toSql(const IBuilder* builderPtr) const override;

    private:
        std::unique_ptr<AggregateImpl> impl_{};
    };
}
