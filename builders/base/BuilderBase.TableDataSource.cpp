// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :TableDataSource;

namespace DataAccessLayer::SqlQueryBuilder
{
	String BuilderBase::buildComponent(const TableDataSource& tableDataSource) const
	{
		String tableDataSourceString{ tableDataSource.table()->sql(this) };

		if (tableDataSource.hasAlias())
		{
			tableDataSourceString += tableDataSource.aliasPtr()->sql(this);
		}

		return tableDataSourceString;
	}
}
