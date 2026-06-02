// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :Operand;

import std;

import :BuilderTypes;

namespace DataAccessLayer::SqlQueryBuilder
{
	Operand::Operand() = default;


	Operand::Operand(FieldRef fieldRef)
		: node_(std::make_shared<Field>(fieldRef.move()))
	{}


	Operand::Operand(Expression expression)
		: node_(std::make_shared<Expression>(std::move(expression)))
	{}


	Operand::Operand(Function func)
		: node_(std::make_shared<Function>(std::move(func)))
	{}


	Operand::Operand(Aggregate aggregate)
		: node_(std::make_shared<Aggregate>(std::move(aggregate)))
	{}


	Operand::Operand(ParameterSelectable parameterSelectable)
		: node_(std::make_shared<ParameterSelectable>(std::move(parameterSelectable)))
	{}


	Operand::Operand(Literal literal)
		: node_(std::make_shared<Literal>(std::move(literal)))
	{}


	Operand::Operand(QueryBuilder queryBuilder)
	{
		const auto queryBuilderPtr = std::make_shared<QueryBuilder>(std::move(queryBuilder));
		node_ = std::make_shared<QuerySelectable>(std::move(queryBuilderPtr));
	}


	Operand::~Operand() = default;


	SelectablePtr Operand::get() const &
	{
		return node_;
	}


	SelectablePtr Operand::get() && noexcept
	{
		return std::move(node_);
	}
}
