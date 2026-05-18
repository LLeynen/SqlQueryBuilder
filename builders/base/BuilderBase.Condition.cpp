// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import std;

import :BuilderTypes;
import :EnumMaps;
import :Variant;
import :Condition;
import :ListOfValues;
import :Parameter;
import :Field;
import :Query;

namespace DataAccessLayer::SqlQueryBuilder
{
	// ConditionVisitor
	struct ConditionVisitor
	{
		ConditionVisitor(const BuilderBase* builder, const Field& field, const Comparison comparison)
			: builder_{ builder }
			, field_{ field }
			, comparison_{ comparison }
		{}

		const BuilderBase* builder_;
		const Field& field_;
		const Comparison comparison_;

		String fieldString{ builder_->buildComponent(field_) };

		// Type nullptr_t
		String operator()(const std::nullptr_t&) const
		{
			if (comparison_ == Comparison::Equals)
			{
				return fieldString + " IS NULL";
			}
			else
			{
				return fieldString + " IS NOT NULL";
			}
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
				return fieldString + " " + ComparisonMap.at(comparison_) + " " + value.sqlFormat();
			}
		}

		// Type Parameter
		String operator()(const Parameter& parameter) const
		{
			return fieldString + " "
				+ ComparisonMap.at(comparison_) + " "
				+ builder_->buildComponent(parameter);
		}

		// Type Field
		String operator()(const Field& field) const
		{
			return fieldString + " " + ComparisonMap.at(comparison_) + " " + builder_->buildComponent(field);
		}

		// Type SqlListOfValues
		String operator()(ListOfValues& listOfValues) const
		{
			if (listOfValues.valueList().empty())
			{
				return (*this)(nullptr);
			}
			else
			{
				switch (comparison_)
				{
				case Comparison::In:
				case Comparison::NotIn:

					return fieldString + " " + ComparisonMap.at(comparison_) + " " + builder_->buildComponent(listOfValues);

				case Comparison::Between:
					if (listOfValues.valueList().size() != 2)
					{
						throw std::runtime_error("ListOfValues for BETWEEN must contain exactly two values");
					}
					return fieldString + " " + ComparisonMap.at(comparison_) + " "
						+ listOfValues.valueList().at(0).sqlFormat()
						+ " AND "
						+ listOfValues.valueList().at(1).sqlFormat();
				default:
					throw std::runtime_error("ListOfValues can only be used with IN, NOT IN, or BETWEEN comparisons");
				}
			}
		}

		// Type Query
		String operator()(Query& query) const
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
				return fieldString + " "
					+ ComparisonMap.at(comparison_) + " ("
					+ builder_->buildComponent(query) + ")";
			}
		}

		// Type String
		String operator()(const String& value) const
		{
			const Variant variant{ value };
			return fieldString + " " + ComparisonMap.at(comparison_) + " " + variant.sqlFormat();
		}

		// Type const char*
		String operator()(const char* value) const
		{
			return (*this)(String{ value });
		}
	};


	String BuilderBase::buildComponent(const Condition& condition) const
	{
		ConditionVariant conditionValue{ condition.conditionValue() };
		ConditionVisitor visitor(this, condition.field(), condition.comparison());

		String conditionString{ std::visit(visitor, conditionValue) };

		return conditionString;
	}
}
