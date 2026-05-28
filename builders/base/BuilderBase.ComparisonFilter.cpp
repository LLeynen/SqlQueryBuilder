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
	/*
		struct FilterValueVisitor
		{
			FilterValueVisitor(const BuilderBase* builder, const Comparison comparison)
				: builder_{ builder }
				, comparison_{ comparison }
			{}

			const BuilderBase* builder_;
			const Comparison comparison_;

			// Type nullptr_t
			String operator()(const std::nullptr_t&) const
			{
				return (comparison_ == Comparison::Equals) ? "IS NULL" : "IS NOT NULL";
			}

			// Type Variant
			String operator()(const Variant& value) const
			{
				if (value.isNull())
				{
					return (*this)(nullptr);
				}
				else
				{
					return ComparisonMap.at(comparison_) + " " + value.sqlFormat();
				}
			}

			// Type Parameter
			String operator()(const Parameter& parameter) const
			{
					return ComparisonMap.at(comparison_) + " " + parameter.sql(builder_);
			}

			// Type ListOfValues
			String operator()(const ListOfValues& listOfValues) const
			{
				if (listOfValues.valueList().empty())
				{
					return (*this)(nullptr);
				}

				switch (comparison_)
				{
				case Comparison::In:
				case Comparison::NotIn:

					return ComparisonMap.at(comparison_) + " " + listOfValues.sql(builder_);

				case Comparison::Between:
					if (listOfValues.valueList().size() != 2)
					{
						throw std::runtime_error("ListOfValues for BETWEEN must contain exactly two values");
					}
					return ComparisonMap.at(comparison_)
						+ listOfValues.valueList().at(0).sqlFormat()
						+ " AND "
						+ listOfValues.valueList().at(1).sqlFormat();
				default:
					throw std::runtime_error("ListOfValues can only be used with IN, NOT IN, or BETWEEN comparisons");
				}
			}

			// Type Query
			String operator()(const Query& query) const
			{
				if (comparison_ != Comparison::In
					&& comparison_ != Comparison::NotIn
					&& comparison_ != Comparison::Exists
					&& comparison_ != Comparison::NotExists
					&& comparison_ != Comparison::Any
					&& comparison_ != Comparison::Some
					&& comparison_ != Comparison::All)
				{
					throw std::runtime_error("Query can only be used with IN, NOT IN, EXISTS, NOT EXISTS, ANY, SOME, or ALL comparisons");
				}
				else
				{
					return ComparisonMap.at(comparison_) + " (" + query.sql(builder_) + ")";
				}
			}

			// Type String
			String operator()(const String& value) const
			{
				const Variant variant{ value };
				return ComparisonMap.at(comparison_) + " " + variant.sqlFormat();
			}

			// Type const char*
			String operator()(const char* value) const
			{
				return (*this)(String{ value });
			}
		};
*/

    String BuilderBase::buildComponent(const ComparisonFilter& filter) const
    {
        String lhsString {};
        String rhsString {};

        const auto lhsSelectable = filter.lhs().get();
    	lhsString = (lhsSelectable) ? lhsSelectable->sql(this) : "";

        const auto rhsComparisonValue = filter.rhs();

        if (std::holds_alternative<Operand>(rhsComparisonValue))
        {
            const auto rhsValue = std::get<Operand>(rhsComparisonValue);
            rhsString = ComparisonMap.at(filter.comparison()) + rhsValue.get()->sql(this);
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
