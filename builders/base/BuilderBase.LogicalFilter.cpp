// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import std;

import :BuilderTypes;
import :EnumMaps;
import :LogicalFilter;

namespace DataAccessLayer::SqlQueryBuilder
{
    String BuilderBase::buildComponent(const LogicalFilter& filter) const
    {
        if (filter.logicOperator() == LogicOperator::Not)
        {
            const String rhsString = (filter.rhs()) ? filter.rhs()->sql(this) : "";
            return LogicOperatorMap.at(LogicOperator::Not) + " (" + rhsString + ")";
        }
        else
        {
            const String lhsString = (filter.lhs()) ? filter.lhs()->sql(this) : "";
            const String rhsString = (filter.rhs()) ? filter.rhs()->sql(this) : "";
            return "(" + lhsString + " " + LogicOperatorMap.at(filter.logicOperator()) + " " + rhsString + ")";
        }
    }
}
