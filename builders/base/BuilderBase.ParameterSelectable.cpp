// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :ParameterSelectable;
import :String;

namespace DataAccessLayer::SqlQueryBuilder
{
	String BuilderBase::buildComponent(const ParameterSelectable& parameterSelectable) const
	{
//		String stringParameterSelectable { parameterSelectable.sql() };

		String stringParameterSelectable { buildComponent(*parameterSelectable.parameterPtr()) };

		if (parameterSelectable.hasAlias())
		{
			stringParameterSelectable += buildComponent(*parameterSelectable.aliasPtr());
		}

		return stringParameterSelectable;
	}
}
