// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import :BuilderTypes;
import :Concepts;
import :Impl;

namespace DataAccessLayer::SqlQueryBuilder
{
	QueryBuilder& QueryBuilder::values(const ListOfValues& values)
	{
		ensureSharedPtr(impl_->listOfValuesPtr_);

		impl_->listOfValuesPtr_ = std::make_shared<ListOfValues>(ListOfValues());

		return *this;
	}

	// QueryBuilder::values(initializer_list)
	QueryBuilder& QueryBuilder::values(std::initializer_list<Variant> valueList)
	{
		ensureSharedPtr(impl_->listOfValuesPtr_);

		impl_->listOfValuesPtr_->valueList().clear();
		impl_->listOfValuesPtr_->setValueList(valueList);

		return *this;
	}

	// QueryBuilder::values(VariantList)
	QueryBuilder& QueryBuilder::values(const VariantList& valueList)
	{
		ensureSharedPtr(impl_->listOfValuesPtr_);

		impl_->listOfValuesPtr_->valueList().clear();
		impl_->listOfValuesPtr_->setValueList(valueList);

		return *this;
	}

	// QueryBuilder::appendValue
	QueryBuilder& QueryBuilder::appendValue(const Variant& value)
	{
		ensureSharedPtr(impl_->listOfValuesPtr_)->appendValue(value);

		return *this;
	}

	// QueryBuilder::appendValues(VariantList)
	QueryBuilder& QueryBuilder::appendValues(const VariantList& valueList)
	{
		ensureSharedPtr(impl_->listOfValuesPtr_)->appendValues(valueList);

		return *this;
	}

	// QueryBuilder::appendValues(initializer_list)
	QueryBuilder& QueryBuilder::appendValues(std::initializer_list<Variant> valueList)
	{
		ensureSharedPtr(impl_->listOfValuesPtr_)->appendValues(valueList);

		return *this;
	}
}
