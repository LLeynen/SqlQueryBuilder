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
	QueryBuilder& QueryBuilder::values(ListOfValues values)
	{
		ensureSharedPtr(impl_->listOfValuesPtr_);

		impl_->listOfValuesPtr_ = std::make_shared<ListOfValues>(std::move(values));

		return *this;
	}


	QueryBuilder& QueryBuilder::values(const std::initializer_list<Variant> valueList)
	{
		ensureSharedPtr(impl_->listOfValuesPtr_);

		impl_->listOfValuesPtr_->valueList().clear();
		impl_->listOfValuesPtr_->setValueList(valueList);

		return *this;
	}


	QueryBuilder& QueryBuilder::values(VariantList valueList)
	{
		ensureSharedPtr(impl_->listOfValuesPtr_);

		impl_->listOfValuesPtr_->valueList().clear();
		impl_->listOfValuesPtr_->setValueList(std::move(valueList));

		return *this;
	}


	QueryBuilder& QueryBuilder::appendValue(Variant value)
	{
		ensureSharedPtr(impl_->listOfValuesPtr_)->appendValue(std::move(value));

		return *this;
	}


	QueryBuilder& QueryBuilder::appendValues(VariantList valueList)
	{
		ensureSharedPtr(impl_->listOfValuesPtr_)->appendValues(std::move(valueList));

		return *this;
	}


	QueryBuilder& QueryBuilder::appendValues(const std::initializer_list<Variant> valueList)
	{
		ensureSharedPtr(impl_->listOfValuesPtr_)->appendValues(valueList);

		return *this;
	}
}
