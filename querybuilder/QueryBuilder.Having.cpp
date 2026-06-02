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
	QueryBuilder& QueryBuilder::having(const FilterBase& filter)
	{
		if (impl_->havingFilterPtr_)
		{
			impl_->havingFilterPtr_ = std::make_shared<LogicalFilter>(*impl_->havingFilterPtr_, LogicOperator::And, *filter.clone());
		}
		else
		{
			impl_->havingFilterPtr_ = filter.clone();
		}
		return *this;
	}
}
