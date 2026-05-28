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
	QueryBuilder& QueryBuilder::top(const int quantity, const TopUnit topUnit)
	{
		if (quantity < 0)
		{
			throw std::runtime_error("Quantity for TOP clause cannot be negative");
		}

		ensureSharedPtr(impl_->topClausePtr_)->setQuantity(quantity);
		impl_->topClausePtr_->setUnit(topUnit);

		return *this;
	}


	QueryBuilder& QueryBuilder::topPercent(const int quantity)
	{
		return top(quantity, TopUnit::Percent);
	}
}
