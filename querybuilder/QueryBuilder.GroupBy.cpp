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
	QueryBuilder& QueryBuilder::groupBy(FieldRef fieldRef)
	{
		ensureSharedPtr(impl_->groupByFieldListPtr_);

		impl_->groupByFieldListPtr_->push_back(std::make_shared<Field>(fieldRef.move()));

		return *this;
	}


	QueryBuilder& QueryBuilder::groupBy(const std::initializer_list<FieldRef> fieldRefList)
	{
		ensureSharedPtr(impl_->groupByFieldListPtr_);

		impl_->groupByFieldListPtr_->clear();

		for (auto& fieldRef : fieldRefList)
		{
			groupBy(fieldRef);
		}

		return *this;
	}


	QueryBuilder& QueryBuilder::groupBy(String tableName, const std::initializer_list<String> columnNameList)
	{
		ensureSharedPtr(impl_->groupByFieldListPtr_);

		impl_->groupByFieldListPtr_->clear();

		for (const auto& columnName : columnNameList)
		{
			groupBy(FieldRef( {tableName, columnName}));
		}

		return *this;
	}
}
