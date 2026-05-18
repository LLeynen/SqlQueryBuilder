// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderTypes;
import :Concepts;
import :Field;
import :Impl;

namespace DataAccessLayer::SqlQueryBuilder
{
	// QueryBuilder::groupBy(Field)
	QueryBuilder& QueryBuilder::groupBy(const FieldRef& fieldRef)
	{
		ensureSharedPtr(impl_->groupByFieldListPtr_);

		Field field = fieldRef.get();

		impl_->groupByFieldListPtr_->push_back(std::make_shared<Field>(std::move(field)));

		return *this;
	}

	// QueryBuilder::groupBy(columnName)
/*
	QueryBuilder& QueryBuilder::groupBy(const String& columnName)
	{
		ensureSharedPtr(impl_->groupByFieldListPtr_);
		impl_->groupByFieldListPtr_->push_back(std::make_shared<Field>(columnName));

		return *this;
	}
*/

	// QueryBuilder::groupBy(tableName, columnName)
	/*
	QueryBuilder& QueryBuilder::groupBy(const String& tableName, const String& columnName)
	{
		ensureSharedPtr(impl_->groupByFieldListPtr_);
		impl_->groupByFieldListPtr_->push_back(std::make_shared<Field>(tableName, columnName));

		return *this;
	}
*/

	// QueryBuilder::groupBy(FieldList)
	QueryBuilder& QueryBuilder::groupBy(std::initializer_list<FieldRef> fieldRefList)
	{
		ensureSharedPtr(impl_->groupByFieldListPtr_);
		impl_->groupByFieldListPtr_->clear();

		for (auto& fieldRef : fieldRefList)
		{
			field(fieldRef.get());
		}

		return *this;
	}

	// QueryBuilder::groupBy(tableName, columnNameList)
	QueryBuilder& QueryBuilder::groupBy(const String& tableName, std::initializer_list<String> columnNameList)
	{
		ensureSharedPtr(impl_->groupByFieldListPtr_);
		impl_->groupByFieldListPtr_->clear();

		for (const auto& columnName : columnNameList)
		{
			this->field(Field(tableName, columnName));
		}

		return *this;
	}
}
