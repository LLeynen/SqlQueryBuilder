// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :ComponentWrappers;

import std;

import :BuilderTypes;
import :IBuilder;
import :Variant;

namespace DataAccessLayer::SqlQueryBuilder
{
    SelectableListWrapper::SelectableListWrapper(SelectableListPtr selectableListPtr) noexcept
        : Component(ComponentId::SelectableListWrapper)
        , selectableListPtr_(std::move(selectableListPtr))
    {}

    SelectableListPtr SelectableListWrapper::selectableListPtr() const noexcept
    {
        return selectableListPtr_;
    }

    String SelectableListWrapper::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }

    JoinClauseListWrapper::JoinClauseListWrapper(JoinClauseListPtr joinClauseListPtr) noexcept
        : Component(ComponentId::JoinClauseListWrapper)
        , joinClauseListPtr_(std::move(joinClauseListPtr))
    {}


    JoinClauseListPtr JoinClauseListWrapper::joinClauseList() const noexcept
    {
        return joinClauseListPtr_;
    }


    String JoinClauseListWrapper::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }


    WhereFilterWrapper::WhereFilterWrapper(FilterBasePtr filterBasePtr) noexcept
        : Component(ComponentId::WhereFilterWrapper)
        , filterPtr_(std::move(filterBasePtr))
    {}


    FilterBasePtr WhereFilterWrapper::filter() const noexcept
    {
        return filterPtr_;
    }


    String WhereFilterWrapper::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }


    GroupByFieldListWrapper::GroupByFieldListWrapper(FieldListPtr fieldListPtr) noexcept
        : Component(ComponentId::GroupByFieldListWrapper)
        , fieldListPtr_(std::move(fieldListPtr))
    {}


    FieldListPtr GroupByFieldListWrapper::fieldList() const noexcept
    {
        return fieldListPtr_;
    }


    String GroupByFieldListWrapper::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }


    HavingFilterWrapper::HavingFilterWrapper(FilterBasePtr filterPtr) noexcept
        : Component(ComponentId::HavingFilterWrapper)
        , filterPtr_(std::move(filterPtr))
    {}


    FilterBasePtr HavingFilterWrapper::filter() const noexcept
    {
        return filterPtr_;
    }


    String HavingFilterWrapper::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }


    OrderByClauseListWrapper::OrderByClauseListWrapper(OrderByClauseListPtr orderByClauseListPtr) noexcept
        : Component(ComponentId::OrderByClauseListWrapper)
        , orderByClauseListPtr_(std::move(orderByClauseListPtr))
    {}


    OrderByClauseListPtr OrderByClauseListWrapper::orderByClauseList() const noexcept
    {
        return orderByClauseListPtr_;
    }


    String OrderByClauseListWrapper::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }


    QueryListWrapper::QueryListWrapper(QueryListPtr queryListPtr) noexcept
        : Component(ComponentId::QueryListWrapper)
        , queryListPtr_(std::move(queryListPtr))
    {}


    QueryListPtr QueryListWrapper::queryList() const noexcept
    {
        return queryListPtr_;
    }


    String QueryListWrapper::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }


    DistinctWrapper::DistinctWrapper(Variant distinct) noexcept
        : Component(ComponentId::DistinctWrapper)
        , distinct_(std::move(distinct))
    {}


    Variant DistinctWrapper::distinct() const
    {
        return distinct_;
    }


    String DistinctWrapper::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }
}
