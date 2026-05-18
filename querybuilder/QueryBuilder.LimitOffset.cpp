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
	// QueryBuilder::limit
	QueryBuilder& QueryBuilder::limit(const int quantity)
	{
		if (quantity < 0)
		{
			throw std::runtime_error("Quantity for LIMIT clause cannot be negative");
		}

		ensureSharedPtr(impl_->limitClausePtr_)->setQuantity(quantity);

		return *this;
	}

	// QueryBuilder::offset
	QueryBuilder& QueryBuilder::offset(const int quantity)
	{
		if (quantity < 0)
		{
			throw std::runtime_error("Quantity for OFFSET clause cannot be negative");
		}

		ensureSharedPtr(impl_->offsetClausePtr_)->setQuantity(quantity);

		return *this;
	}
}
