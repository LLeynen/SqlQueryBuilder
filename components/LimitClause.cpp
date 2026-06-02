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


	LimitClause::LimitClause() noexcept
		: Component(ComponentId::LimitClause)
		, impl_{ std::make_unique<LimitClauseImpl>() }
	{}


	LimitClause::LimitClause(int quantity) noexcept
		: Component(ComponentId::LimitClause)
		, impl_{ std::make_unique<LimitClauseImpl>(quantity) }
	{}


	LimitClause::~LimitClause() = default;


	LimitClause::LimitClause(const LimitClause& other)
		: Component(other)
		, impl_ { std::make_unique<LimitClauseImpl>(*other.impl_) }
	{}


	LimitClause& LimitClause::operator=(const LimitClause& other)
	{
		if (this != &other)
		{
			Component::operator=(other);
			impl_ = std::make_unique<LimitClauseImpl>(*other.impl_);
		}

		return *this;
	}


	LimitClause::LimitClause(LimitClause&& other) noexcept
		: Component(std::move(other)) 
		, impl_{ std::move(other.impl_) }
	{}


	LimitClause& LimitClause::operator=(LimitClause&& other) noexcept
	{
		if (this != &other)
		{
			Component::operator=(std::move(other));
			impl_ = std::move(other.impl_);
		}

		return *this;
	}


	int LimitClause::quantity() const noexcept
	{
		return impl_->quantity_;
	}


	void LimitClause::setQuantity(const int quantity) const noexcept
	{
		impl_->quantity_ = quantity;
	}


	String LimitClause::toSql(const IBuilder* builderPtr) const
	{
		return Component::sqlImpl(builderPtr, *this);
	}
}
