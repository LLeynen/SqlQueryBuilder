// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import :BuilderTypes;
import :Concepts;
//import :Field;
//import :Condition;
//import :ConditionExpression;
//import :Parameter;
import :FilterBase;
//import :CompositeCondition;
import :Impl;

namespace DataAccessLayer::SqlQueryBuilder
{
	QueryBuilder& QueryBuilder::where(const FilterBase& filter)
	{
		if (impl_->whereFilterPtr_)
		{
			impl_->whereFilterPtr_ = std::make_shared<LogicalFilter>(*impl_->whereFilterPtr_, LogicOperator::And, filter);
		}
		else
		{
			impl_->whereFilterPtr_ = filter.clone();
		}
		return *this;
	}
/*
	QueryBuilder& QueryBuilder::where(Operand lhs, const Comparison comp, Operand rhs)
	{
		return where(Filter(std::move(lhs), comp, std::move(rhs)));
	}
*/

	/*
	QueryBuilder& QueryBuilder::where(FieldRef fieldRef, const Comparison comparison, ConditionVariant conditionValue)
	{
		ensureSharedPtr(impl_->whereFilterPtr_);

		const auto value = std::move(conditionValue);

		if (impl_->whereFilterPtr_->conditionBase())
		{
			return andWhere(std::move(fieldRef), comparison, value);
		}

		ConditionVariant modifiedValue = value;

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

		if (impl_->isWhereChaining_)
		{
			impl_->addConditionToWhereChain(condition, LogicOperator::And);
		}
		else
		{
			impl_->whereFilterPtr_->setCondition(condition);
		}

		return *this;
	}



	QueryBuilder& QueryBuilder::where(const ConditionBase& conditionBase)
	{
		ensureSharedPtr(impl_->whereFilterPtr_)->setCondition(conditionBase);

		return *this;
	}


	QueryBuilder& QueryBuilder::whereGroup()
	{
		using CC = std::remove_reference_t<decltype(*impl_->currentWhereChainPtr_)>;
		const auto newGroup = std::make_shared<CC>();

		if (!impl_->isWhereChaining_)
		{
			impl_->currentWhereChainPtr_ = newGroup;
			impl_->isWhereChaining_ = true;
		}
		else
		{
			impl_->whereGroupStack_.push_back(impl_->currentWhereChainPtr_);
			impl_->currentWhereChainPtr_ = newGroup;
		}

		return *this;
	}


	QueryBuilder& QueryBuilder::endGroup()
	{
		if (impl_->whereGroupStack_.empty())
		{
			if (impl_->currentWhereChainPtr_ && impl_->isWhereChaining_)
			{
				if (!impl_->whereFilterPtr_)
				{
					impl_->whereFilterPtr_ = std::make_shared<Filter>();
				}
				impl_->whereFilterPtr_->setCondition(*impl_->currentWhereChainPtr_);

				impl_->currentWhereChainPtr_.reset();
				impl_->isWhereChaining_ = false;
			}
		}
		else
		{
			auto parentGroup = impl_->whereGroupStack_.back();
			impl_->whereGroupStack_.pop_back();

			if (impl_->currentWhereChainPtr_)
			{
				parentGroup->addCondition(*impl_->currentWhereChainPtr_);
			}

			impl_->currentWhereChainPtr_ = parentGroup;
		}

		return *this;
	}


	QueryBuilder& QueryBuilder::andWhere(FieldRef fieldRef, const Comparison comparison, ConditionVariant conditionValue)
	{
		const auto value = std::move(conditionValue);
		ConditionVariant modifiedValue = value;

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

		if (!impl_->isWhereChaining_ && impl_->whereFilterPtr_ && impl_->whereFilterPtr_->conditionBase())
		{
			using CC = std::remove_reference_t<decltype(*impl_->currentWhereChainPtr_)>;
			impl_->currentWhereChainPtr_ = std::make_shared<CC>();
			impl_->currentWhereChainPtr_->addCondition(*impl_->whereFilterPtr_->conditionBase());

			impl_->whereFilterPtr_->clear();

			impl_->currentWhereChainPtr_->setLogicOperator(LogicOperator::And);
			impl_->currentWhereChainPtr_->addCondition(condition);
			impl_->isWhereChaining_ = true;
		}
		else
		{
			impl_->addConditionToWhereChain(condition, LogicOperator::And);
		}

		return *this;
	}


	QueryBuilder& QueryBuilder::andWhere(const ConditionBase& conditionBase)
	{
		if (!impl_->isWhereChaining_ && impl_->whereFilterPtr_ && impl_->whereFilterPtr_->conditionBase())
		{
			using CC = std::remove_reference_t<decltype(*impl_->currentWhereChainPtr_)>;
			impl_->currentWhereChainPtr_ = std::make_shared<CC>();
			impl_->currentWhereChainPtr_->addCondition(*impl_->whereFilterPtr_->conditionBase());

			impl_->whereFilterPtr_->clear();

			impl_->currentWhereChainPtr_->setLogicOperator(LogicOperator::And);
			impl_->currentWhereChainPtr_->addCondition(conditionBase);
			impl_->isWhereChaining_ = true;
		}
		else
		{
			impl_->addConditionToWhereChain(conditionBase, LogicOperator::And);
		}

		return *this;
	}


	QueryBuilder& QueryBuilder::orWhere(FieldRef fieldRef, const Comparison comparison, ConditionVariant conditionValue)
	{
		const auto value = std::move(conditionValue);
		ConditionVariant modifiedValue = value;

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

		if (!impl_->isWhereChaining_ && impl_->whereFilterPtr_ && impl_->whereFilterPtr_->conditionBase())
		{
			using CC = std::remove_reference_t<decltype(*impl_->currentWhereChainPtr_)>;
			impl_->currentWhereChainPtr_ = std::make_shared<CC>();
			impl_->currentWhereChainPtr_->addCondition(*impl_->whereFilterPtr_->conditionBase());

			impl_->whereFilterPtr_->clear();

			impl_->currentWhereChainPtr_->setLogicOperator(LogicOperator::Or);
			impl_->currentWhereChainPtr_->addCondition(condition);
			impl_->isWhereChaining_ = true;
		}
		else
		{
			impl_->addConditionToWhereChain(condition, LogicOperator::Or);
		}

		return *this;
	}


	QueryBuilder& QueryBuilder::orWhere(const ConditionBase& conditionBase)
	{
		if (!impl_->isWhereChaining_ && impl_->whereFilterPtr_ && impl_->whereFilterPtr_->conditionBase())
		{
			using CC = std::remove_reference_t<decltype(*impl_->currentWhereChainPtr_)>;
			impl_->currentWhereChainPtr_ = std::make_shared<CC>();
			impl_->currentWhereChainPtr_->addCondition(*impl_->whereFilterPtr_->conditionBase());

			impl_->whereFilterPtr_->clear();

			impl_->currentWhereChainPtr_->setLogicOperator(LogicOperator::Or);
			impl_->currentWhereChainPtr_->addCondition(conditionBase);

			impl_->isWhereChaining_ = true;
		}
		else
		{
			impl_->addConditionToWhereChain(conditionBase, LogicOperator::Or);
		}

		return *this;
	}
	*/
}
