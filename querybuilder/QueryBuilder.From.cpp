// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderTypes;
import :Concepts;
//import :DataSource;
import :TableDataSource;
import :QueryDataSource;
import :Field;
import :Impl;

namespace DataAccessLayer::SqlQueryBuilder
{
	// QueryBuilder::from(DataSource)
	QueryBuilder& QueryBuilder::from(const DataSource& dataSource)
	{
		impl_->dataSourcePtr_ = dataSource.clone();
		return *this;
	}

	// QueryBuilder::from(table name)
	QueryBuilder& QueryBuilder::from(const String& tableName, std::optional<Alias> alias)
	{
		impl_->dataSourcePtr_ = std::make_shared<TableDataSource>(tableName, alias);
		return *this;
	}

	// QueryBuilder::from (QueryBuilder)
	QueryBuilder& QueryBuilder::from(const QueryBuilder& queryBuilder, std::optional<Alias> alias)
	{
		impl_->dataSourcePtr_ = std::make_shared<QueryDataSource>(queryBuilder, alias);
		return *this;
	}


	// QueryBuilder::join (JoinClause)
	QueryBuilder& QueryBuilder::join(const JoinClause& joinClause)
	{
		ensureSharedPtr(impl_->joinClauseListPtr_);

		impl_->joinClauseListPtr_->emplace_back(std::make_shared<JoinClause>(joinClause));
		return *this;
	}
	
	// QueryBuilder::join(primaryKey, comparison, foreignKey, joinType)
	QueryBuilder& QueryBuilder::join(const FieldRef& primaryKey, const Comparison comparison, const FieldRef& foreignKey, const JoinType joinType)
	{
		ensureSharedPtr(impl_->joinClauseListPtr_);

		Field local = primaryKey.get();
		Field foreign = foreignKey.get();
		JoinClause joinClause{ std::move(local), comparison, std::move(foreign), joinType };

		impl_->joinClauseListPtr_->emplace_back(std::make_shared<JoinClause>(joinClause));

		return *this;
	}
}
