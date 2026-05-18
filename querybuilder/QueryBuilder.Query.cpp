// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import :BuilderTypes;
import :Concepts;
import :Impl;

import :QueryDataSource;

namespace DataAccessLayer::SqlQueryBuilder
{
	// QueryBuilder::query(Query&)
	QueryBuilder& QueryBuilder::query(Query query)
	{
		ensureSharedPtr(impl_->queryListPtr_)->emplace_back(std::make_shared<Query>(query));

		return *this;
	}

	// QueryBuilder::query(string, alias)
	QueryBuilder& QueryBuilder::query(const String& rawSql)
	{
		ensureSharedPtr(impl_->queryListPtr_)->emplace_back(std::make_shared<Query>(rawSql));

		return *this;
	}

	// QueryBuilder::query(QueryBuilder, alias)
	QueryBuilder& QueryBuilder::query(const QueryBuilder& queryBuilder)
	{
		ensureSharedPtr(impl_->queryListPtr_)->emplace_back(std::make_shared<Query>(queryBuilder));

		return *this;
	}

	// QueryBuilder::queries(QueryBuilder list)
	QueryBuilder& QueryBuilder::queries(std::initializer_list<QueryBuilder> queryBuilderList)
	{
		for (auto& queryBuilder : queryBuilderList)
		{
			query(queryBuilder);
		}

		return *this;
	}
}
