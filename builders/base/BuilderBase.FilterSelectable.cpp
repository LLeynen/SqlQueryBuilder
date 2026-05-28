// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :FilterSelectable;
import :String;

namespace DataAccessLayer::SqlQueryBuilder
{
	String BuilderBase::buildComponent(const FilterSelectable& filterSelectable) const
	{
		String stringFilterSelectable = filterSelectable.filter()->sql(this);

		if (filterSelectable.hasAlias())
		{
			stringFilterSelectable += filterSelectable.aliasPtr()->sql(this);
		}

		return stringFilterSelectable;
	}
}
