// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :Literal;

namespace DataAccessLayer::SqlQueryBuilder
{
	String BuilderBase::buildComponent(const Literal& literal) const
	{
		String literalString{ literal.value().toString() };

		if (literal.hasAlias())
		{
			literalString += buildComponent(*literal.aliasPtr());
		}

		return literalString;
	}
}
