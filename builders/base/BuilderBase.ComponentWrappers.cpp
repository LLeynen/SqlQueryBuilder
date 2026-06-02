// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import std;

import :BuilderTypes;
import :ComponentWrappers;
import :Selectable;

namespace DataAccessLayer::SqlQueryBuilder
{
    String BuilderBase::buildComponent(const DistinctWrapper& distinctWrapper) const
    {
        String distinctWrapperString{};

        if (distinctWrapper.distinct().toBool())
        {
            distinctWrapperString = "DISTINCT ";
        }

        return distinctWrapperString;
    }


    String BuilderBase::buildComponent(const SelectableListWrapper& selectableListWrapper) const
    {
        String selectableListWrapperString{};

        if (selectableListWrapper.selectableListPtr()->empty())
        {
            selectableListWrapperString = "*";
        }
        else
        {
            const auto selectableListPtr = selectableListWrapper.selectableListPtr();

            for (size_t i = 0; i < selectableListPtr->size(); ++i)
            {
                const auto sqlSelectable = selectableListPtr->at(i);
                selectableListWrapperString += sqlSelectable->sql(this);

                if (i < selectableListPtr->size() - 1)
                {
                    selectableListWrapperString += ", ";
                }
            }
        }

        return selectableListWrapperString;
    }


    String BuilderBase::buildComponent(const WhereFilterWrapper& whereFilterWrapper) const
    {
        return whereFilterWrapper.filter()->clone()->sql(this);
    }


    String BuilderBase::buildComponent(const JoinClauseListWrapper& joinClauseListWrapper) const
    {
        String joinClauseListWrapperString{ " "};

        const auto joinClauseList = joinClauseListWrapper.joinClauseList();

        if (!joinClauseList->empty())
        {
            size_t joinCount = 1;

            for (size_t i = 0; i < joinClauseList->size(); ++i)
            {
                auto joinClause = joinClauseList->at(i);
                joinClauseListWrapperString = joinClauseListWrapperString + joinClause->sql(this) + " ";
            }
        }

        return joinClauseListWrapperString;
    }


    String BuilderBase::buildComponent(const GroupByFieldListWrapper& groupByFieldListWrapper) const
    {
        String groupByFieldListWrapperString{};

        if (const auto fieldList = groupByFieldListWrapper.fieldList(); !fieldList->empty())
        {
            for (size_t i = 0; i < groupByFieldListWrapper.fieldList()->size(); ++i)
            {
                const auto field = fieldList->at(i);
                groupByFieldListWrapperString += field->sql(this);

                if (i < fieldList->size() - 1)
                {
                    groupByFieldListWrapperString += ", ";
                }
            }
        }

        return groupByFieldListWrapperString;
    }


    String BuilderBase::buildComponent(const HavingFilterWrapper& havingFilterWrapper) const
    {
        return havingFilterWrapper.filter()->clone()->sql(this);
    }


    String BuilderBase::buildComponent(const OrderByClauseListWrapper& orderByClauseListWrapper) const
    {
        String orderByClauseListWrapperString{};

        if (const auto orderByClauseList = orderByClauseListWrapper.orderByClauseList(); !orderByClauseList->empty())
        {
            for (size_t i = 0; i < orderByClauseList->size(); ++i)
            {
                const auto orderByClause = orderByClauseList->at(i);
                orderByClauseListWrapperString += orderByClause->sql(this);

                if (i < orderByClauseList->size() - 1)
                {
                    orderByClauseListWrapperString += ", ";
                }
            }
        }

        return orderByClauseListWrapperString;
    }


    String BuilderBase::buildComponent(const QueryListWrapper& queryListWrapper) const
    {
        String queryListWrapperString{};

        if (const auto queryList = queryListWrapper.queryList(); !queryList->empty())
        {
            for (size_t i = 0; i < queryListWrapper.queryList()->size(); ++i)
            {
                const auto query = queryList->at(i);
                queryListWrapperString += query->sql(this);

                if (i < queryList->size() - 1)
                {
                    queryListWrapperString += "; ";
                }
            }
        }

        return queryListWrapperString;
    }
}
