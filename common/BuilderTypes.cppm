// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

export module QueryBuilder:BuilderTypes;

import std;

export import :Enums;
export import :String;

export namespace DataAccessLayer::SqlQueryBuilder
{
	// Forward declarations of components
	class Aggregate;
	class Alias;
	class BuilderBase;
	class BuilderFactory;
	class Component;
	class DataSource;
	class Expression;
	class Field;
	class FieldRef;
	class ComparisonFilter;
	class FilterBase;
	class FilterSelectable;
	class Function;
	class IBuilder;
	class JoinClause;
	class LimitClause;
	class ListOfValues;
	class Literal;
	class LogicalFilter;
	class OffsetClause;
	class Operand;
	class OrderByClause;
	class Parameter;
	class ParameterRegistry;
	class ParameterSelectable;
	class Query;
	class QueryBuilder;
	class QueryDataSource;
	class QuerySelectable;
	class Selectable;
	class Table;
	class TableDataSource;
	class TopClause;
	class Variant;

	// Forward declarations of wrapper classes
	class DistinctWrapper;
	class SelectableListWrapper;
	class FieldListWrapper;
	class WhereFilterWrapper;
	class JoinClauseListWrapper;
	class GroupByFieldListWrapper;
	class HavingFilterWrapper;
	class OrderByClauseListWrapper;
	class QueryListWrapper;

	export using FilterValue = std::variant
		<
			std::nullptr_t,
			Variant,
			Parameter,
			ListOfValues,
			Query,
			String,
			const char*
		>;

	export using ComparisonValue = std::variant
		<
			std::monostate,
			Operand,
			FilterValue
		>;

	export using FormulaValue = std::variant
	<
		Variant,
		Parameter,
		String,
		const char*
	>;

	export using FormulaArg = std::variant
	<
		std::monostate,
		Operand,
		FormulaValue
	>;

	// Aliases for shared pointers to classes
	using AggregatePtr = std::shared_ptr<Aggregate>;
	using AliasPtr = std::shared_ptr<Alias>;
	using ComparisonFilterPtr = std::shared_ptr<ComparisonFilter>;
	using ComponentPtr = std::shared_ptr<Component>;
	using DataSourcePtr = std::shared_ptr<DataSource>;
	using ExpressionPtr = std::shared_ptr<Expression>;
	using FieldPtr = std::shared_ptr<Field>;
	using FilterBasePtr = std::shared_ptr<FilterBase>;
	using FilterSelectablePtr = std::shared_ptr<FilterSelectable>;
	using IBuilderPtr = std::shared_ptr<IBuilder>;
	using JoinClausePtr = std::shared_ptr<JoinClause>;
	using LimitClausePtr = std::shared_ptr<LimitClause>;
	using ListOfValuesPtr = std::shared_ptr<ListOfValues>;
	using LiteralPtr = std::shared_ptr<Literal>;
	using LogicalFilterPtr = std::shared_ptr<LogicalFilter>;
	using OffsetClausePtr = std::shared_ptr<OffsetClause>;
	using OperandPtr = std::shared_ptr<Operand>;
	using OrderByClausePtr = std::shared_ptr<OrderByClause>;
	using ParameterPtr = std::shared_ptr<Parameter>;
	using ParameterSelectablePtr = std::shared_ptr<ParameterSelectable>;
	using QueryPtr = std::shared_ptr<Query>;
	using QueryDataSourcePtr = std::shared_ptr<QueryDataSource>;
	using QueryBuilderPtr = std::shared_ptr<QueryBuilder>;
	using QuerySelectablePtr = std::shared_ptr<QuerySelectable>;
	using SelectablePtr = std::shared_ptr<Selectable>;
	using TablePtr = std::shared_ptr<Table>;
	using TableDataSourcePtr = std::shared_ptr<TableDataSource>;
	using TopClausePtr = std::shared_ptr<TopClause>;
	using VariantPtr = std::shared_ptr<Variant>;

	// Aliases for containers of shared pointers
	using SelectableList = std::vector<SelectablePtr>;
	using SelectableListPtr = std::shared_ptr<SelectableList>;
	using TableList = std::vector<TablePtr>;
	using TableListPtr = std::shared_ptr<TableList>;
	using JoinClauseList = std::vector<JoinClausePtr>;
	using JoinClauseListPtr = std::shared_ptr<JoinClauseList>;
	using FieldList = std::vector<FieldPtr>;
	using FieldListPtr = std::shared_ptr<FieldList>;
	using OperandList = std::vector<OperandPtr>;	//???
	using OperandListPtr = std::shared_ptr<OperandList>;
	using OrderByClauseList = std::vector<OrderByClausePtr>;
	using OrderByClauseListPtr = std::shared_ptr<OrderByClauseList>;
	using QueryList = std::vector<QueryPtr>;
	using QueryListPtr = std::shared_ptr<QueryList>;
	using ComponentMap = std::unordered_map<ComponentId, ComponentPtr>;
	using ComponentMapPtr = std::shared_ptr<ComponentMap>;
	using BuilderFactoryMap = std::unordered_map<DatabaseEngine, IBuilderPtr>;
	using ParameterRegistryMap = std::unordered_map<String, Variant>;
	using DistinctWrapperPtr = std::shared_ptr<DistinctWrapper>;
	using SelectableListWrapperPtr = std::shared_ptr<SelectableListWrapper>;
	using WhereFilterWrapperPtr = std::shared_ptr<WhereFilterWrapper>;
	using JoinClauseListWrapperPtr = std::shared_ptr<JoinClauseListWrapper>;
	using GroupByFieldListWrapperPtr = std::shared_ptr<GroupByFieldListWrapper>;
	using HavingFilterWrapperPtr = std::shared_ptr<HavingFilterWrapper>;
	using OrderByClauseListWrapperPtr = std::shared_ptr<OrderByClauseListWrapper>;
	using QueryListWrapperPtr = std::shared_ptr<QueryListWrapper>;
}
