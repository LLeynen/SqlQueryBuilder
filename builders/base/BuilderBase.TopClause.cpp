// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :TopClause;
import :EnumMaps;

namespace DataAccessLayer::SqlQueryBuilder
{
	// BuilderBase::buildComponent(TopClause)
	String BuilderBase::buildComponent(const TopClause& topClause) const
	{
		String topClauseString{};

		if (topClause.quantity() > 0)
		{
			topClauseString = "TOP " + toString(topClause.quantity()) + " ";
			if (topClause.topUnit() == TopUnit::Percent)
			{
				topClauseString += TopUnitMap.at(topClause.topUnit()) + " ";
			}
		}

		return topClauseString;
	}
}
