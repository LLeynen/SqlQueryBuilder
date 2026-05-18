// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :LimitClause;

namespace DataAccessLayer::SqlQueryBuilder
{
	// BuilderBase::buildComponent(LimitClause)
	String BuilderBase::buildComponent(const LimitClause& limitClause) const
	{
		String limitClauseString{};

		if (limitClause.quantity() > 0)
		{
			limitClauseString = " LIMIT " + toString(limitClause.quantity());
		}

		return limitClauseString;
	}
}
