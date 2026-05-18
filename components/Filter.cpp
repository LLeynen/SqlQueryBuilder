// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :Filter;

import std;

import :BuilderTypes;
import :Component;
import :IBuilder;
import :ConditionBase;

namespace DataAccessLayer::SqlQueryBuilder
{
	class FilterImpl
	{
		public:
			FilterImpl() = default;
			FilterImpl(const ConditionBase& condition)
				: conditionBasePtr_{ condition.clone() }
			{}
			~FilterImpl() = default;

			FilterImpl(const FilterImpl&) = default;
			FilterImpl& operator=(const FilterImpl&) = default;
			FilterImpl(FilterImpl&&) = default;
			FilterImpl& operator=(FilterImpl&&) = default;

			ConditionBasePtr conditionBasePtr_;
	};

	// Filter::Filter
	Filter::Filter() noexcept
		: Component(ComponentId::Filter)
		, impl_{ std::make_unique<FilterImpl>() }
	{}

	// Filter::Filter(condition)
	Filter::Filter(const ConditionBase& condition)
		: Component(ComponentId::Filter)
		, impl_{ std::make_unique<FilterImpl>(condition) }
	{}

	// Filter::~Filter
	Filter::~Filter() = default;

	// Filter::Filter(Filter&)
	Filter::Filter(const Filter& other)
		: Component(other)
		, impl_{ std::make_unique<FilterImpl>(*other.impl_) }
	{}

	// Filter::operator=(Filter&)
	Filter& Filter::operator=(const Filter& other)
	{
		if (this != &other)
		{
			Component::operator=(other);
			impl_ = std::make_unique<FilterImpl>(*other.impl_);
		}

		return *this;
	}

	// Filter::Filter(Filter&&)
	Filter::Filter(Filter&& other) noexcept
		: Component(std::move(other))
		, impl_{ std::move(other.impl_) }
	{}

	// Filter::operator=(Filter&&)
	Filter& Filter::operator=(Filter&& other) noexcept
	{
		if (this != &other)
		{
			Component::operator=(std::move(other));
			impl_ = std::move(other.impl_);
		}

		return *this;
	}

	// Filter::conditionBase
	ConditionBasePtr Filter::conditionBase() const noexcept
	{
		return impl_->conditionBasePtr_;
	}

	// Filter::setCondition
	void Filter::setCondition(const ConditionBase& conditionBase)
	{
		impl_->conditionBasePtr_ = (conditionBase.clone());
	}

	// Filter::clear
	void Filter::clear() noexcept
	{
		impl_->conditionBasePtr_.reset();
	}

	// Filter::toSql
	String Filter::toSql(const IBuilder* builderPtr) const
	{
		return Component::sqlImpl(builderPtr, *this);
	}
}
