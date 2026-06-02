// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import BuilderMariaDB;

import :BuilderTypes;
import :Table;

namespace DataAccessLayer::SqlQueryBuilder
{
	String toLower(String& str)
	{
		std::ranges::transform(str, str.begin(),
			[](const unsigned char c){ return std::tolower(c); });
		return str;
	}


	String BuilderMariaDB::buildComponent(const Table& table) const
	{
		if (table.name().empty())
		{
			return "";
		}
		else
		{
			const String tableName{ toLower(table.name()) };
			String tableString = engineParams_.startDelimiter
				+ tableName
				+ engineParams_.endDelimiter;
			return tableString;
		}
	}
}
