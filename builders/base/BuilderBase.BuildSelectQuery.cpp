// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import std;

import :BuilderTypes;
import :ComponentWrappers;
import :TopClause;
import :LimitClause;
import :OffsetClause;
import :DataSource;

namespace DataAccessLayer::SqlQueryBuilder
{
   String BuilderBase::buildSelectQuery(const ComponentMap& componentMap)
    {
        String sqlStatement{ "SELECT " };

        // distinct
        auto it = componentMap.find(ComponentId::DistinctWrapper);
        if (it != componentMap.end())
        {
            if (auto distinctWrapperPtr = std::dynamic_pointer_cast<DistinctWrapper>(it->second))
            {
                sqlStatement += distinctWrapperPtr->sql(this);
            }
        }

        // top clause
        it = componentMap.find(ComponentId::TopClause);
        if (it != componentMap.end())
        {
            if (auto topClausePtr = std::dynamic_pointer_cast<TopClause>(it->second))
            {
                sqlStatement += topClausePtr->sql(this);
            }
        }

        // selectables
        it = componentMap.find(ComponentId::SelectableListWrapper);
        if (it == componentMap.end())
        {
            throw std::runtime_error("No selectable items for SELECT query");
        }

        if (auto selectableListWrapperPtr = std::dynamic_pointer_cast<SelectableListWrapper>(it->second))
        {
            sqlStatement += selectableListWrapperPtr->sql(this);
        }

        // from
        String fromClause{ };

        it = componentMap.find(ComponentId::DataSource);
        if (it != componentMap.end())
        {
            if (auto dataSourcePtr = std::dynamic_pointer_cast<DataSource>(it->second))
            {
                fromClause += dataSourcePtr->sql(this);
            }
        }

        // join
        it = componentMap.find(ComponentId::JoinClauseListWrapper);
        if (it != componentMap.end())
        {
            if (auto joinClauseListWrapperPtr = std::dynamic_pointer_cast<JoinClauseListWrapper>(it->second))
            {
                fromClause += joinClauseListWrapperPtr->sql(this);
            }
        }

        sqlStatement += " FROM " + fromClause;

        // where
        it = componentMap.find(ComponentId::WhereFilterWrapper);
        if (it != componentMap.end())
        {
            if (auto whereFilterWrapperPtr = std::dynamic_pointer_cast<WhereFilterWrapper>(it->second))
            {
                sqlStatement += " WHERE " + whereFilterWrapperPtr->sql(this);
            }
        }

        // group by
        it = componentMap.find(ComponentId::GroupByFieldListWrapper);
        if (it != componentMap.end())
        {
            if (auto groupByFieldListWrapperPtr = std::dynamic_pointer_cast<GroupByFieldListWrapper>(it->second))
            {
                sqlStatement += " GROUP BY " + groupByFieldListWrapperPtr->sql(this);
            }
        }

        // having
        it = componentMap.find(ComponentId::HavingFilterWrapper);
        if (it != componentMap.end())
        {
            if (auto havingFilterWrapperPtr = std::dynamic_pointer_cast<HavingFilterWrapper>(it->second))
            {
                sqlStatement += " HAVING " + havingFilterWrapperPtr->sql(this);
            }
        }

        // order by
        it = componentMap.find(ComponentId::OrderByClauseListWrapper);
        if (it != componentMap.end())
        {
            if (auto orderByClauseListWrapperPtr = std::dynamic_pointer_cast<OrderByClauseListWrapper>(it->second))
            {
                sqlStatement += " ORDER BY " + orderByClauseListWrapperPtr->sql(this);
            }
        }

        // limit
        it = componentMap.find(ComponentId::LimitClause);
        if (it != componentMap.end())
        {
            if (auto sqlLimitClausePtr = std::dynamic_pointer_cast<LimitClause>(it->second))
            {
                sqlStatement += sqlLimitClausePtr->sql(this);
            }
        }

        // offset
        it = componentMap.find(ComponentId::OffsetClause);
        if (it != componentMap.end())
        {
            if (auto sqlOffsetClausePtr = std::dynamic_pointer_cast<OffsetClause>(it->second))
            {
                sqlStatement += sqlOffsetClausePtr->sql(this);
            }
        }

        return sqlStatement;
    }
}
