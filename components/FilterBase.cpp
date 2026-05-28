// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :FilterBase;

import :BuilderTypes;

namespace DataAccessLayer::SqlQueryBuilder
{
	class FilterBaseImpl
	{
	public:
		FilterBaseImpl(ConditionMode conditionMode)
			: mode_{ conditionMode }
		{}
		~FilterBaseImpl() = default;

		FilterBaseImpl(const FilterBaseImpl& other) = default;
		FilterBaseImpl& operator=(const FilterBaseImpl& other) = default;
		FilterBaseImpl(FilterBaseImpl&& other) noexcept = default;
		FilterBaseImpl& operator=(FilterBaseImpl&& other) noexcept = default;

		ConditionMode mode_{};
	};

	FilterBase::FilterBase()
		: Component{ ComponentId::FilterBase }
	{}

	FilterBase::FilterBase(ComponentId componentId, ConditionMode conditionMode) noexcept
		: Component{ componentId }
		, impl_{ std::make_unique<FilterBaseImpl>(conditionMode) }
	{}

	FilterBase::~FilterBase() = default;


	FilterBase::FilterBase(const FilterBase& other)
		: Component(other)
		, impl_{ std::make_unique<FilterBaseImpl>(*other.impl_) }
	{}


	FilterBase& FilterBase::operator=(const FilterBase& other)
	{
		if (this != &other)
		{
			Component::operator=(other);
			impl_ = std::make_unique<FilterBaseImpl>(*other.impl_);
		}

		return *this;
	}


	FilterBase::FilterBase(FilterBase&& other) noexcept
		: Component(std::move(other))
		, impl_{ std::move(other.impl_) }
	{}


	FilterBase& FilterBase::operator=(FilterBase&& other) noexcept
	{
		if (this != &other)
		{
			Component::operator=(std::move(other));
			impl_ = std::move(other.impl_);
		}

		return *this;
	}


	ConditionMode FilterBase::mode() const
	{
		return impl_->mode_;
	}
}
