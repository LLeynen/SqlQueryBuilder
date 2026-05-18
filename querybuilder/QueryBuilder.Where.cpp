// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import :BuilderTypes;
import :Concepts;
import :Field;
import :Condition;
import :Parameter;
import :Filter;
import :CompositeCondition;
import :Impl;

namespace DataAccessLayer::SqlQueryBuilder
{
	// QueryBuilder::where(field, comp, value)
	QueryBuilder& QueryBuilder::where(const FieldRef& fieldRef, const Comparison comparison, const ConditionVariant& conditionValue)
	{
		ensureSharedPtr(impl_->whereFilterPtr_);

		if (impl_->whereFilterPtr_->conditionBase())
		{
			return andWhere(fieldRef, comparison, conditionValue);
		}

		ConditionVariant modifiedConditionValue = conditionValue;
		if (std::holds_alternative<Parameter>(conditionValue))
		{
			auto parameter = std::get<Parameter>(conditionValue);
			if (!parameter.parameterMap())
			{
				parameter.setParameterMap(impl_->parameterMapPtr_);
			}
			modifiedConditionValue = parameter;
		}

		Condition condition{ fieldRef.get(), comparison, modifiedConditionValue };

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

	// QueryBuilder::where(ConditionBase)
	QueryBuilder& QueryBuilder::where(const ConditionBase& conditionBase)
	{
		ensureSharedPtr(impl_->whereFilterPtr_)->setCondition(conditionBase);

		return *this;
	}

	// QueryBuilder::where(column, comp, value)
	/*
	QueryBuilder& QueryBuilder::where(const String& columnName, const Comparison comparison, const ConditionVariant& conditionValue)
	{
		return where(Field(columnName), comparison, conditionValue);
	}
*/

	// QueryBuilder::where(table, column, comp, value)
	/*
	QueryBuilder& QueryBuilder::where(const String& tableName, const String& columnName, const Comparison comparison, const ConditionVariant& conditionValue)
	{
		return where(Field(tableName, columnName), comparison, conditionValue);
	}
*/

	// QueryBuilder::whereGroup
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

	// QueryBuilder::endGroup
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

	// QueryBuilder::andWhere
	QueryBuilder& QueryBuilder::andWhere(const FieldRef& fieldRef, const Comparison comparison, const ConditionVariant& conditionValue)
	{
		ConditionVariant modifiedConditionValue = conditionValue;

		if (std::holds_alternative<Parameter>(conditionValue))
		{
			Parameter parameter = std::get<Parameter>(conditionValue);
			if (!parameter.parameterMap())
			{
				parameter.setParameterMap(impl_->parameterMapPtr_);
			}
			modifiedConditionValue = parameter;
		}

		Condition condition{ fieldRef.get(), comparison, modifiedConditionValue };

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

	// QueryBuilder::andWhere
/*
	QueryBuilder& QueryBuilder::andWhere(const String& columnName, const Comparison comparison, const ConditionVariant& conditionValue)
	{
		return andWhere(Field(columnName), comparison, conditionValue);
	}
*/

	// QueryBuilder::andWhere
/*
	QueryBuilder& QueryBuilder::andWhere(const String& tableName, const String& columnName, const Comparison comparison, const ConditionVariant& conditionValue)
	{
		return andWhere(Field(tableName, columnName), comparison, conditionValue);
	}
*/
	// QueryBuilder::andWhere
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

	// QueryBuilder::orWhere
	QueryBuilder& QueryBuilder::orWhere(const FieldRef& fieldRef, const Comparison comparison, const ConditionVariant& conditionValue)
	{
		ConditionVariant modifiedConditionValue = conditionValue;
		if (std::holds_alternative<Parameter>(conditionValue))
		{
			Parameter parameter = std::get<Parameter>(conditionValue);
			if (!parameter.parameterMap())
			{
				parameter.setParameterMap(impl_->parameterMapPtr_);
			}
			modifiedConditionValue = parameter;
		}

		Condition condition{ fieldRef.get(), comparison, modifiedConditionValue };

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

	// QueryBuilder::orWhere
/*
	QueryBuilder& QueryBuilder::orWhere(const String& columnName, const Comparison comparison, const ConditionVariant& conditionValue)
	{
		return orWhere(Field(columnName), comparison, conditionValue);
	}
*/

	// QueryBuilder::orWhere
/*
	QueryBuilder& QueryBuilder::orWhere(const String& tableName, const String& columnName, const Comparison comparison, const ConditionVariant& conditionValue)
	{
		return orWhere(Field(tableName, columnName), comparison, conditionValue);
	}
*/

	// QueryBuilder::orWhere
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
}
