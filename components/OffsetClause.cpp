// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :OffsetClause;

import std;

import :BuilderTypes;
import :Component;
import :IBuilder;

namespace DataAccessLayer::SqlQueryBuilder
{
	class OffsetClauseImpl
	{
	public:
		OffsetClauseImpl() = default;
		explicit OffsetClauseImpl(int quantity) noexcept
			: quantity_{ quantity }
		{}
		~OffsetClauseImpl() = default;

		OffsetClauseImpl(const OffsetClauseImpl&) = default;
		OffsetClauseImpl& operator=(const OffsetClauseImpl&) = default;
		OffsetClauseImpl(OffsetClauseImpl&&) = default;
		OffsetClauseImpl& operator=(OffsetClauseImpl&&) = default;

		int quantity_{};
	};

	// OffsetClause::OffsetClause
	OffsetClause::OffsetClause() noexcept
		: Component(ComponentId::OffsetClause)
		, impl_{ std::make_unique<OffsetClauseImpl>() }
	{}

	// OffsetClause::OffsetClause(quantity)
	OffsetClause::OffsetClause(int quantity) noexcept
		: Component(ComponentId::OffsetClause)
		, impl_{ std::make_unique<OffsetClauseImpl>(quantity) }
	{}

	// OffsetClause::~OffsetClause
	OffsetClause::~OffsetClause() = default;

	// OffsetClause::OffsetClause(OffsetClause&)
	OffsetClause::OffsetClause(const OffsetClause& other)
		: Component(other)
		, impl_{ std::make_unique<OffsetClauseImpl>(*other.impl_) }
	{}

	// OffsetClause::operator=(OffsetClause&)
	OffsetClause& OffsetClause::operator=(const OffsetClause& other)
	{
		if (this != &other)
		{
			Component::operator=(other);
			impl_ = std::make_unique<OffsetClauseImpl>(*other.impl_);
		}

		return *this;
	}

	// OffsetClause::OffsetClause(OffsetClause&&)
	OffsetClause::OffsetClause(OffsetClause&& other) noexcept
		: Component(std::move(other))
		, impl_{ std::move(other.impl_) }
	{}

	// OffsetClause::operator=(OffsetClause&&)
	OffsetClause& OffsetClause::operator=(OffsetClause&& other) noexcept
	{
		if (this != &other)
		{
			Component::operator=(std::move(other));
			impl_ = std::move(other.impl_);
		}

		return *this;
	}

	// OffsetClause::quantity
	const int OffsetClause::quantity() const noexcept
	{
		return impl_->quantity_;
	}

	// OffsetClause::setQuantity
	void OffsetClause::setQuantity(int quantity) noexcept
	{
		impl_->quantity_ = quantity;
	}

	// OffsetClause::toSql
	String OffsetClause::toSql(const IBuilder* builderPtr) const
	{
		return Component::sqlImpl(builderPtr, *this);
	}
}
