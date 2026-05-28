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
		TopClauseImpl(const int quantity, const TopUnit unit) noexcept
			: unit_{ unit }
			, quantity_{ quantity }
		{}
		~TopClauseImpl() = default;

		TopClauseImpl(const TopClauseImpl&) = default;
		TopClauseImpl& operator=(const TopClauseImpl&) = default;
		TopClauseImpl(TopClauseImpl&&) = default;
		TopClauseImpl& operator=(TopClauseImpl&&) = default;

		TopUnit unit_{ TopUnit::Records };
		int quantity_{};
	};

	TopClause::TopClause() noexcept
		: Component(ComponentId::TopClause)
		, impl_{ std::make_unique<TopClauseImpl>() }
	{}


	TopClause::TopClause(int quantity, TopUnit unit) noexcept
		: Component(ComponentId::TopClause)
		, impl_{ std::make_unique<TopClauseImpl>(quantity, unit) }
	{}


	TopClause::~TopClause() = default;


	TopClause::TopClause(const TopClause& other)
		: Component(ComponentId::TopClause)
		, impl_{ std::make_unique<TopClauseImpl>(*other.impl_) }
	{}


	TopClause& TopClause::operator=(const TopClause& other)
	{
		if (this != &other)
		{
			impl_ = std::make_unique<TopClauseImpl>(*other.impl_);
		}

		return *this;
	}


	TopClause::TopClause(TopClause&& other) noexcept
		: Component(ComponentId::TopClause)
		, impl_{ std::move(other.impl_) }
	{}


	TopClause& TopClause::operator=(TopClause&& other) noexcept
	{
		if (this != &other)
		{
			impl_ = std::move(other.impl_);
		}

		return *this;
	}


	int TopClause::quantity() const noexcept
	{
		return impl_->quantity_;
	}


	void TopClause::setQuantity(const int quantity) const noexcept
	{
		impl_->quantity_ = quantity;
	}


	TopUnit TopClause::unit() const noexcept
	{
		return impl_->unit_;
	}


	void TopClause::setUnit(const TopUnit unit) const noexcept
	{
		impl_->unit_ = unit;
	}


	String TopClause::toSql(const IBuilder* builderPtr) const
	{
		return Component::sqlImpl(builderPtr, *this);
	}
}
