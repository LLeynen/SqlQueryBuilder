// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderTypes;
import :Concepts;
import :Aggregate;
import :Field;
import :Impl;

namespace DataAccessLayer::SqlQueryBuilder
{
	QueryBuilder& QueryBuilder::aggregate(const AggregateFunction aggregateFunction, Operand operand, std::optional<Alias> alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		impl_->selectableListPtr_->push_back(std::make_shared<Aggregate>(aggregateFunction, operand.get(), alias));

		return *this;
	}
}
