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
    export class SelectableListWrapper : public Component
    {
    public:
        SelectableListWrapper(SelectableListPtr selectableListPtr) noexcept;
        [[nodiscard]] SelectableListPtr selectableListPtr() const noexcept;

    protected:
        String toSql(const IBuilder* builderPtr) const override;

    private:
        SelectableListPtr selectableListPtr_;
    };


    export class JoinClauseListWrapper : public Component
    {
    public:
        JoinClauseListWrapper(JoinClauseListPtr  joinClauseListPtr) noexcept;
        [[nodiscard]] JoinClauseListPtr joinClauseList() const noexcept;

    protected:
        String toSql(const IBuilder* builderPtr) const override;

    private:
        JoinClauseListPtr joinClauseListPtr_;
    };


    export class WhereFilterWrapper : public Component
    {
    public:
        WhereFilterWrapper(FilterBasePtr filterPtr) noexcept;
        [[nodiscard]] FilterBasePtr filter() const noexcept;

    protected:
        String toSql(const IBuilder* builderPtr) const override;

    private:
        FilterBasePtr filterPtr_;
    };


    export class GroupByFieldListWrapper : public Component
    {
    public:
        GroupByFieldListWrapper(FieldListPtr  fieldListPtr) noexcept;
        [[nodiscard]] FieldListPtr fieldList() const noexcept;

    protected:
        String toSql(const IBuilder* builderPtr) const override;

    private:
        FieldListPtr fieldListPtr_;
    };


    export class HavingFilterWrapper : public Component
    {
    public:
        HavingFilterWrapper(FilterBasePtr filterPtr) noexcept;
        [[nodiscard]] FilterBasePtr filter() const noexcept;

    protected:
        String toSql(const IBuilder* builderPtr) const override;

    private:
        FilterBasePtr filterPtr_;
    };


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
