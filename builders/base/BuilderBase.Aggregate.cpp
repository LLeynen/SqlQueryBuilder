// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :Aggregate;
import :Alias;
import :EnumMaps;

namespace DataAccessLayer::SqlQueryBuilder
{
	String BuilderBase::buildComponent(const Aggregate& aggregate) const
	{
		String aggregateString{};
		String targetString{};

		auto selectablePtr = aggregate.selectable();
		targetString = selectablePtr->sql(this);

		if (!targetString.empty())
		{
			aggregateString = AggregateFunctionMap.at(aggregate.aggregateFunction())
				+ "(" + targetString + ")";

			if (aggregate.hasAlias())
			{
				aggregateString += buildComponent(*aggregate.aliasPtr());
			}
		}

		return aggregateString;
	}
}
