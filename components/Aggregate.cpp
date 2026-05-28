// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :Aggregate;

import std;

import :BuilderTypes;
//import :IBuilder;
//import :Selectable;
//import :Expression;
//import :Field;

namespace DataAccessLayer::SqlQueryBuilder
{
    class AggregateImpl
    {
    public:
        AggregateImpl() = default;
//        AggregateImpl(const AggregateFunction aggregateFunction, SelectablePtr selectablePtr)
//            : aggregateFunction_{ aggregateFunction }
//            , selectablePtr_{std::move( selectablePtr )}
//        {}
        AggregateImpl(AggregateFunction aggregateFunction, FormulaArg arg)
            : aggregateFunction_{ aggregateFunction }
            , arg_{ std::move(arg) }
        {}

        ~AggregateImpl() = default;

        AggregateImpl(const AggregateImpl&) = default;
        AggregateImpl& operator=(const AggregateImpl&) = default;
		AggregateImpl(AggregateImpl&&) noexcept = default;
		AggregateImpl& operator=(AggregateImpl&&) noexcept = default;

        AggregateFunction aggregateFunction_{ AggregateFunction::Sum };
        FormulaArg arg_{std::monostate{}};
    };


    Aggregate::Aggregate()
        : Selectable(ComponentId::Aggregate)
        , impl_{ std::make_unique<AggregateImpl>() }
    {}


    Aggregate::Aggregate(AggregateFunction aggregateFunction, FormulaArg formulaArg, std::optional<Alias> alias)
        : Selectable(ComponentId::Aggregate)
        , impl_{ std::make_unique<AggregateImpl>(aggregateFunction, std::move(formulaArg)) }
    {
/*        const SelectablePtr selectablePtr = std::move(operand).get();

        if (selectablePtr)
        {
            selectablePtr->suppressBrackets(true);
        }
*/
//        impl_ = std::make_unique<AggregateImpl>(aggregateFunction, std::move(selectablePtr));

        Selectable::setAlias(std::move(alias));
    }

    /*
    Aggregate::Aggregate(AggregateFunction aggregateFunction, SelectablePtr selectablePtr, std::optional<Alias> alias)
    {
        if (selectablePtr)
        {
            selectablePtr->suppressBrackets(true);
        }

        impl_ = std::make_unique<AggregateImpl>(aggregateFunction, std::move(selectablePtr));

        Selectable::setAlias(std::move(alias));
    }
*/

    Aggregate::~Aggregate() = default;


    Aggregate::Aggregate(const Aggregate& other)
        : Selectable(other)
        , impl_{ std::make_unique<AggregateImpl>(*other.impl_) }
    {}


    Aggregate& Aggregate::operator=(const Aggregate& other)
    {
        if (this != &other)
        {
            Selectable::operator=(other);
            impl_ = std::make_unique<AggregateImpl>(*other.impl_);
        }
        return *this;
    }


    Aggregate::Aggregate(Aggregate&& other) noexcept
        : Selectable(std::move(other))
        , impl_{ std::move(other.impl_) }
    {}


    Aggregate& Aggregate::operator=(Aggregate&& other) noexcept
    {
        if (this != &other)
        {
            Selectable::operator=(std::move(other));
            impl_ = std::move(other.impl_);
        }
        return *this;
    }


    SelectablePtr Aggregate::clone() const
    {
        return std::make_shared<Aggregate>(*this);
    }


    AggregateFunction Aggregate::aggregateFunction() const noexcept
    {
        return impl_->aggregateFunction_;
    }


/*    void Aggregate::setAggregateFunction(const AggregateFunction aggregateFunction) const noexcept
    {
        impl_->aggregateFunction_ = aggregateFunction;
    }
*/

    FormulaArg Aggregate::arg() const noexcept
    {
        return impl_->arg_;
    }

/*
    void Aggregate::setSelectable(const FieldPtr& fieldPtr) const
    {
        impl_->selectablePtr_ = fieldPtr;
    }


    void Aggregate::setSelectable(const ExpressionPtr& expressionPtr) const
    {
        impl_->selectablePtr_ = expressionPtr;
    }

*/
    String Aggregate::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }
}
