// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import :BuilderTypes;
import :Concepts;
import :Field;
import :Impl;

namespace DataAccessLayer::SqlQueryBuilder
{
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


	QueryBuilder& QueryBuilder::field(FieldRef fieldRef)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		impl_->selectableListPtr_->push_back(std::make_shared<Field>(fieldRef.move()));

		return *this;
	}


	QueryBuilder& QueryBuilder::field(FieldRef fieldRef, std::optional<Alias> alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		// 1. Move the Field straight into the shared pointer first
		auto fieldPtr = std::make_shared<Field>(fieldRef.move());

		// 2. Safely apply the alias via the inherited Selectable method!
		if (alias)
		{
			fieldPtr->setAlias(std::move(*alias));
		}

		impl_->selectableListPtr_->push_back(std::move(fieldPtr));


		return *this;
	}


	QueryBuilder& QueryBuilder::fields(const std::initializer_list<FieldRef> fieldRefList)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		for (auto& fieldRef : fieldRefList)
		{
			field(fieldRef);
		}

		return *this;
	}


	QueryBuilder& QueryBuilder::fields(String tableName, const std::initializer_list<String> columnNameList)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		String table = std::move(tableName);

		for (const auto& columnName : columnNameList)
		{
			this->field(Field(table, columnName));
		}

		return *this;
	}


	QueryBuilder& QueryBuilder::fields(std::initializer_list<const char*> flatNames)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		for (const auto* name : flatNames)
		{
			impl_->selectableListPtr_->push_back(std::make_unique<Field>(name));
		}

		return *this;
	}
}
