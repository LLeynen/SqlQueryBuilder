// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import :ConditionBase;

import :BuilderTypes;
import :Component;

namespace DataAccessLayer::SqlQueryBuilder
{
	class ConditionBaseImpl
	{
		public:
			ConditionBaseImpl() = default;
			~ConditionBaseImpl() = default;

			ConditionBaseImpl(const ConditionBaseImpl&) = default;
			ConditionBaseImpl& operator=(const ConditionBaseImpl&) = default;
			ConditionBaseImpl(ConditionBaseImpl&&) = default;
			ConditionBaseImpl& operator=(ConditionBaseImpl&&) = default;
	};

	// ConditionBase::ConditionBase
	ConditionBase::ConditionBase() noexcept
		: Component(ComponentId::ConditionBase)
		, impl_(std::make_unique<ConditionBaseImpl>())
	{}

	// ConditionBase::ConditionBase(ComponentId)
	ConditionBase::ConditionBase(ComponentId componentId) noexcept
		: Component(componentId)
		, impl_(std::make_unique<ConditionBaseImpl>())
	{}

	// ConditionBase::~ConditionBase
	ConditionBase::~ConditionBase() = default;

	// ConditionBase::ConditionBase(const ConditionBase&)
	ConditionBase::ConditionBase(const ConditionBase& other)
		: Component(ComponentId::ConditionBase)
		, impl_(std::make_unique<ConditionBaseImpl>(*other.impl_))
	{}

	// ConditionBase::operator=(const ConditionBase&)
	ConditionBase& ConditionBase::operator=(const ConditionBase& other)
	{
		if (this != &other)
		{
			Component::operator=(other);
			impl_ = std::make_unique<ConditionBaseImpl>(*other.impl_);
		}

		return *this;
	}

	// ConditionBase::ConditionBase(ConditionBase&&)
	ConditionBase::ConditionBase(ConditionBase&& other) noexcept
		: Component(std::move(other))
		, impl_(std::move(other.impl_))
	{}

	// ConditionBase::operator=(ConditionBase&&)
	ConditionBase& ConditionBase::operator=(ConditionBase&& other) noexcept
	{
		if (this != &other)
		{
			Component::operator=(std::move(other));
			impl_ = std::move(other.impl_);
		}

		return *this;
	}
}
