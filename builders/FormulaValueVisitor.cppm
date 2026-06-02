// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:FormulaValueVisitor;

import std;

import :BuilderTypes;
import :Variant;
import :Parameter;

namespace DataAccessLayer::SqlQueryBuilder
{
	export struct FormulaValueVisitor
	{
		FormulaValueVisitor(const IBuilder* builder)
			: builder_{ builder }
		{}

		const IBuilder* builder_{};

		// Type nullptr_t
		String operator()(const std::nullptr_t&) const
		{
			return "NULL";
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
				return value.sqlFormat();
			}
		}

		// Type Parameter
		String operator()(const Parameter& parameter) const
		{
			return parameter.sql(builder_);
		}

		// Type String
		String operator()(const String& value) const
		{
			const Variant variant{ value };
			return variant.sqlFormat();
		}

		// Type const char*
		String operator()(const char* value) const
		{
			return (*this)(String{ value });
		}
	};
}