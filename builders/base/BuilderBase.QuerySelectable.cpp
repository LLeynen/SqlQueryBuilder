// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :QuerySelectable;
import :String;

namespace DataAccessLayer::SqlQueryBuilder
{
	String BuilderBase::buildComponent(const QuerySelectable& querySelectable) const
	{
		String querySelectableString{ "(" + querySelectable.query()->sql() + ")" };

		if (querySelectable.hasAlias())
		{
			querySelectableString += buildComponent(*querySelectable.aliasPtr());
		}

		return querySelectableString;
	}
}
