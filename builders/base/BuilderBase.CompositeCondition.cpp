// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import std;

import :BuilderTypes;
import :CompositeCondition;
import :EnumMaps;

namespace DataAccessLayer::SqlQueryBuilder
{
	String BuilderBase::buildComponent(const CompositeCondition& compositeCondition) const
	{
		String compositeConditionString{};
		const auto conditionBaseList = compositeCondition.conditionBaseList();

		for (size_t i = 0; i < conditionBaseList.size(); ++i)
		{
			if (i > 0)
			{
				compositeConditionString +=
					" " + LogicOperatorMap.at(compositeCondition.logicOperator()) + " ";
			}

			const auto& conditionBasePtr = conditionBaseList.at(i);
			compositeConditionString += "(" + conditionBasePtr->sql(this) + ")";
		}

		return compositeConditionString;
	}
}
