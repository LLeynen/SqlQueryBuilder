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
	QueryBuilder& QueryBuilder::query(Query query)
	{
		ensureSharedPtr(impl_->queryListPtr_)->emplace_back(std::make_shared<Query>(std::move(query)));

		return *this;
	}


	QueryBuilder& QueryBuilder::query(String rawSql)
	{
		ensureSharedPtr(impl_->queryListPtr_)->emplace_back(std::make_shared<Query>(std::move(rawSql)));

		return *this;
	}


	QueryBuilder& QueryBuilder::query(QueryBuilder queryBuilder)
	{
		ensureSharedPtr(impl_->queryListPtr_)->emplace_back(std::make_shared<Query>(std::move(queryBuilder)));

		return *this;
	}


	QueryBuilder& QueryBuilder::queries(std::initializer_list<QueryBuilder> queryBuilderList)
	{
		for (auto& queryBuilder : queryBuilderList)
		{
			query(queryBuilder);
		}

		return *this;
	}
}
