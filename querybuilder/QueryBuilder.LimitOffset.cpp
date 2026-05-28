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
	QueryBuilder& QueryBuilder::limit(const int limit)
	{
		if (limit < 0)
		{
			throw std::runtime_error("Quantity for LIMIT clause cannot be negative");
		}

		ensureSharedPtr(impl_->limitClausePtr_)->setQuantity(limit);

		return *this;
	}


	QueryBuilder& QueryBuilder::offset(const int offset)
	{
		if (offset < 0)
		{
			throw std::runtime_error("Quantity for OFFSET clause cannot be negative");
		}

		ensureSharedPtr(impl_->offsetClausePtr_)->setQuantity(offset);

		return *this;
	}
}
