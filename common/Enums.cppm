// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:Enums;

namespace DataAccessLayer::SqlQueryBuilder
{
	// QueryType
	export enum class QueryType
	{
		SelectQuery,
		AppendQuery,
		UpdateQuery,
		DeleteQuery,
		MakeTableQuery,
		UnionQuery,
		DataDefinitionQuery,
		CrosstabQuery
	};

	// DatabaseEngine 
	export enum class DatabaseEngine
	{
		MariaDB,
		MySQL,
		Oracle,
		PostgreSQL,
		SQLite,
		SQLServer,
		Access,
		AnsiSQL
	};

	// ComponentId 
	export enum class ComponentId
	{
		// Component classes
		Aggregate,
		Alias,
		Function,
		ComparisonFilter,
		DataSource,
		Distinct,
		Expression,
		Field,
		FilterBase,
		FilterSelectable,
		JoinClause,
		LimitClause,
		ListOfValues,
		Literal,
		LogicalFilter,
		OffsetClause,
		OrderByClause,
		Parameter,
		ParameterSelectable,
		ParameterValue,
		Query,
		QueryDataSource,
		QuerySelectable,
		Selectable,
		Table,
		TableDataSource,
		TopClause,

		// Component Wrappers
		SelectableListWrapper,
		WhereFilterWrapper,
		JoinClauseListWrapper,
		GroupByFieldListWrapper,
		HavingFilterWrapper,
		OrderByClauseListWrapper,
		QueryListWrapper,
		DistinctWrapper
	};

	// Comparison 
	export enum class Comparison
	{
		Equals,
		NotEquals,
		Not,
		Like,
		NotLike,
		GreaterThan,
		GreaterOrEquals,
		LessThan,
		LessOrEquals,
		In,
		NotIn,
		Between,
		Exists,
		NotExists,
		Any,
		Some,
		All
	};

	// LogicOperator 
	export enum class LogicOperator
	{
		And,
		Or,
		Not
	};

	// JoinType
	export enum class JoinType
	{
		InnerJoin,
		OuterJoin,
		LeftJoin,
		RightJoin
	};

	// SortOrder 
	export enum class SortOrder
	{
		Ascending,
		Descending
	};

	// AggregateFunction 
	export enum class AggregateFunction
	{
		Sum,
		Avg,
		Min,
		Max,
		Count,
		StdDev,
		Var,
		First,
		Last
	};

	// ScalarFunction
	export enum class ScalarFunction
	{
		// String
		Upper,
		Lower,
		Length,
		Trim,
		Substring,
		Replace,
		Concat,
		Instr,

		// Numeric
		Abs,
		Ceil,
		Floor,
		Round,
		Power,
		Sqrt,
		Random,

		// Date/Time
		Now,
		CurrentDate,
		CurrentTime,
		Year,
		DateDiff,
		DateAdd,

		// Conversion
		Cast,
		DateFormat,

		// Null Handling
		IfNull,
		Coalesce
	};

	// Operator
	export enum class Operator
	{
		Add,
		Subtract,
		Multiply,
		Divide,
		Modulus
	};

	// TopUnit 
	export enum class TopUnit
	{
		Records,
		Percent
	};
} // DataAccessLayer::SqlQueryBuilder
