// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :Impl;

import :BuilderTypes;
import :Concepts;

namespace DataAccessLayer::SqlQueryBuilder
{
	void QueryBuilderImpl::populateComponents()
	{
/*
 *		if (currentWhereChainPtr_ && isWhereChaining_)
		{
			ensureSharedPtr(whereFilterPtr_)->setCondition(*currentWhereChainPtr_);

			currentWhereChainPtr_.reset();
			isWhereChaining_ = false;
		}

		if (currentHavingChainPtr_ && isHavingChaining_)
		{
			ensureSharedPtr(havingFilterPtr_)->setCondition(*currentHavingChainPtr_);

			currentHavingChainPtr_.reset();
			isHavingChaining_ = false;
		}
*/
		ensureSharedPtr(componentMapPtr_)->clear();

		if (!distinct_.isNull())
		{
			(*componentMapPtr_)[ComponentId::DistinctWrapper] = std::make_shared<DistinctWrapper>(distinct_);
		}

		if (topClausePtr_)
		{
			(*componentMapPtr_)[ComponentId::TopClause] = topClausePtr_;
		}

		if (dataSourcePtr_)
		{
			(*componentMapPtr_)[ComponentId::DataSource] = dataSourcePtr_;
		}

		if (selectableListPtr_ and !selectableListPtr_->empty())
		{
			(*componentMapPtr_)[ComponentId::SelectableListWrapper] = std::make_shared<SelectableListWrapper>(selectableListPtr_);
		}

		if (joinClauseListPtr_ and !joinClauseListPtr_->empty())
		{
			(*componentMapPtr_)[ComponentId::JoinClauseListWrapper] = std::make_shared<JoinClauseListWrapper>(joinClauseListPtr_);
		}

		if (whereFilterPtr_)
		{
			(*componentMapPtr_)[ComponentId::WhereFilterWrapper] = std::make_shared<WhereFilterWrapper>(whereFilterPtr_);
		}

		if (havingFilterPtr_)
		{
			(*componentMapPtr_)[ComponentId::HavingFilterWrapper] = std::make_shared<HavingFilterWrapper>(havingFilterPtr_);
		}

		if (listOfValuesPtr_)
		{
			(*componentMapPtr_)[ComponentId::ListOfValues] = listOfValuesPtr_;
		}

		if (limitClausePtr_)
		{
			(*componentMapPtr_)[ComponentId::LimitClause] = limitClausePtr_;
		}

		if (offsetClausePtr_)
		{
			(*componentMapPtr_)[ComponentId::OffsetClause] = offsetClausePtr_;
		}

		if (groupByFieldListPtr_ and !groupByFieldListPtr_->empty())
		{
			(*componentMapPtr_)[ComponentId::GroupByFieldListWrapper] = std::make_shared<GroupByFieldListWrapper>(groupByFieldListPtr_);
		}

		if (orderByClauseListPtr_ and !orderByClauseListPtr_->empty())
		{
			(*componentMapPtr_)[ComponentId::OrderByClauseListWrapper] = std::make_shared<OrderByClauseListWrapper>(orderByClauseListPtr_);
		}

		if (queryListPtr_ and !queryListPtr_->empty())
		{
			(*componentMapPtr_)[ComponentId::QueryListWrapper] = std::make_shared<QueryListWrapper>(queryListPtr_);
		}
	}

/*
	void QueryBuilderImpl::addConditionToWhereChain(const ConditionBase& conditionBase, const LogicOperator logicOperator)
	{
		if (!isWhereChaining_)
		{
			using CC = std::remove_reference_t<decltype(*currentWhereChainPtr_)>;
			currentWhereChainPtr_ = std::make_shared<CC>();
			currentWhereChainPtr_->addCondition(conditionBase);
			isWhereChaining_ = true;
		}
		else
		{
			if (currentWhereChainPtr_->conditionBaseList().empty())
			{
				currentWhereChainPtr_->addCondition(conditionBase);
			}
			else
			{
				currentWhereChainPtr_->setLogicOperator(logicOperator);
				currentWhereChainPtr_->addCondition(conditionBase);
			}
		}
	}


	void QueryBuilderImpl::addConditionToHavingChain(const ConditionBase& conditionBase, const LogicOperator logicOperator)
	{
		if (!isHavingChaining_)
		{
			using CC = std::remove_reference_t<decltype(*currentHavingChainPtr_)>;
			currentHavingChainPtr_ = std::make_shared<CC>();
			currentHavingChainPtr_->addCondition(conditionBase);
			isHavingChaining_ = true;
		}
		else
		{
			if (currentHavingChainPtr_->conditionBaseList().empty())
			{
				currentHavingChainPtr_->addCondition(conditionBase);
			}
			else
			{
				currentHavingChainPtr_->setLogicOperator(logicOperator);
				currentHavingChainPtr_->addCondition(conditionBase);
			}
		}
	}
	*/
}
