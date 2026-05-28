// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import :BuilderTypes;
import :Concepts;
import :Impl;

namespace DataAccessLayer::SqlQueryBuilder
{
	QueryBuilder& QueryBuilder::expression(Expression expression)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		impl_->selectableListPtr_->push_back(std::make_shared<Expression>(std::move(expression)));
		return *this;
	}


	QueryBuilder& QueryBuilder::expression(Operand left, const Operator op, Operand right, std::optional<Alias> alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		Expression expression{ std::move(left), op, std::move(right), std::move(alias) };
		impl_->selectableListPtr_->push_back(std::make_shared<Expression>(expression));

		return *this;
	}

	QueryBuilder& QueryBuilder::expression(Operand lhs, Operator op, FormulaValue formulaValue, std::optional<Alias> alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		Expression expression{ std::move(lhs), op, std::move(formulaValue), std::move(alias) };
		impl_->selectableListPtr_->push_back(std::make_shared<Expression>(expression));

		return *this;
	}

	QueryBuilder& QueryBuilder::expression(FormulaValue formulaValue, Operator op, Operand rhs, std::optional<Alias> alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		Expression expression{ std::move(formulaValue), op, std::move(rhs), std::move(alias) };
		impl_->selectableListPtr_->push_back(std::make_shared<Expression>(expression));

		return *this;
	}

	QueryBuilder& QueryBuilder::expression(Operator op, Operand operand, std::optional<Alias> alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		Expression expression { op, std::move(operand), alias };
		impl_->selectableListPtr_->push_back(std::make_shared<Expression>(expression));

		return *this;
	}

	QueryBuilder& QueryBuilder::expression(Operator op, FormulaValue formulaValue, std::optional<Alias> alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		Expression expression { op, std::move(formulaValue), alias };
		impl_->selectableListPtr_->push_back(std::make_shared<Expression>(expression));

		return *this;
	}


	QueryBuilder& QueryBuilder::expression(const ScalarFunction function, const std::vector<FormulaArg> args, std::optional<Alias> alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		Expression expression{ function, args, std::move(alias) };
		impl_->selectableListPtr_->push_back(std::make_shared<Expression>(expression));

		return *this;
	}


	QueryBuilder& QueryBuilder::expression(const AggregateFunction function, FormulaArg arg, std::optional<Alias> alias) noexcept
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		Expression expression{ function, arg, std::move(alias) };
		impl_->selectableListPtr_->push_back(std::make_shared<Expression>(expression));

		return *this;
	}
}
