// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:BuilderBase;

import :BuilderTypes;
import :IBuilder;

namespace DataAccessLayer::SqlQueryBuilder
{
    export class BuilderBase : public IBuilder
    {
    public:
        BuilderBase();
        explicit BuilderBase(DatabaseEngine databaseEngine);
        ~BuilderBase() override = default;

	    [[nodiscard]] DatabaseEngine databaseEngine()const noexcept override;
        [[nodiscard]] String databaseEngineName() const override;

        // Query Builders
        String buildQuery(QueryType queryType, const ComponentMap& componentMap) override;
        String buildSelectQuery(const ComponentMap& componentMap) override;
        String buildAppendQuery(const ComponentMap& componentMap) override;
        String buildUpdateQuery(const ComponentMap& componentMap) override;
        String buildDeleteQuery(const ComponentMap& componentMap) override;
        String buildUnionQuery(const ComponentMap& componentMap) override;
        String buildMakeTableQuery(const ComponentMap& componentMap) override;
        String buildDataDefinitionQuery(const ComponentMap& componentMap) override;

        // Component Builders
        [[nodiscard]] String buildComponent(const Aggregate& aggregate) const override;
        [[nodiscard]] String buildComponent(const Alias& alias) const override;
        [[nodiscard]] String buildComponent(const Expression& expression) const override;
        [[nodiscard]] String buildComponent(const Field& field) const override;
        [[nodiscard]] String buildComponent(const ComparisonFilter& filter) const override;
        [[nodiscard]] String buildComponent(const LogicalFilter& filter) const override;
        [[nodiscard]] String buildComponent(const FilterSelectable& filterSelectable) const override;
		[[nodiscard]] String buildComponent(const Function& scalarFunction) const override;
        [[nodiscard]] String buildComponent(const JoinClause& joinClause) const override;
        [[nodiscard]] String buildComponent(const LimitClause& limitClause) const override;
        [[nodiscard]] String buildComponent(const ListOfValues& listOfValues) const override;
        [[nodiscard]] String buildComponent(const Literal& literal) const override;
        [[nodiscard]] String buildComponent(const OffsetClause& offsetClause) const override;
        [[nodiscard]] String buildComponent(const OrderByClause& orderByClause) const override;
        [[nodiscard]] String buildComponent(const Parameter& parameter) const override;
		[[nodiscard]] String buildComponent(const ParameterSelectable& parameterSelectable) const override;
        [[nodiscard]] String buildComponent(const Query& query) const override;
        [[nodiscard]] String buildComponent(const QueryDataSource& queryDataSource) const override;
        [[nodiscard]] String buildComponent(const QuerySelectable& querySelectable) const override;
        [[nodiscard]] String buildComponent(const Table& table) const override;
        [[nodiscard]] String buildComponent(const TableDataSource& tableDataSource) const override;
        [[nodiscard]] String buildComponent(const TopClause& topClause) const override;

        // Component Wrapper Builders
        [[nodiscard]] String buildComponent(const DistinctWrapper& distinctWrapper) const override;
        [[nodiscard]] String buildComponent(const SelectableListWrapper& selectableListWrapper) const override;
        [[nodiscard]] String buildComponent(const WhereFilterWrapper& whereFilterWrapper) const override;
        [[nodiscard]] String buildComponent(const JoinClauseListWrapper& joinClauseListWrapper) const override;
        [[nodiscard]] String buildComponent(const GroupByFieldListWrapper& groupByFieldListWrapper) const override;
        [[nodiscard]] String buildComponent(const HavingFilterWrapper& havingFilterWrapper) const override;
        [[nodiscard]] String buildComponent(const OrderByClauseListWrapper& orderByClauseListWrapper) const override;
        [[nodiscard]] String buildComponent(const QueryListWrapper& queryListWrapper) const override;

        void setupEngineParams() override;

    private:
        DatabaseEngine databaseEngine_{};
    };
}
