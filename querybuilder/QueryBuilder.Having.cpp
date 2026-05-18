// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import :BuilderTypes;
import :Concepts;
import :Field;
import :Condition;
import :Impl;

namespace DataAccessLayer::SqlQueryBuilder
{
	// QueryBuilder::having(Field, comp, value)
	QueryBuilder& QueryBuilder::having(const FieldRef& fieldRef, const Comparison comparison, const ConditionVariant& conditionValue)
	{
		ensureSharedPtr(impl_->havingFilterPtr_);

		if (impl_->havingFilterPtr_->conditionBase())
		{
			return andHaving(fieldRef, comparison, conditionValue);
		}

		ConditionVariant modifiedConditionValue = conditionValue;
		if (std::holds_alternative<Parameter>(conditionValue))
		{
			Parameter parameterReference = std::get<Parameter>(conditionValue);
			if (!parameterReference.parameterMap())
			{
				parameterReference.setParameterMap(impl_->parameterMapPtr_);
			}
			modifiedConditionValue = parameterReference;
		}

		Condition condition{ fieldRef.get(), comparison, modifiedConditionValue };

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

	// QueryBuilder::having(ConditionBase)
	QueryBuilder& QueryBuilder::having(const ConditionBase& conditionBase)
	{
		ensureSharedPtr(impl_->havingFilterPtr_)->setCondition(conditionBase);

		return *this;
	}

	// QueryBuilder::having(column, comp, value)
	/*
	QueryBuilder& QueryBuilder::having(const String& columnName, const Comparison comparison, const ConditionVariant& conditionValue)
	{
		return having(Field(columnName), comparison, conditionValue);
	}
*/

	// QueryBuilder::having(table, column, comp, value)
/*
	QueryBuilder& QueryBuilder::having(const String& tableName, const String& columnName, const Comparison comparison, const ConditionVariant& conditionValue)
	{
		return having(Field(tableName, columnName), comparison, conditionValue);
	}
*/

	// QueryBuilder::havingGroup
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

	// QueryBuilder::endHavingGroup
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

	// QueryBuilder::andHaving(Field, comp, value)
	QueryBuilder& QueryBuilder::andHaving(const FieldRef& fieldRef, const Comparison comparison, const ConditionVariant& conditionValue)
	{
		Condition condition{ fieldRef.get(), comparison, conditionValue };
		impl_->addConditionToHavingChain(condition, LogicOperator::And);

		return *this;
	}

	// QueryBuilder::andHaving(column, comp, value)
/*
	QueryBuilder& QueryBuilder::andHaving(const String& columnName, const Comparison comparison, const ConditionVariant& conditionValue)
	{
		return andHaving(Field(columnName), comparison, conditionValue);
	}
*/

	// QueryBuilder::andHaving(table, column, comp, value)
/*
	QueryBuilder& QueryBuilder::andHaving(const String& tableName, const String& columnName, Comparison comparison, const ConditionVariant& conditionValue)

	{
		return andHaving(Field(tableName, columnName), comparison, conditionValue);
	}
*/

	// QueryBuilder::andHaving(ConditionBase)
	QueryBuilder& QueryBuilder::andHaving(const ConditionBase& conditionBase)
	{
		impl_->addConditionToHavingChain(conditionBase, LogicOperator::And);
		return *this;
	}

	// QueryBuilder::orHaving(Field, comp, value)
	QueryBuilder& QueryBuilder::orHaving(const FieldRef& fieldRef, const Comparison comparison, const ConditionVariant& conditionValue)
	{
		Condition condition{ fieldRef.get(), comparison, conditionValue };
		impl_->addConditionToHavingChain(condition, LogicOperator::Or);

		return *this;
	}

	// QueryBuilder::orHaving(column, comp, value)
/*
	QueryBuilder& QueryBuilder::orHaving(const String& columnName, const Comparison comparison, const ConditionVariant& conditionValue)
	{
		return orHaving(Field(columnName), comparison, conditionValue);
	}
*/

	// QueryBuilder::orHaving(table, column, comp, value)
/*
	QueryBuilder& QueryBuilder::orHaving(const String& tableName, const String& columnName, const Comparison comparison, const ConditionVariant& conditionValue)
	{
		return orHaving(Field(tableName, columnName), comparison, conditionValue);
	}
*/

	// QueryBuilder::orHaving(ConditionBase)
	QueryBuilder& QueryBuilder::orHaving(const ConditionBase& conditionBase)
	{
		impl_->addConditionToHavingChain(conditionBase, LogicOperator::Or);
		return *this;
	}
}
