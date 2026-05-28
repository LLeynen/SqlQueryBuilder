// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :Aggregate;
import :Alias;
import :EnumMaps;
import :FormulaArgString;

namespace DataAccessLayer::SqlQueryBuilder
{
	String BuilderBase::buildComponent(const Aggregate& aggregate) const
	{
		const auto arg { aggregate.arg() };
		if (std::holds_alternative<Operand>(arg))
		{
			if (auto selectablePtr = std::get<Operand>(arg).get())
			{
				selectablePtr->suppressBrackets(true);
			}
		}

		String aggregateString{AggregateFunctionMap.at(aggregate.aggregateFunction())
				+ "(" + formulaArgString(this, aggregate.arg()) + ")" };

		if (aggregate.hasAlias())
		{
			aggregateString += aggregate.aliasPtr()->sql(this);
		}

		//		String targetString{};

/*
		const auto selectablePtr = aggregate.selectable();
		targetString = selectablePtr->sql(this);

		if (!targetString.empty())
		{
			aggregateString = AggregateFunctionMap.at(aggregate.aggregateFunction())
				+ "(" + targetString + ")";

			if (aggregate.hasAlias())
			{
				aggregateString += aggregate.aliasPtr()->sql(this);
			}
		}
*/
		return aggregateString;
	}
}
