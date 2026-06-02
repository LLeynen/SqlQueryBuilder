// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :JoinClause;

import std;

import :BuilderTypes;
import :Component;
import :IBuilder;
import :Field;

namespace DataAccessLayer::SqlQueryBuilder
{
	class JoinClauseImpl
	{
		public:
			JoinClauseImpl() = default;
			JoinClauseImpl(Field fromField, const Comparison comparison, Field toField, const JoinType joinType)
				: fromField_ {std::move(fromField) }
				, comparison_{ comparison }
				, toField_{ std::move(toField) }
				, joinType_{ joinType }
			{}
			~JoinClauseImpl() = default;

			JoinClauseImpl(const JoinClauseImpl& other) = default;
			JoinClauseImpl& operator=(const JoinClauseImpl& other) = default;
			JoinClauseImpl(JoinClauseImpl&& other) = default;
			JoinClauseImpl& operator=(JoinClauseImpl&& other) = default;

			Field fromField_{};
			Comparison comparison_ { Comparison::Equals};
			Field toField_{};
			JoinType joinType_{ JoinType::InnerJoin };
	};


	JoinClause::JoinClause()
		: Component(ComponentId::JoinClause)
		, impl_{ std::make_unique<JoinClauseImpl>() }
	{}


	JoinClause::JoinClause(FieldRef fromFieldRef, const Comparison comparison, FieldRef toFieldRef, JoinType joinType)
		: Component(ComponentId::JoinClause)
		, impl_{ std::make_unique<JoinClauseImpl>(fromFieldRef.move(), comparison, toFieldRef.move(), joinType) }
	{}


	JoinClause::~JoinClause() = default;


	JoinClause::JoinClause(const JoinClause& other)
		: Component(ComponentId::JoinClause)
		, impl_{ std::make_unique<JoinClauseImpl>(*other.impl_) }
	{}


	JoinClause& JoinClause::operator=(const JoinClause& other)
	{
		if (this != &other)
		{
			impl_ = std::make_unique<JoinClauseImpl>(*other.impl_);
		}

		return *this;
	}


	JoinClause::JoinClause(JoinClause&& other) noexcept
		: Component(ComponentId::JoinClause)
		, impl_{ std::move(other.impl_) }
	{}


	JoinClause& JoinClause::operator=(JoinClause&& other) noexcept
	{
		if (this != &other)
		{
			impl_ = std::move(other.impl_);
		}

		return *this;
	}


	Field JoinClause::fromField() const noexcept
	{
		return impl_->fromField_;
	}


	void JoinClause::setFromField(FieldRef fromFieldRef) const
	{
		impl_->fromField_ = fromFieldRef.move();
	}


	Comparison JoinClause::comparison() const noexcept
	{
		return impl_->comparison_;
	}


	void JoinClause::setComparison(const Comparison comparison) const noexcept
	{
		impl_->comparison_ = comparison;
	}


	Field JoinClause::toField() const noexcept
	{
		return impl_->toField_;
	}


	void JoinClause::setToField(FieldRef toFieldRef)
	{
		impl_->toField_ = toFieldRef.move();
	}


	JoinType JoinClause::joinType() const noexcept
	{
		return impl_->joinType_;
	}


	void JoinClause::setJoinType(JoinType joinType) const noexcept
	{
		impl_->joinType_ = joinType;
	}


	String JoinClause::toSql(const IBuilder* builderPtr) const
	{
		return Component::sqlImpl(builderPtr, *this);
	}
}
