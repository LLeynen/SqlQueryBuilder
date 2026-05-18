// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :OrderByClause;
import :Field;
import :EnumMaps;

namespace DataAccessLayer::SqlQueryBuilder
{
	String BuilderBase::buildComponent(const OrderByClause& orderByClause) const
	{
		String orderByClauseString
		{ buildComponent(orderByClause.field()) + " " +
		SortOrderMap.at(orderByClause.sortOrder()) };

		return orderByClauseString;
	}
}
