// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:IBuilder;

import std;

import :BuilderTypes;

namespace DataAccessLayer::SqlQueryBuilder
{
	export class IBuilder
	{
	public:
		IBuilder() = default;
		virtual ~IBuilder() = default;

		[[nodiscard]] virtual DatabaseEngine databaseEngine() const = 0;
		[[nodiscard]] virtual String databaseEngineName() const = 0;

		// Query Builders
		virtual String buildQuery(QueryType queryType, const ComponentMap& componentMap) = 0;
		virtual String buildSelectQuery(const ComponentMap& componentMap) = 0;
		virtual String buildAppendQuery(const ComponentMap& componentMap) = 0;
		virtual String buildUpdateQuery(const ComponentMap& componentMap) = 0;
		virtual String buildDeleteQuery(const ComponentMap& componentMap) = 0;
		virtual String buildUnionQuery(const ComponentMap& componentMap) = 0;
		virtual String buildMakeTableQuery(const ComponentMap& componentMap) = 0;
		virtual String buildDataDefinitionQuery(const ComponentMap& componentMap) = 0;

		// Component Builders
		[[nodiscard]] virtual String buildComponent(const Aggregate& aggregate) const = 0;
		[[nodiscard]] virtual String buildComponent(const Alias& alias) const = 0;
		[[nodiscard]] virtual String buildComponent(const Expression& expression) const = 0;
		[[nodiscard]] virtual String buildComponent(const Field& field) const = 0;
//		[[nodiscard]] virtual String buildComponent(const FilterBase& filter) const = 0;
		[[nodiscard]] virtual String buildComponent(const ComparisonFilter& filter) const = 0;
		[[nodiscard]] virtual String buildComponent(const LogicalFilter& filter) const = 0;
		[[nodiscard]] virtual String buildComponent(const FilterSelectable& filterSelectable) const = 0;
		[[nodiscard]] virtual String buildComponent(const Function& scalarFunction) const = 0;
		[[nodiscard]] virtual String buildComponent(const JoinClause& joinClause) const = 0;
		[[nodiscard]] virtual String buildComponent(const LimitClause& limitClause) const = 0;
		[[nodiscard]] virtual String buildComponent(const ListOfValues& listOfValues) const = 0;
		[[nodiscard]] virtual String buildComponent(const Literal& literal) const = 0;
		[[nodiscard]] virtual String buildComponent(const OffsetClause& offsetClause) const = 0;
		[[nodiscard]] virtual String buildComponent(const OrderByClause& orderByClause) const = 0;
		[[nodiscard]] virtual String buildComponent(const Parameter& parameter) const = 0;
		[[nodiscard]] virtual String buildComponent(const ParameterSelectable& parameterSelectable) const = 0;
	//	[[nodiscard]] virtual String buildComponent(const Selectable& selectable) const = 0;
		[[nodiscard]] virtual String buildComponent(const Query& query) const = 0;
		[[nodiscard]] virtual String buildComponent(const QueryDataSource& queryDataSource) const = 0;
		[[nodiscard]] virtual String buildComponent(const QuerySelectable& subQuerySelectable) const = 0;
		[[nodiscard]] virtual String buildComponent(const Table& table) const = 0;
		[[nodiscard]] virtual String buildComponent(const TableDataSource& tableDataSource) const = 0;
		[[nodiscard]] virtual String buildComponent(const TopClause& topClause) const = 0;

		// Component Wrapper Builders
		[[nodiscard]] virtual String buildComponent(const DistinctWrapper& distinctWrapper) const = 0;
		[[nodiscard]] virtual String buildComponent(const SelectableListWrapper& selectableListWrapper) const = 0;
		[[nodiscard]] virtual String buildComponent(const WhereFilterWrapper& whereFilterWrapper) const = 0;
		[[nodiscard]] virtual String buildComponent(const JoinClauseListWrapper& joinClauseListWrapper) const = 0;
		[[nodiscard]] virtual String buildComponent(const GroupByFieldListWrapper& groupByFieldListWrapper) const = 0;
		[[nodiscard]] virtual String buildComponent(const HavingFilterWrapper& havingFilterWrapper) const = 0;
		[[nodiscard]] virtual String buildComponent(const OrderByClauseListWrapper& orderByClauseListWrapper) const = 0;
		[[nodiscard]] virtual String buildComponent(const QueryListWrapper& queryListWrapper) const = 0;
	};
}
