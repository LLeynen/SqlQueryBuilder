// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:ComponentWrappers;

import std;

import :BuilderTypes;
import :Variant;
import :Component;

namespace DataAccessLayer::SqlQueryBuilder
{
    // SelectableListWrapper
    export class SelectableListWrapper : public Component
    {
    public:
        SelectableListWrapper(const SelectableListPtr& selectableListPtr) noexcept;
        [[nodiscard]] SelectableListPtr selectableListPtr() const noexcept;

    protected:
        String toSql(const IBuilder* builderPtr) const override;

    private:
        SelectableListPtr selectableListPtr_;
    };

    // JoinClauseListWrapper
    export class JoinClauseListWrapper : public Component
    {
    public:
        JoinClauseListWrapper(const JoinClauseListPtr& joinClauseListPtr) noexcept;
        [[nodiscard]] JoinClauseListPtr joinClauseList() const noexcept;

    protected:
        String toSql(const IBuilder* builderPtr) const override;

    private:
        JoinClauseListPtr joinClauseListPtr_;
    };

    // WhereFilterWrapper
    export class WhereFilterWrapper : public Component
    {
    public:
        WhereFilterWrapper(const FilterPtr& filterPtr) noexcept;
        [[nodiscard]] FilterPtr filter() const noexcept;

    protected:
        String toSql(const IBuilder* builderPtr) const override;

    private:
        FilterPtr filterPtr_;
    };

    // GroupByFieldListWrapper
    export class GroupByFieldListWrapper : public Component
    {
    public:
        GroupByFieldListWrapper(const FieldListPtr& fieldListPtr) noexcept;
        [[nodiscard]] const FieldListPtr fieldList() const noexcept;

    protected:
        String toSql(const IBuilder* builderPtr) const override;

    private:
        FieldListPtr fieldListPtr_;
    };

    // HavingFilterWrapper
    export class HavingFilterWrapper : public Component
    {
    public:
        HavingFilterWrapper(FilterPtr  filterPtr) noexcept;
        [[nodiscard]] FilterPtr filter() const noexcept;

    protected:
        String toSql(const IBuilder* builderPtr) const override;

    private:
        FilterPtr filterPtr_;
    };

    // OrderByClauseListWrapper
    export class OrderByClauseListWrapper : public Component
    {
    public:
        OrderByClauseListWrapper(OrderByClauseListPtr  orderByClauseListPtr) noexcept;
        [[nodiscard]] OrderByClauseListPtr orderByClauseList() const noexcept;

    protected:
        String toSql(const IBuilder* builderPtr) const override;

    private:
        OrderByClauseListPtr orderByClauseListPtr_;
    };

    // QueryListWrapper
    export class QueryListWrapper : public Component
    {
    public:
        QueryListWrapper(QueryListPtr  queryListPtr) noexcept;
        [[nodiscard]] QueryListPtr queryList() const noexcept;

    protected:
        String toSql(const IBuilder* builderPtr) const override;

    private:
        QueryListPtr queryListPtr_;
    };

    // DistinctWrapper
    export class DistinctWrapper : public Component
    {
    public:
        DistinctWrapper(Variant  distinct) noexcept;
        [[nodiscard]] Variant distinct() const;

    protected:
        String toSql(const IBuilder* builderPtr) const override;

    private:
        Variant distinct_;
    };
}
