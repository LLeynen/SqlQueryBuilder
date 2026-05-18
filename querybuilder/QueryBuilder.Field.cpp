// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import :BuilderTypes;
import :Concepts;
import :Field;
import :QuerySelectable;
import :Impl;

// TODO VERSIONS WITH ALIAS

namespace DataAccessLayer::SqlQueryBuilder
{
	// QueryBuilder::allFields
	QueryBuilder& QueryBuilder::allFields(std::optional<String> tableName)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		Field field{};

		if (tableName.has_value())
		{
			field.setTableName(std::move(tableName.value()));
		}

		field.setColumnName("*");

		impl_->selectableListPtr_->push_back(std::make_shared<Field>(field));

		return *this;
	}

	// QueryBuilder::field(Field)
	QueryBuilder& QueryBuilder::field(const FieldRef& fieldRef)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		impl_->selectableListPtr_->push_back(std::make_shared<Field>(fieldRef.move()));

		return *this;
	}

	// QueryBuilder::field(columnName)
/*
	QueryBuilder& QueryBuilder::field(const String& columnName)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		Field field{ columnName };
		impl_->selectableListPtr_->push_back(std::make_shared<Field>(field));

		return *this;
	}
*/
	// QueryBuilder::field(tableName, columnName)
/*
	QueryBuilder& QueryBuilder::field(const String& tableName, const String& columnName)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		Field field{ tableName, columnName };
		impl_->selectableListPtr_->push_back(std::make_shared<Field>(field));

		return *this;
	}
*/

	/*
	// QueryBuilder::field(tableName, columnName, alias)
	QueryBuilder& QueryBuilder::field(const String& tableName, const String& columnName, const String& alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		Field field{ tableName, columnName, alias };
		impl_->selectableListPtr_->push_back(std::make_shared<Field>(field));

		return *this;
	}
*/


	// QueryBuilder::fields(initializer list)
	QueryBuilder& QueryBuilder::fields(std::initializer_list<FieldRef> fieldRefList)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		for (auto& fieldRef : fieldRefList)
		{
			field(fieldRef.get());
		}

		return *this;
	}


	// QueryBuilder::fields(table, columnNameList)
	QueryBuilder& QueryBuilder::fields(const String& tableName, std::initializer_list<String> columnNameList)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		for (const auto& columnName : columnNameList)
		{
			this->field(Field(tableName, columnName));
		}

		return *this;
	}

	// QueryBuilder::field(subQuery, alias)
	QueryBuilder& QueryBuilder::field(const QueryBuilder& queryBuilder, std::optional<Alias> alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		auto querySelectable = std::make_shared<QuerySelectable>(queryBuilder, alias);

//		QuerySelectable query{ queryBuilder, alias };
		impl_->selectableListPtr_->push_back(std::move(querySelectable));

		return *this;
	}


	QueryBuilder& QueryBuilder::field(const String& parameterName, std::optional<Alias> alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		const auto parameterSelectable = std::make_shared<ParameterSelectable>(parameterName, alias);

		impl_->selectableListPtr_->push_back(parameterSelectable);

		return *this;
	}
}
