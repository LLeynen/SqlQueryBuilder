// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import BuilderMariaDB;

import :BuilderTypes;
import :Field;
import :Table;

namespace DataAccessLayer::SqlQueryBuilder
{
	String BuilderMariaDB::buildComponent(const Field& field) const
	{
		String fieldString{};

		if (!field.tableName().empty())
		{
			fieldString = buildComponent(Table{ field.tableName() }) + ".";
		}

		fieldString += engineParams_.startDelimiter
			+ field.columnName()
			+ engineParams_.endDelimiter;

		if (field.hasAlias())
		{
			fieldString += field.aliasPtr()->sql(this);
		}

		return fieldString;
	}
}
