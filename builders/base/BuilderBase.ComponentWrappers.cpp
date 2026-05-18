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
            auto selectableListPtr = selectableListWrapper.selectableListPtr();
            for (size_t i = 0; i < selectableListPtr->size(); ++i)
            {
                auto sqlSelectable = (*selectableListPtr).at(i);
                selectableListWrapperString += buildComponent(*sqlSelectable);
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
        String whereFilterWrapperString{ };

        whereFilterWrapperString = buildComponent(*whereFilterWrapper.filter());

        return whereFilterWrapperString;
    }


    String BuilderBase::buildComponent(const JoinClauseListWrapper& joinClauseListWrapper) const
    {
        String joinClauseListWrapperString{};

        auto joinClauseList = joinClauseListWrapper.joinClauseList();

        if (!joinClauseList->empty())
        {
            size_t joinCount = 1;
            for (size_t i = 0; i < joinClauseList->size(); ++i)
            {
                if (joinCount == 1)
                {
                    auto joinClause = joinClauseList->at(0);
                    joinClauseListWrapperString += " " + buildComponent(*joinClause);
                }
                else
                {
                    auto joinClause = joinClauseList->at(i);
                    joinClauseListWrapperString = "(" + joinClauseListWrapperString + ") " + buildComponent(*joinClause);
                }
                joinCount++;
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
                auto field = fieldList->at(i);
                groupByFieldListWrapperString += buildComponent(*field);
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
        String havingFilterWrapperString{ };

        havingFilterWrapperString = buildComponent(*havingFilterWrapper.filter());

        return havingFilterWrapperString;
    }


    String BuilderBase::buildComponent(const OrderByClauseListWrapper& orderByClauseListWrapper) const
    {
        String orderByClauseListWrapperString{};

        if (auto orderByClauseList = orderByClauseListWrapper.orderByClauseList(); !orderByClauseList->empty())
        {
            for (size_t i = 0; i < orderByClauseList->size(); ++i)
            {
                auto orderByClause = orderByClauseList->at(i);
                orderByClauseListWrapperString += buildComponent(*orderByClause);
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

        if (auto queryList = queryListWrapper.queryList(); !queryList->empty())
        {
            for (size_t i = 0; i < queryListWrapper.queryList()->size(); ++i)
            {
                auto query = queryList->at(i);
                queryListWrapperString += buildComponent(*query);

                if (i < queryList->size() - 1)
                {
                    queryListWrapperString += "; ";
                }
            }
        }

        return queryListWrapperString;
    }
}
