// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :TopClause;

import std;

import :BuilderTypes;
import :Component;
import :IBuilder;

namespace DataAccessLayer::SqlQueryBuilder
{
	class TopClauseImpl
	{
	public:
		TopClauseImpl() noexcept = default;
		TopClauseImpl(int quantity, TopUnit topUnit) noexcept
			: topUnit_{ topUnit }
			, quantity_{ quantity }
		{}
		~TopClauseImpl() = default;

		TopClauseImpl(const TopClauseImpl&) = default;
		TopClauseImpl& operator=(const TopClauseImpl&) = default;
		TopClauseImpl(TopClauseImpl&&) = default;
		TopClauseImpl& operator=(TopClauseImpl&&) = default;

		TopUnit topUnit_{ TopUnit::Records };
		int quantity_{};
	};

	// TopClause::TopClause
	TopClause::TopClause() noexcept
		: Component(ComponentId::TopClause)
		, impl_{ std::make_unique<TopClauseImpl>() }
	{}

	// TopClause::TopClause(quantity, topunit)
	TopClause::TopClause(int quantity, TopUnit topUnit) noexcept
		: Component(ComponentId::TopClause)
		, impl_{ std::make_unique<TopClauseImpl>(quantity, topUnit) }
	{}

	// TopClause::~TopClause
	TopClause::~TopClause() = default;

	// TopClause::TopClause(TopClause&)
	TopClause::TopClause(const TopClause& other)
		: Component(ComponentId::TopClause)
		, impl_{ std::make_unique<TopClauseImpl>(*other.impl_) }
	{}

	// TopClause::operator=(TopClause&)
	TopClause& TopClause::operator=(const TopClause& other)
	{
		if (this != &other)
		{
			impl_ = std::make_unique<TopClauseImpl>(*other.impl_);
		}

		return *this;
	}

	// TopClause::TopClause(TopClause&&)
	TopClause::TopClause(TopClause&& other) noexcept
		: Component(ComponentId::TopClause)
		, impl_{ std::move(other.impl_) }
	{}

	// TopClause::operator=(TopClause&&)
	TopClause& TopClause::operator=(TopClause&& other) noexcept
	{
		if (this != &other)
		{
			impl_ = std::move(other.impl_);
		}

		return *this;
	}

	// TopClause::quantity
	int TopClause::quantity() const noexcept
	{
		return impl_->quantity_;
	}

	// TopClause::setQuantity
	void TopClause::setQuantity(int quantity) noexcept
	{
		impl_->quantity_ = quantity;
	}

	// TopClause::sqlTopUnit
	const TopUnit TopClause::topUnit() const noexcept
	{
		return impl_->topUnit_;
	}

	// TopClause::setTopUnit
	void TopClause::setTopUnit(TopUnit topUnit) noexcept
	{
		impl_->topUnit_ = topUnit;
	}

	// TopClause::toSql
	String TopClause::toSql(const IBuilder* builderPtr) const
	{
		return Component::sqlImpl(builderPtr, *this);
	}
}
