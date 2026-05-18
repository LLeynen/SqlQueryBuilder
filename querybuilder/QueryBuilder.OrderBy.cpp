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
	// QueryBuilder::orderBy(Field, SortOrder)
	QueryBuilder& QueryBuilder::orderBy(const FieldRef& fieldRef, SortOrder sortOrder)
	{
		ensureSharedPtr(impl_->orderByClauseListPtr_);

		Field field = fieldRef.get();

		impl_->orderByClauseListPtr_->emplace_back(std::make_shared<OrderByClause>(std::move(field), sortOrder));

		return *this;
	}

	// QueryBuilder::orderBy(columnName, SortOrder)
/*
	QueryBuilder& QueryBuilder::orderBy(const String& columnmName, SortOrder sortOrder)
	{
		return orderBy(Field(columnmName), sortOrder);
	}
*/

	// QueryBuilder::orderBy(tableName, columnName, SortOrder)
	/*
	SqlQueryBuilder::QueryBuilder& QueryBuilder::orderBy(const String& tableName, const String& columnName, SortOrder sortOrder)
	{
		return orderBy(Field(tableName, columnName), sortOrder);
	}
*/

	// QueryBuilder::OrderBy(FieldList)
	QueryBuilder& QueryBuilder::orderBy(FieldList& fieldList, SortOrder sortOrder)
	{
		for (const auto& fieldPtr : fieldList)
		{
			orderBy(*fieldPtr, sortOrder);
		}

		return *this;
	}

	// QueryBuilder::orderBy(tableName, columnNameList)
	QueryBuilder& QueryBuilder::orderBy(const String& tableName, std::initializer_list<String> columnNameList, SortOrder sortOrder)
	{
		for (const auto& columnName : columnNameList)
		{
			Field field{ tableName, columnName };
			orderBy(field, sortOrder);
		}

		return *this;
	}

	// QueryBuilder::orderBy(columnNameList)
	QueryBuilder& QueryBuilder::orderBy(std::initializer_list<String> columnNameList, SortOrder sortOrder)
	{
		for (const auto& columnName : columnNameList)
		{
			Field field{ columnName };
			orderBy(field, sortOrder);
		}

		return *this;
	}
}
