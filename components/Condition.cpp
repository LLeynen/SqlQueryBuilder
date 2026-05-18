// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :Condition;

import std;

import :BuilderTypes;
import :IBuilder;
import :ConditionBase;
import :CompositeCondition;
import :Variant;
import :Parameter;
import :Field;
import :ListOfValues;
import :Query;

namespace DataAccessLayer::SqlQueryBuilder
{
	class ConditionImpl
	{
	public:
		ConditionImpl() = default;
		ConditionImpl(Field  field, Comparison comparison, ConditionVariant conditionValue)
			: field_{std::move(field)}
			, comparison_{comparison}
			, conditionValue_{std::move(conditionValue)}
		{}
		ConditionImpl(const ConditionImpl& other) = default;
		ConditionImpl& operator=(const ConditionImpl& other) = default;
		ConditionImpl(ConditionImpl&& other)  noexcept = default;
		ConditionImpl& operator=(ConditionImpl&& other) = default;

		Field field_{};
		Comparison comparison_{ Comparison::Equals };
		ConditionVariant conditionValue_{};
	};

	// Condition::Condition
	Condition::Condition() noexcept
		: ConditionBase(ComponentId::Condition)
		, impl_{ std::make_unique<ConditionImpl>() }
	{}

	// Condition::Condition(Field, Comparison, ConditionVariant)
	Condition::Condition(const Field& field, const Comparison comparison, const ConditionVariant& conditionValue)
		: ConditionBase(ComponentId::Condition)
		, impl_{ std::make_unique<ConditionImpl>(field, comparison, conditionValue) }
	{}

	// Condition::Condition(Field, ConditionVariant)
	Condition::Condition(const Field& field, const ConditionVariant& conditionValue)
		: Condition(field, Comparison::Equals, conditionValue)
	{}
	
	// Condition::~Condition
	Condition::~Condition() = default;

	// Condition::Condition(const Condition& other)
	Condition::Condition(const Condition& other)
		: ConditionBase(ComponentId::Condition)
		, impl_{ std::make_unique<ConditionImpl>(*other.impl_) }
	{}

	// Condition::operator=
	Condition& Condition::operator=(const Condition& other)
	{
		if (this != &other)
		{
			impl_ = std::make_unique<ConditionImpl>(*other.impl_);
		}

		return *this;
	}

	// Condition::Condition(Condition&& other) 
	Condition::Condition(Condition&& other) noexcept = default;

	// Condition::operator=(Condition&& other) 
	Condition& Condition::operator=(Condition&& other) noexcept = default;

	// Condition::field
	const Field& Condition::field() const noexcept
	{
		return impl_->field_;
	}

	// Condition::setField
	void Condition::setField(const Field& field)
	{
		impl_->field_ = field;
	}

	// Condition::comparison
	const Comparison& Condition::comparison() const noexcept
	{
		return impl_->comparison_;
	}

	// Condition::setComparison
	void Condition::setComparison(const Comparison comparison) noexcept
	{
		impl_->comparison_ = comparison;
	}

	// Condition::conditionValue
	const ConditionVariant& Condition::conditionValue() const noexcept
	{
		return impl_->conditionValue_;
	}

	// Condition::setConditionValue
	void Condition::setConditionValue(const ConditionVariant& conditionValue)
	{
		impl_->conditionValue_ = conditionValue;
	}

	// Condition::operator&
	CompositeCondition Condition::operator&(const ConditionBase& other) const
	{
		return CompositeCondition{ *this, LogicOperator::And, other };
	}

	// Condition::operator|
	CompositeCondition Condition::operator|(const ConditionBase& other) const
	{
		return CompositeCondition{ *this, LogicOperator::Or, other };
	}

	// Condition::clone
	ConditionBasePtr Condition::clone() const
	{
		return std::shared_ptr<Condition>(new Condition(*this));
	}

	// Condition::sql
	String Condition::toSql(const IBuilder* builderPtr) const
	{
		return Component::sqlImpl(builderPtr, *this);
	}
}
