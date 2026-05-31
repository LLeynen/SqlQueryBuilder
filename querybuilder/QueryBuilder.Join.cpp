// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import :BuilderTypes;
import :Concepts;
//import :DataSource;
import :TableDataSource;
import :QueryDataSource;
import :Field;
import :Impl;

namespace DataAccessLayer::SqlQueryBuilder
{
	// QueryBuilder::join (JoinClause)
	QueryBuilder& QueryBuilder::join(const JoinClause& joinClause)
	{
		ensureSharedPtr(impl_->joinClauseListPtr_);

		impl_->joinClauseListPtr_->emplace_back(std::make_shared<JoinClause>(joinClause));
		return *this;
	}

	// QueryBuilder::join(primaryKey, comparison, foreignKey, joinType)
	QueryBuilder& QueryBuilder::join(FieldRef primaryKey, const Comparison comparison, FieldRef foreignKey, const JoinType joinType)
	{
		ensureSharedPtr(impl_->joinClauseListPtr_);

		Field local = primaryKey.move();
		Field foreign = foreignKey.move();

		std::cout << "QueryBuilder::Join " << std::endl;
		std::cout << "Local = " <<  local.sql() << std::endl;;
		std::cout << "Foreign = " <<  foreign.sql() << std::endl;;

		JoinClause joinClause{ local, comparison, foreign, joinType };

		impl_->joinClauseListPtr_->emplace_back(std::make_shared<JoinClause>(std::move(joinClause)));

		return *this;
	}
}
