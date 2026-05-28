// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

export module QueryBuilder:Aggregate;

import std;

import :BuilderTypes;
import :Selectable;
import :Alias;
import :Operand;
import :Variant;
import :Parameter;

namespace DataAccessLayer::SqlQueryBuilder
{
    class AggregateImpl;

    export class Aggregate : public Selectable
    {
    public:
        Aggregate();
        Aggregate(AggregateFunction aggregateFunction, FormulaArg formulaArg, std::optional<Alias> alias = std::nullopt);
//        Aggregate(AggregateFunction aggregateFunction, SelectablePtr selectablePtr, std::optional<Alias> alias = std::nullopt);
        ~Aggregate() override;

        Aggregate(const Aggregate& other);
        Aggregate& operator=(const Aggregate& other);
        Aggregate(Aggregate&&) noexcept;
        Aggregate& operator=(Aggregate&&) noexcept;

        [[nodiscard]] AggregateFunction aggregateFunction() const noexcept;
//        void setAggregateFunction(AggregateFunction aggregateFunction) const noexcept;

        [[nodiscard]] FormulaArg arg() const noexcept;
//        void setSelectable(const FieldPtr& fieldPtr) const;             // to be checked: pass FieldRef?
//        void setSelectable(const ExpressionPtr& expressionPtr) const;   // to be checked; pass Expression by value?

        [[nodiscard]] SelectablePtr clone() const override;

    protected:
        String toSql(const IBuilder* builderPtr) const override;

    private:
        std::unique_ptr<AggregateImpl> impl_{};
    };

    export inline Aggregate aggregate(const AggregateFunction aggregateFunction, FormulaArg formulaArg, std::optional<Alias> alias = std::nullopt)
    {
        return { aggregateFunction, std::move(formulaArg), std::move(alias) };
    }
}

