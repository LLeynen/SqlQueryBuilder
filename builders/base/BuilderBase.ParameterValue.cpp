// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :Parameter;
import :Variant;

namespace DataAccessLayer::SqlQueryBuilder
{
	// BuilderBase::buildComponent(Parameter)
	String BuilderBase::buildComponent(const ParameterValue& parameter) const
	{
		String parameterValueString{ parameter.value().sqlFormat() };

		return parameterValueString;
	}
}
