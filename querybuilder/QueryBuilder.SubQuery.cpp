// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import :BuilderTypes;
import :Concepts;
import :QuerySelectable;
import :Impl;
namespace DataAccessLayer::SqlQueryBuilder
{
	QueryBuilder& QueryBuilder::subQuery(QueryBuilder queryBuilder, std::optional<Alias> alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		auto querySelectable = std::make_shared<QuerySelectable>(std::move(queryBuilder), std::move(alias));

		impl_->selectableListPtr_->push_back(std::move(querySelectable));

		return *this;
	}


	QueryBuilder& QueryBuilder::subQuery(Query query, std::optional<Alias> alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		if (auto querySource = query.querySource(); std::holds_alternative<QueryBuilderPtr>(querySource))
		{
			auto queryBuilderPtr = std::get<QueryBuilderPtr>(querySource);
			auto querySelectable = std::make_shared<QuerySelectable>(queryBuilderPtr, std::move(alias));
			impl_->selectableListPtr_->push_back(std::move(querySelectable));
		}
		else if (std::holds_alternative<String>(querySource))
		{
			auto rawSql = std::get<String>(querySource);
			auto querySelectable = std::make_shared<QuerySelectable>(rawSql, std::move(alias));
			impl_->selectableListPtr_->push_back(std::move(querySelectable));
		}

		return *this;
	}


	QueryBuilder& QueryBuilder::subQuery(String rawSql, std::optional<Alias> alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		auto querySelectable = std::make_shared<QuerySelectable>(std::move(rawSql), std::move(alias));

		impl_->selectableListPtr_->push_back(std::move(querySelectable));

		return *this;
	}
}