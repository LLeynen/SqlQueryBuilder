// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderTypes;
//import :Concepts;
import :TableDataSource;
import :QueryDataSource;
import :Impl;

namespace DataAccessLayer::SqlQueryBuilder
{
	QueryBuilder& QueryBuilder::from(const DataSource& dataSource)
	{
		impl_->dataSourcePtr_ = dataSource.clone();
		return *this;
	}

	QueryBuilder& QueryBuilder::from(String tableName, std::optional<Alias> alias)
	{
		impl_->dataSourcePtr_ = std::make_shared<TableDataSource>(std::move(tableName), std::move(alias));
		return *this;
	}


	QueryBuilder& QueryBuilder::from(QueryBuilder queryBuilder, std::optional<Alias> alias)
	{
		impl_->dataSourcePtr_ = std::make_shared<QueryDataSource>(std::move(queryBuilder), std::move(alias));
		return *this;
	}
}
