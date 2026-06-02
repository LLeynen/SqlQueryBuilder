// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import :BuilderTypes;
import :Concepts;
import :FilterBase;
import :Impl;

namespace DataAccessLayer::SqlQueryBuilder
{
	QueryBuilder& QueryBuilder::where(const FilterBase& filter)
	{
		if (impl_->whereFilterPtr_)
		{
			impl_->whereFilterPtr_ = std::make_shared<LogicalFilter>(*impl_->whereFilterPtr_, LogicOperator::And, filter);
		}
		else
		{
			impl_->whereFilterPtr_ = filter.clone();
		}
		return *this;
	}
}
