// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :OrderByClause;

import std;

import :BuilderTypes;
import :Component;
import :IBuilder;
import :Field;

namespace DataAccessLayer::SqlQueryBuilder
{
	class OrderByClauseImpl
	{
	public:
		OrderByClauseImpl() = default;
		explicit OrderByClauseImpl(Field field, const SortOrder sortOrder)
			: field_{std::move(field)}
			, sortOrder_{ sortOrder }
		{}
		~OrderByClauseImpl() = default;

		OrderByClauseImpl(const OrderByClauseImpl&) = default;
		OrderByClauseImpl& operator=(const OrderByClauseImpl&) = default;
		OrderByClauseImpl(OrderByClauseImpl&&) = default;
		OrderByClauseImpl& operator=(OrderByClauseImpl&&) = default;

		Field field_{};
		SortOrder sortOrder_{ SortOrder::Ascending };
	};

	OrderByClause::OrderByClause() noexcept
		: Component(ComponentId::OrderByClause)
		, impl_{ std::make_unique<OrderByClauseImpl>() }
	{}


	OrderByClause::OrderByClause(FieldRef fieldRef, SortOrder sortOrder)
		: Component(ComponentId::OrderByClause)
		, impl_{ std::make_unique<OrderByClauseImpl>(fieldRef.move(), sortOrder) }
	{}


	OrderByClause::~OrderByClause() = default;


	OrderByClause::OrderByClause(const OrderByClause& other)
		: Component(other)
		, impl_{ std::make_unique<OrderByClauseImpl>(*other.impl_) }
	{}


	OrderByClause& OrderByClause::operator=(const OrderByClause& other)
	{
		if (this != &other)
		{
			Component::operator=(other);
			impl_ = std::make_unique<OrderByClauseImpl>(*other.impl_);
		}

		return *this;
	}


	OrderByClause::OrderByClause(OrderByClause&& other) noexcept
		: Component(std::move(other))
		, impl_{ std::move(other.impl_) }
	{}


	OrderByClause& OrderByClause::operator=(OrderByClause&& other) noexcept
	{
		if (this != &other)
		{
			Component::operator=(std::move(other));
			impl_ = std::move(other.impl_);
		}
		return *this;
	}


	Field OrderByClause::field() const
	{
		return impl_->field_;
	}


	void OrderByClause::setField(FieldRef fieldRef) const
	{
		impl_->field_ = fieldRef.move();
	}


	SortOrder OrderByClause::sortOrder() const noexcept
	{
		return impl_->sortOrder_;
	}


	void OrderByClause::setSortOrder(SortOrder sortOrder) const noexcept
	{
		impl_->sortOrder_ = sortOrder;
	}


	String OrderByClause::toSql(const IBuilder* builderPtr) const
	{
		return Component::sqlImpl(builderPtr, *this);
	}
}
