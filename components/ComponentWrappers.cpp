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
	// SelectableListWrapper::SelectableListWrapper
    SelectableListWrapper::SelectableListWrapper(const SelectableListPtr& selectableListPtr) noexcept
        : Component(ComponentId::SelectableListWrapper)
        , selectableListPtr_(selectableListPtr)
    {}

	// SelectableListWrapper::selectableListPtr
    SelectableListPtr SelectableListWrapper::selectableListPtr() const noexcept
    {
        return selectableListPtr_;
    }

	// SelectableListWrapper::toSql
    String SelectableListWrapper::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }

	// JoinClauseListWrapper::JoinClauseListWrapper
    JoinClauseListWrapper::JoinClauseListWrapper(const JoinClauseListPtr& joinClauseListPtr) noexcept
        : Component(ComponentId::JoinClauseListWrapper)
        , joinClauseListPtr_(joinClauseListPtr)
    {}

	// JoinClauseListWrapper::joinClauseList
    JoinClauseListPtr JoinClauseListWrapper::joinClauseList() const noexcept
    {
        return joinClauseListPtr_;
    }

	// JoinClauseListWrapper::toSql
    String JoinClauseListWrapper::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }

	// WhereFilterWrapper::WhereFilterWrapper
    WhereFilterWrapper::WhereFilterWrapper(const FilterPtr& filterPtr) noexcept
        : Component(ComponentId::WhereFilterWrapper)
        , filterPtr_(filterPtr)
    {}

	// WhereFilterWrapper::filter
    FilterPtr WhereFilterWrapper::filter() const noexcept
    {
        return filterPtr_;
    }

	// WhereFilterWrapper::toSql
    String WhereFilterWrapper::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }

    // GroupByFieldListWrapper
    GroupByFieldListWrapper::GroupByFieldListWrapper(const FieldListPtr& fieldListPtr) noexcept
        : Component(ComponentId::GroupByFieldListWrapper)
        , fieldListPtr_(fieldListPtr)
    {}

	// GroupByFieldListWrapper::fieldList
    const FieldListPtr GroupByFieldListWrapper::fieldList() const noexcept
    {
        return fieldListPtr_;
    }

	// GroupByFieldListWrapper::toSql
    String GroupByFieldListWrapper::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }

	// HavingFilterWrapper::HavingFilterWrapper
    HavingFilterWrapper::HavingFilterWrapper(FilterPtr  filterPtr) noexcept
        : Component(ComponentId::HavingFilterWrapper)
        , filterPtr_(std::move(filterPtr))
    {}

	// HavingFilterWrapper::filter
    FilterPtr HavingFilterWrapper::filter() const noexcept
    {
        return filterPtr_;
    }

	// HavingFilterWrapper::toSql
    String HavingFilterWrapper::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }

	// OrderByClauseListWrapper::OrderByClauseListWrapper
    OrderByClauseListWrapper::OrderByClauseListWrapper(OrderByClauseListPtr  orderByClauseListPtr) noexcept
        : Component(ComponentId::OrderByClauseListWrapper)
        , orderByClauseListPtr_(std::move(orderByClauseListPtr))
    {}

	// OrderByClauseListWrapper::orderByClauseList
    OrderByClauseListPtr OrderByClauseListWrapper::orderByClauseList() const noexcept
    {
        return orderByClauseListPtr_;
    }

	// OrderByClauseListWrapper::toSql
    String OrderByClauseListWrapper::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }

	// QueryListWrapper::QueryListWrapper
    QueryListWrapper::QueryListWrapper(QueryListPtr  queryListPtr) noexcept
        : Component(ComponentId::QueryListWrapper)
        , queryListPtr_(std::move(queryListPtr))
    {}

	// QueryListWrapper::queryList
    QueryListPtr QueryListWrapper::queryList() const noexcept
    {
        return queryListPtr_;
    }

	// QueryListWrapper::toSql
    String QueryListWrapper::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }

	// DistinctWrapper::DistinctWrapper
    DistinctWrapper::DistinctWrapper(Variant  distinct) noexcept
        : Component(ComponentId::DistinctWrapper)
        , distinct_(std::move(distinct))
    {}

	// DistinctWrapper::distinct
    Variant DistinctWrapper::distinct() const
    {
        return distinct_;
    }

	// DistinctWrapper::toSql
    String DistinctWrapper::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }
}
