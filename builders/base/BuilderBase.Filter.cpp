// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :Filter;
import :ConditionBase;

namespace DataAccessLayer::SqlQueryBuilder
{
	String BuilderBase::buildComponent(const Filter& filter) const
	{
		String filterString{};

		if (const auto conditionBasePtr = filter.conditionBase())
		{
			filterString = conditionBasePtr->sql(this);
		}

		return filterString;
	}
}
