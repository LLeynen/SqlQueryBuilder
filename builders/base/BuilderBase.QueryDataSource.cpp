// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :QueryDataSource;
import :String;

namespace DataAccessLayer::SqlQueryBuilder
{
	String BuilderBase::buildComponent(const QueryDataSource& queryDataSource) const
	{
		String queryDataSourceString{ "(" + queryDataSource.query()->sql(this) + ")" };

		if (queryDataSource.hasAlias())
		{
//			queryDataSourceString += buildComponent(*queryDataSource.aliasPtr());
			queryDataSourceString += queryDataSource.aliasPtr()->sql(this);
		}

		return queryDataSourceString;
	}
}
