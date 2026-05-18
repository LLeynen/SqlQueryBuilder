// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :OffsetClause;

namespace DataAccessLayer::SqlQueryBuilder
{
	String BuilderBase::buildComponent(const OffsetClause& offsetClause) const
	{
		String offsetClauseString{};

		if (offsetClause.quantity() > 0)
		{
			offsetClauseString = " OFFSET " + toString(offsetClause.quantity());
		}

		return offsetClauseString;
	}
}
