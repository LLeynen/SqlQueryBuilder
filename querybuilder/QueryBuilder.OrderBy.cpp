// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderTypes;
import :Concepts;
import :Field;
import :OrderByClause;
import :Impl;

namespace DataAccessLayer::SqlQueryBuilder
{
	QueryBuilder& QueryBuilder::orderBy(FieldRef fieldRef, const SortOrder sortOrder)
	{
		ensureSharedPtr(impl_->orderByClauseListPtr_);

		impl_->orderByClauseListPtr_->emplace_back(std::make_shared<OrderByClause>(fieldRef.move(), sortOrder));

		return *this;
	}


	QueryBuilder& QueryBuilder::orderBy(String tableName, const std::initializer_list<String> columnNameList, const SortOrder sortOrder)
	{
		String table = std::move(tableName);

		for (const auto& columnName : columnNameList)
		{
			Field field{ table, columnName };
			orderBy(std::move(field), sortOrder);
		}

		return *this;
	}


	QueryBuilder& QueryBuilder::orderBy(const std::initializer_list<FieldRef> fieldRefList, const SortOrder sortOrder)
	{
		for (const auto& fieldRef : fieldRefList)
		{
			orderBy(std::move(fieldRef), sortOrder);
		}

		return *this;
	}
}
