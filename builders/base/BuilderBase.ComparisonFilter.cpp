// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import std;

import :BuilderTypes;
import :EnumMaps;
import :ComparisonFilter;
import :FilterValueVisitor;

namespace DataAccessLayer::SqlQueryBuilder
{
    String BuilderBase::buildComponent(const ComparisonFilter& filter) const
    {
        const auto lhsSelectable { filter.lhs().get()};
    	const String lhsString { (lhsSelectable) ? lhsSelectable->sql(this) : "" };

        String rhsString {};
        if (const auto rhsComparisonValue = filter.rhs(); std::holds_alternative<Operand>(rhsComparisonValue))
        {
        	const auto rhsValue = std::get<Operand>(rhsComparisonValue);
            rhsString = ComparisonMap.at(filter.comparison()) + " " + rhsValue.get()->sql(this);
        }
        else if (std::holds_alternative<FilterValue>(rhsComparisonValue))
        {
        	const auto filterValue = std::get<FilterValue>(rhsComparisonValue);
			rhsString = std::visit(FilterValueVisitor{ this, filter.comparison()}, filterValue);
        }

    	String comparisonFilterString {};
    	if (filter.mode() == ConditionMode::Comparison)
    	{
    		comparisonFilterString = lhsString + " " + rhsString;
    	}
        else
        {
        	comparisonFilterString = lhsString.empty() ? rhsString : lhsString + " " + rhsString;
        }

    	return comparisonFilterString;
    }
}
