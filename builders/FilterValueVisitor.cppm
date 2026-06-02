// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:FilterValueVisitor;

import std;

import :BuilderTypes;
import :EnumMaps;
import :ListOfValues;
import :Parameter;
import :Query;

namespace DataAccessLayer::SqlQueryBuilder
{
	namespace
	{
		Comparison validateComparison(const IBuilder* builder, Comparison comparison, const String& sqlValue)
		{
			if (comparison == Comparison::Equals)
			{
				const bool hasWildcard =
					(sqlValue.find(builder->engineParams_.MatchAll) != String::npos) ||
					(sqlValue.find(builder->engineParams_.MatchSingle) != String::npos);

				if (hasWildcard)
				{
					return Comparison::Like;
				}
			}

			return comparison;
		}
	}

	struct FilterValueVisitor
		{
			FilterValueVisitor(const IBuilder* builder, const Comparison comparison)
				: builder_{ builder }
				, comparison_{ comparison }
			{}

			const IBuilder* builder_{};
			const Comparison comparison_{};

			// nullptr_t
			String operator()(const std::nullptr_t&) const
			{
				return (comparison_ == Comparison::Equals) ? "IS NULL" : "IS NOT NULL";
			}

			// Variant
			String operator()(const Variant& value) const
			{
				if (value.isNull())
				{
					return (*this)(nullptr);
				}
				else
				{
					const String sqlValue { value.sqlFormat() };
					Comparison comparison { validateComparison(builder_, comparison_, sqlValue) };

					return ComparisonMap.at(comparison) + " " + sqlValue;
				}
			}

			// Parameter
			String operator()(const Parameter& parameter) const
			{
				String sqlValue{ parameter.sql(builder_) };
				Comparison comparison { validateComparison(builder_, comparison_, sqlValue) };

				return ComparisonMap.at(comparison) + " " + sqlValue;
			}

			// ListOfValues
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

			// Query
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

			// String
			String operator()(const String& value) const
			{
				const Variant variant{ value };
				const String sqlValue{ variant.sqlFormat() };

				Comparison comparison { validateComparison(builder_, comparison_, sqlValue) };

				return ComparisonMap.at(comparison) + " " + sqlValue;
			}

			// const char*
			String operator()(const char* value) const
			{
				return (*this)(String{ value });
			}
		};
}