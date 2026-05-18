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
	// QueryBuilder::expression(Expression)
	QueryBuilder& QueryBuilder::expression(const Expression& expression)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		impl_->selectableListPtr_->push_back(std::make_shared<Expression>(expression));
		return *this;
	}


	QueryBuilder& QueryBuilder::expression(const Operand& left, const Operator op, const Operand& right, const std::optional<String>& alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		Expression expression{ left, op, right, alias };
		impl_->selectableListPtr_->push_back(std::make_shared<Expression>(expression));

		return *this;
	}


	QueryBuilder& QueryBuilder::expression(Operator op, const Operand& operand, const std::optional<String>& alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		Expression expression { op, operand, alias };
		impl_->selectableListPtr_->push_back(std::make_shared<Expression>(expression));

		return *this;
	}


	QueryBuilder& QueryBuilder::expression(const Selectable& selectable, const std::optional<String>& alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		Expression expression{ selectable, alias };
		impl_->selectableListPtr_->push_back(std::make_shared<Expression>(expression));

		return *this;
	}


	QueryBuilder& QueryBuilder::expression(const ScalarFunction function, std::initializer_list<Operand> args, const std::optional<String>& alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		Expression expression{ function, args, alias };
		impl_->selectableListPtr_->push_back(std::make_shared<Expression>(expression));

		return *this;
	}


	QueryBuilder& QueryBuilder::expression(const AggregateFunction function, const Selectable& selectable, const std::optional<String>& alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		Expression expression{ function, selectable, alias };
		impl_->selectableListPtr_->push_back(std::make_shared<Expression>(expression));

		return *this;
	}
}
