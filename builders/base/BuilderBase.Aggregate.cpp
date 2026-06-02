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
		if (const auto arg { aggregate.arg() }; std::holds_alternative<Operand>(arg))
		{
			if (const auto selectablePtr = std::get<Operand>(arg).get())
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

		return aggregateString;
	}
}
