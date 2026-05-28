// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import :BuilderTypes;
import :Concepts;
//import :Field;
import :FilterBase;
import :Impl;

namespace DataAccessLayer::SqlQueryBuilder
{
	QueryBuilder& QueryBuilder::having(const FilterBase& filter)
	{
		if (impl_->havingFilterPtr_)
		{
			impl_->havingFilterPtr_ = std::make_shared<LogicalFilter>(*impl_->havingFilterPtr_, LogicOperator::And, *filter.clone());
		}
		else
		{
//			ensureSharedPtr(impl_->havingFilterPtr_);
			impl_->havingFilterPtr_ = filter.clone();
		}
		return *this;
	}

	/*
	QueryBuilder& QueryBuilder::having(Operand lhs, const Comparison comp, Operand rhs)
	{
		return having(ComparisonFilter(std::move(lhs), comp, std::move(rhs)));
	}

*/

/*
	QueryBuilder& QueryBuilder::having(FieldRef fieldRef, const Comparison comparison, ConditionVariant conditionValue)
	{
		ensureSharedPtr(impl_->havingFilterPtr_);

		const auto value = std::move(conditionValue);

		if (impl_->havingFilterPtr_->conditionBase())
		{
			return andHaving(fieldRef, comparison, value);
		}

		auto modifiedValue = value;

		if (std::holds_alternative<Parameter>(value))
		{
			auto parameter = std::get<Parameter>(value);
			if (!parameter.parameterMap())
			{
				parameter.setParameterMap(impl_->parameterMapPtr_);
			}
			modifiedValue = parameter;
		}

		const Condition condition{ std::move(fieldRef), comparison, modifiedValue };

		if (impl_->isHavingChaining_)
		{
			impl_->addConditionToHavingChain(condition, LogicOperator::And);
		}
		else
		{
			impl_->havingFilterPtr_->setCondition(condition);
		}

		return *this;
	}


	QueryBuilder& QueryBuilder::having(const ConditionBase& conditionBase)
	{
		ensureSharedPtr(impl_->havingFilterPtr_)->setCondition(conditionBase);

		return *this;
	}


	QueryBuilder& QueryBuilder::havingGroup()
	{
		using CC = std::remove_reference_t<decltype(*impl_->currentHavingChainPtr_)>;
		auto newGroup = std::make_shared<CC>();

		if (!impl_->isHavingChaining_)
		{
			impl_->currentHavingChainPtr_ = newGroup;
			impl_->isHavingChaining_ = true;
		}
		else
		{
			impl_->havingGroupStack_.push_back(impl_->currentHavingChainPtr_);
			impl_->currentHavingChainPtr_ = newGroup;
		}

		return *this;
	}


	QueryBuilder& QueryBuilder::endHavingGroup()
	{
		if (impl_->havingGroupStack_.empty())
		{
			if (impl_->currentHavingChainPtr_ && impl_->isHavingChaining_)
			{
				if (!impl_->havingFilterPtr_)
				{
					impl_->havingFilterPtr_ = std::make_shared<Filter>();
				}
				impl_->havingFilterPtr_->setCondition(*impl_->currentHavingChainPtr_);

				impl_->currentHavingChainPtr_.reset();
				impl_->isHavingChaining_ = false;
			}
		}
		else
		{
			auto parentGroup = impl_->havingGroupStack_.back();
			impl_->havingGroupStack_.pop_back();

			if (impl_->currentHavingChainPtr_)
			{
				parentGroup->addCondition(*impl_->currentHavingChainPtr_);
			}

			impl_->currentHavingChainPtr_ = parentGroup;
		}

		return *this;
	}


	QueryBuilder& QueryBuilder::andHaving(FieldRef fieldRef, const Comparison comparison, ConditionVariant conditionValue)
	{
		const Condition condition{ std::move(fieldRef), comparison, std::move(conditionValue) };
		impl_->addConditionToHavingChain(condition, LogicOperator::And);

		return *this;
	}


	QueryBuilder& QueryBuilder::andHaving(const ConditionBase& conditionBase)
	{
		impl_->addConditionToHavingChain(conditionBase, LogicOperator::And);
		return *this;
	}


	QueryBuilder& QueryBuilder::orHaving(FieldRef fieldRef, const Comparison comparison, ConditionVariant conditionValue)
	{
		Condition condition{ std::move(fieldRef), comparison, std::move(conditionValue) };
		impl_->addConditionToHavingChain(condition, LogicOperator::Or);

		return *this;
	}


	QueryBuilder& QueryBuilder::orHaving(const ConditionBase& conditionBase)
	{
		impl_->addConditionToHavingChain(conditionBase, LogicOperator::Or);
		return *this;
	}

	*/
}
