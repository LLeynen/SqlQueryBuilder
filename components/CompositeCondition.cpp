// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :CompositeCondition;

import std;

import :BuilderTypes;
import :ConditionBase;
import :IBuilder;

namespace DataAccessLayer::SqlQueryBuilder
{
	class CompositeConditionImpl
	{
		public:
		CompositeConditionImpl() = default;
		CompositeConditionImpl(const LogicOperator logicOperator, ConditionBaseList conditionBaseList) noexcept
			: logicOperator_{ logicOperator }
			, conditionBaseList_{ std::move(conditionBaseList) }
		{}
		~CompositeConditionImpl() = default;

		CompositeConditionImpl(const CompositeConditionImpl& other) = default;
		CompositeConditionImpl& operator=(const CompositeConditionImpl& other) = default;
		CompositeConditionImpl(CompositeConditionImpl&& other) = default;
		CompositeConditionImpl& operator=(CompositeConditionImpl&& other) = default;

		LogicOperator logicOperator_{ LogicOperator::And };
		ConditionBaseList conditionBaseList_{};
	};

	// CompositeCondition::CompositeCondition()
	CompositeCondition::CompositeCondition() noexcept
		: ConditionBase(ComponentId::CompositeCondition)
		, impl_{ std::make_unique<CompositeConditionImpl>() }
	{}

	// CompositeCondition::CompositeCondition(left, logic, right)
	CompositeCondition::CompositeCondition(const ConditionBase& left, const LogicOperator logicOperator, const ConditionBase& right)
		: ConditionBase(ComponentId::CompositeCondition)
		, impl_{ std::make_unique<CompositeConditionImpl>() }
	{
		impl_->logicOperator_ = logicOperator;
		impl_->conditionBaseList_.push_back(left.clone());
		impl_->conditionBaseList_.push_back(right.clone());
	}

	// CompositeCondition::CompositeCondition(logic, vector)
	CompositeCondition::CompositeCondition(const LogicOperator logicOperator, ConditionBaseList conditionBaseList) noexcept
		: ConditionBase(ComponentId::CompositeCondition)
		, impl_{ std::make_unique<CompositeConditionImpl>(logicOperator, ConditionBaseList(conditionBaseList)) }
	{}

	// CompositeCondition::CompositeCondition(logic, initializer_list)
	CompositeCondition::CompositeCondition(const LogicOperator logicOperator, std::initializer_list<ConditionBasePtr> conditionBaseList) noexcept
		: ConditionBase(ComponentId::CompositeCondition)
		, impl_{ std::make_unique<CompositeConditionImpl>(logicOperator, ConditionBaseList(conditionBaseList)) }
	{}

	// CompositeCondition::~CompositeCondition
	CompositeCondition::~CompositeCondition() = default;

	// CompositeCondition::CompositeCondition(CompositeCondition&)
	CompositeCondition::CompositeCondition(const CompositeCondition& other)
		: ConditionBase(other)
		, impl_{ std::make_unique<CompositeConditionImpl>() }
	{
		copyFrom(other);
	}

	// CompositeCondition::operator=
	CompositeCondition& CompositeCondition::operator=(const CompositeCondition& other)
	{
		if (this != &other)
		{
			ConditionBase::operator=(other);
			copyFrom(other);
		}
		return *this;
	}

	// CompositeCondition::CompositeCondition(CompositeCondition&&)
	CompositeCondition::CompositeCondition(CompositeCondition&&) noexcept = default;

	// CompositeCondition::operator=
	CompositeCondition& CompositeCondition::operator=(CompositeCondition&&) noexcept = default;

	// CompositeCondition::logicOperator
	LogicOperator CompositeCondition::logicOperator() const noexcept
	{
		return impl_->logicOperator_;
	}

	// CompositeCondition::setLogicOperator
	void CompositeCondition::setLogicOperator(const LogicOperator logicOperator) const noexcept
	{
		impl_->logicOperator_ = logicOperator;
	}

	// CompositeCondition::conditionBaseList
	const ConditionBaseList CompositeCondition::conditionBaseList() const
	{
		return impl_->conditionBaseList_;
	}

	// CompositeCondition::setConditionBaseList
	void CompositeCondition::setConditionBaseList(ConditionBaseList conditionBaseList)
	{
		impl_->conditionBaseList_ = conditionBaseList;
	}

	// CompositeCondition::addCondition
	void CompositeCondition::addCondition(const ConditionBase& conditionBase)
	{
		impl_->conditionBaseList_.push_back(conditionBase.clone());
	}

	// CompositeCondition::clone
	ConditionBasePtr CompositeCondition::clone() const
	{
		ConditionBaseList clonedConditionBaseList;

		for (const auto& conditionBase : impl_->conditionBaseList_)
		{
			clonedConditionBaseList.push_back(conditionBase->clone());
		}

		return std::make_shared<CompositeCondition>(impl_->logicOperator_, std::move(clonedConditionBaseList));
	}

	// CompositeCondition::operator&
	CompositeCondition CompositeCondition::operator&(const ConditionBase& other) const
	{
		return CompositeCondition{ *this, LogicOperator::And, other };
	}

	// CompositeCondition::operator|
	CompositeCondition CompositeCondition::operator|(const ConditionBase& other) const
	{
		return CompositeCondition{ *this, LogicOperator::Or, other };
	}

	// CompositeCondition::toSql

	String CompositeCondition::toSql(const IBuilder* builderPtr) const
	{
		return Component::sqlImpl(builderPtr, *this);
	}

	// CompositeCondition::copyFrom
	void CompositeCondition::copyFrom(const CompositeCondition& other)
	{
		impl_->logicOperator_ = other.impl_->logicOperator_;

		impl_->conditionBaseList_.clear();

		for (const auto& conditionBase : other.impl_->conditionBaseList_)
		{
			impl_->conditionBaseList_.push_back(conditionBase->clone());
		}
	}
}
