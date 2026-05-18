// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :LimitClause;

import std;

import :BuilderTypes;
import :Component;
import :IBuilder;

namespace DataAccessLayer::SqlQueryBuilder
{
	class LimitClauseImpl
	{
	public:
		LimitClauseImpl() = default;
		explicit LimitClauseImpl(int quantity) noexcept
			: quantity_{ quantity }
		{}
		LimitClauseImpl(const LimitClauseImpl&) = default;
		LimitClauseImpl& operator=(const LimitClauseImpl&) = default;
		LimitClauseImpl(LimitClauseImpl&&) = default;
		LimitClauseImpl& operator=(LimitClauseImpl&&) = default;

		int quantity_{};
	};

	// LimitClause::LimitClause
	LimitClause::LimitClause() noexcept
		: Component(ComponentId::LimitClause)
		, impl_{ std::make_unique<LimitClauseImpl>() }
	{}

	// LimitClause::LimitClause(quantity)
	LimitClause::LimitClause(int quantity) noexcept
		: Component(ComponentId::LimitClause)
		, impl_{ std::make_unique<LimitClauseImpl>(quantity) }
	{}

	// LimitClause::~LimitClause
	LimitClause::~LimitClause() = default;

	// LimitClause::LimitClause(LimitClause&)
	LimitClause::LimitClause(const LimitClause& other)
		: Component(other)
		, impl_ { std::make_unique<LimitClauseImpl>(*other.impl_) }
	{}

	// LimitClause::operator=(LimitClause&)
	LimitClause& LimitClause::operator=(const LimitClause& other)
	{
		if (this != &other)
		{
			Component::operator=(other);
			impl_ = std::make_unique<LimitClauseImpl>(*other.impl_);
		}

		return *this;
	}

	// LimitClause::LimitClause(LimitClause&&)
	LimitClause::LimitClause(LimitClause&& other) noexcept
		: Component(std::move(other)) 
		, impl_{ std::move(other.impl_) }
	{}

	// LimitClause::operator=(LimitClause&&)
	LimitClause& LimitClause::operator=(LimitClause&& other) noexcept
	{
		if (this != &other)
		{
			Component::operator=(std::move(other));
			impl_ = std::move(other.impl_);
		}

		return *this;
	}

	// LimitClause::quantity
	int LimitClause::quantity() const noexcept
	{
		return impl_->quantity_;
	}

	// LimitClause::setQuantity
	void LimitClause::setQuantity(int quantity) noexcept
	{
		impl_->quantity_ = quantity;
	}

	// LimitClause::toSql
	String LimitClause::toSql(const IBuilder* builderPtr) const
	{
		return Component::sqlImpl(builderPtr, *this);
	}
}
