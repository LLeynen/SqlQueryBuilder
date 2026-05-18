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
			JoinClauseImpl(Field fromField, const Comparison comparison, const Field& toField, JoinType joinType)
				: fromField_{std::move( fromField )}
				, comparison_{ comparison }
				, toField_{ toField }
				, joinType_{ joinType }
			{}
			~JoinClauseImpl() = default;

			JoinClauseImpl(const JoinClauseImpl& other) = default;
			JoinClauseImpl& operator=(const JoinClauseImpl& other) = default;
			JoinClauseImpl(JoinClauseImpl&& other) = default;
			JoinClauseImpl& operator=(JoinClauseImpl&& other) = default;

			Field fromField_;
			Comparison comparison_ { Comparison::Equals};
			Field toField_;
			JoinType joinType_{ JoinType::InnerJoin };
	};

	// JoinClause::JoinClause
	JoinClause::JoinClause() 
		: Component(ComponentId::JoinClause)
		, impl_{ std::make_unique<JoinClauseImpl>() }
	{}

	// JoinClause::JoinClause
	JoinClause::JoinClause(const Field& fromField, const Comparison comparison, const Field& toField, JoinType joinType)
		: Component(ComponentId::JoinClause)
		, impl_{ std::make_unique<JoinClauseImpl>(fromField, comparison, toField, joinType) }
	{}

	// JoinClause::~JoinClause
	JoinClause::~JoinClause() = default;

	// JoinClause::JoinClause(JoinClause&)
	JoinClause::JoinClause(const JoinClause& other)
		: Component(ComponentId::JoinClause)
		, impl_{ std::make_unique<JoinClauseImpl>(*other.impl_) }
	{}

	// JoinClause::operator=(JoinClause&)
	JoinClause& JoinClause::operator=(const JoinClause& other)
	{
		if (this != &other)
		{
			impl_ = std::make_unique<JoinClauseImpl>(*other.impl_);
		}

		return *this;
	}

	// JoinClause::JoinClause(JoinClause&&)
	JoinClause::JoinClause(JoinClause&& other) noexcept
		: Component(ComponentId::JoinClause)
		, impl_{ std::move(other.impl_) }
	{}

	// JoinClause::operator=(JoinClause&&)
	JoinClause& JoinClause::operator=(JoinClause&& other) noexcept
	{
		if (this != &other)
		{
			impl_ = std::move(other.impl_);
		}

		return *this;
	}

	// JoinClause::fromField
	const Field& JoinClause::fromField() const noexcept
	{
		return impl_->fromField_;
	}

	// JoinClause::setFromField
	void JoinClause::setFromField(const Field& fromField)
	{
		impl_->fromField_ = fromField;
	}

	// JoinClause::Comparison
	const Comparison JoinClause::comparison() const noexcept
	{
		return impl_->comparison_;
	}

	// JoinClause::setComparison
	void JoinClause::setComparison(Comparison comparison) noexcept
	{
		impl_->comparison_ = comparison;
	}

	// JoinClause::toField
	const Field& JoinClause::toField() const noexcept
	{
		return impl_->toField_;
	}

	// JoinClause::setToField
	void JoinClause::setToField(const Field& toField)
	{
		impl_->toField_ = toField;
	}

	// JoinClause::joinType
	const JoinType JoinClause::joinType() const noexcept
	{
		return impl_->joinType_;
	}

	// JoinClause::setJoinType
	void JoinClause::setJoinType(JoinType joinType) noexcept
	{
		impl_->joinType_ = joinType;
	}

	// JoinClause::toSql
	String JoinClause::toSql(const IBuilder* builderPtr) const
	{
		return Component::sqlImpl(builderPtr, *this);
	}
}
