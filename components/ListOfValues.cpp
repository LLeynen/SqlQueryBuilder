// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :ListOfValues;

import std;

import :BuilderTypes;
import :Selectable;
import :Variant;

namespace DataAccessLayer::SqlQueryBuilder
{
	class ListOfValuesImpl
	{
		public:
			ListOfValuesImpl() = default;
			ListOfValuesImpl(VariantList  valueList)
				: valueList_{std::move( valueList )}
			{}
			ListOfValuesImpl(const std::initializer_list<Variant> valueList)
				: valueList_(valueList)
			{}
			~ListOfValuesImpl() = default;

			ListOfValuesImpl(const ListOfValuesImpl& other) = default;
			ListOfValuesImpl& operator=(const ListOfValuesImpl& other) = default;
			ListOfValuesImpl(ListOfValuesImpl&& other) noexcept = default;
			ListOfValuesImpl& operator=(ListOfValuesImpl&& other) noexcept = default;

			VariantList valueList_{};
	};

	ListOfValues::ListOfValues()
		: Selectable(ComponentId::ListOfValues)
		, impl_{ std::make_unique<ListOfValuesImpl>() }
	{}
	

	ListOfValues::ListOfValues(VariantList valueList)
		: Selectable(ComponentId::ListOfValues)
		, impl_{ std::make_unique<ListOfValuesImpl>(std::move(valueList)) }
	{}


	ListOfValues::ListOfValues(std::initializer_list<Variant> valueList)
		: Selectable(ComponentId::ListOfValues)
		, impl_{ std::make_unique<ListOfValuesImpl>(valueList) }
	{}


	ListOfValues::~ListOfValues() = default;


	ListOfValues::ListOfValues(const ListOfValues& other)
		: Selectable(other)
		, impl_{ std::make_unique<ListOfValuesImpl>(*other.impl_) }
	{}


	ListOfValues& ListOfValues::operator=(const ListOfValues& other)
	{
		if (this != &other)
		{
			Selectable::operator=(other);
			impl_ = std::make_unique<ListOfValuesImpl>(*other.impl_);
		}

		return *this;
	}


	ListOfValues::ListOfValues(ListOfValues&& other) noexcept
		: Selectable(std::move(other))
		, impl_{ std::move(other.impl_) }
	{}


	ListOfValues& ListOfValues::operator=(ListOfValues&& other) noexcept
	{
		if (this != &other)
		{
			Selectable::operator=(std::move(other));
			impl_ = std::move(other.impl_);
		}

		return *this;
	}


	VariantList ListOfValues::valueList() const
	{
		return impl_->valueList_;
	}


	void ListOfValues::setValueList(VariantList valueList) const
	{
		impl_->valueList_.clear();
		impl_->valueList_ = std::move(valueList);
	}


	void ListOfValues::setValueList(const std::initializer_list<Variant> valueList) const
	{
		impl_->valueList_.clear();
		impl_->valueList_ = valueList;
	}


	void ListOfValues::appendValue(Variant value) const
	{
		impl_->valueList_.emplace_back(std::move(value));
	}


	void ListOfValues::appendValues(VariantList valueList) const
	{
		impl_->valueList_.insert(impl_->valueList_.end(), valueList.begin(), valueList.end());
	}


	void ListOfValues::appendValues(const std::initializer_list<Variant> valueList) const
	{
		impl_->valueList_.insert(impl_->valueList_.end(), valueList.begin(), valueList.end());
	}


	Variant ListOfValues::operator[](const size_t index)
	{
		return impl_->valueList_.at(index);
	}


	Variant ListOfValues::operator[](const size_t index) const
	{
		return impl_->valueList_.at(index);
	}


	SelectablePtr ListOfValues::clone() const
	{
		return std::make_shared<ListOfValues>(*this);
	}


	String ListOfValues::toSql(const IBuilder* builderPtr) const
	{
		return Component::sqlImpl(builderPtr, *this);
	}
}
