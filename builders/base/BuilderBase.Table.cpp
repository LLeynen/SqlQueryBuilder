// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :Table;

namespace DataAccessLayer::SqlQueryBuilder
{
	String BuilderBase::buildComponent(const Table& table) const
	{
		String tableString;

		if (table.tableName().empty())
		{
			return "";
		}
		else
		{
			const String tableName{ table.tableName() };

			if (table.tableName().find(' ') == npos)
			{
				tableString = tableName;
			}
			else
			{
				tableString = engineParams_.startDelimiter
					+ tableName
					+ engineParams_.endDelimiter;
			}
		}

		return tableString;
	}
}
