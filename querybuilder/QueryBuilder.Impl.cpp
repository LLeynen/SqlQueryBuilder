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
}
