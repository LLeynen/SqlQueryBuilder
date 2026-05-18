// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :ListOfValues;

import std;

import :BuilderTypes;
import :Component;
import :IBuilder;

namespace DataAccessLayer::SqlQueryBuilder
{
	class ListOfValuesImpl
	{
		public:
			ListOfValuesImpl() = default;
			ListOfValuesImpl(VariantList  valueList)
				: valueList_{std::move( valueList )}
			{}
			ListOfValuesImpl(std::initializer_list<Variant> valueList)
				: valueList_(valueList)
			{}
			~ListOfValuesImpl() = default;

			ListOfValuesImpl(const ListOfValuesImpl& other) = default;
			ListOfValuesImpl& operator=(const ListOfValuesImpl& other) = default;
			ListOfValuesImpl(ListOfValuesImpl&& other) noexcept = default;
			ListOfValuesImpl& operator=(ListOfValuesImpl&& other) noexcept = default;

			VariantList valueList_{};
	};

	// ListOfValues::ListOfValues
	ListOfValues::ListOfValues()
		: Component(ComponentId::ListOfValues)
		, impl_{ std::make_unique<ListOfValuesImpl>() }
	{}
	
	// ListOfValues::ListOfValues(vector)
	ListOfValues::ListOfValues(const VariantList& valueList)
		: Component(ComponentId::ListOfValues)
		, impl_{ std::make_unique<ListOfValuesImpl>(valueList) }
	{}

	// ListOfValues::ListOfValues(initializer_list)
	ListOfValues::ListOfValues(std::initializer_list<Variant> valueList)
		: Component(ComponentId::ListOfValues)
		, impl_{ std::make_unique<ListOfValuesImpl>(valueList) }
	{}

	// ListOfValues::~ListOfValues
	ListOfValues::~ListOfValues() = default;

	// ListOfValues::ListOfValues(ListOfValues&)
	ListOfValues::ListOfValues(const ListOfValues& other)
		: Component(other)
		, impl_{ std::make_unique<ListOfValuesImpl>(*other.impl_) }
	{}

	// ListOfValues::operator=(ListOfValues&)
	ListOfValues& ListOfValues::operator=(const ListOfValues& other)
	{
		if (this != &other)
		{
			Component::operator=(other);
			impl_ = std::make_unique<ListOfValuesImpl>(*other.impl_);
		}

		return *this;
	}

	// ListOfValues::ListOfValues(ListOfValues&&)
	ListOfValues::ListOfValues(ListOfValues&& other) noexcept
		: Component(std::move(other))
		, impl_{ std::move(other.impl_) }
	{}

	// ListOfValues::operator=(ListOfValues&&)
	ListOfValues& ListOfValues::operator=(ListOfValues&& other) noexcept
	{
		if (this != &other)
		{
			Component::operator=(std::move(other));
			impl_ = std::move(other.impl_);
		}

		return *this;
	}

	// ListOfValues::valueList
	VariantList ListOfValues::valueList() const
	{
		return impl_->valueList_;
	}

	// ListOfValues::setValueList(vector)
	void ListOfValues::setValueList(const VariantList& valueList)
	{
		impl_->valueList_.clear();
		impl_->valueList_ = valueList;
	}

	// ListOfValues::setValueList(initializer_list)
	void ListOfValues::setValueList(std::initializer_list<Variant> valueList)
	{
		impl_->valueList_.clear();
		impl_->valueList_ = valueList;
	}

	// ListOfValues::appendValue
	void ListOfValues::appendValue(const Variant& value)
	{
		impl_->valueList_.emplace_back(value);
	}

	// LisOfValues::appendValues
	void ListOfValues::appendValues(const VariantList& valueList)
	{
		impl_->valueList_.insert(impl_->valueList_.end(), valueList.begin(), valueList.end());
	}

	// ListOfValues::appendValues
	void ListOfValues::appendValues(std::initializer_list<Variant> valueList)
	{
		impl_->valueList_.insert(impl_->valueList_.end(), valueList.begin(), valueList.end());
	}

	// ListOfValues::operator[]  for set and get, non const
	Variant& ListOfValues::operator[](size_t index)
	{
		return impl_->valueList_.at(index);
	}

	// operator[] get only, const
	const Variant& ListOfValues::operator[](size_t index) const
	{
		return impl_->valueList_.at(index);
	}

	// ListOfValues::toSql
	String ListOfValues::toSql(const IBuilder* builderPtr) const
	{
		return Component::sqlImpl(builderPtr, *this);
	}
}
