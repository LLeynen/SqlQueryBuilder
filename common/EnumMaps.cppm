// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:EnumMaps;

import :EnumMap;
import :Enums;

namespace DataAccessLayer::SqlQueryBuilder
{
	// SqlQueryTypeMap
	export const EnumMap<QueryType> QueryTypeMap
	{
		{ QueryType::SelectQuery, "Select Query" },
		{ QueryType::AppendQuery, "Append Query" },
		{ QueryType::UpdateQuery, "Update Query" },
		{ QueryType::DeleteQuery, "Delete Query" },
		{ QueryType::MakeTableQuery, "Make Table Query" },
		{ QueryType::UnionQuery, "Union Query" },
		{ QueryType::DataDefinitionQuery, "Data Definition Query" },
		{ QueryType::CrosstabQuery, "Crosstab Query" }
	};

	// DatabaseEngineMap
	export const EnumMap<DatabaseEngine> DatabaseEngineMap
	{
		{ DatabaseEngine::MariaDB, "MariaDB" },
		{ DatabaseEngine::MySQL, "MySQL" },
		{ DatabaseEngine::Oracle, "Oracle" },
		{ DatabaseEngine::PostgreSQL, "PostgreSQL" },
		{ DatabaseEngine::SQLite, "SQLite" },
		{ DatabaseEngine::SQLServer, "SQLServer" },
		{ DatabaseEngine::Access, "Access" },
		{ DatabaseEngine::AnsiSQL, "AnsiSQL" }
	};

	// ComponentIdMap
	export const EnumMap<ComponentId> ComponentIdMap
	{
		// Individual component classes
		{ ComponentId::Aggregate, "Aggregate" },
		{ ComponentId::Alias, "Alias" },
		{ ComponentId::CompositeCondition, "CompositeCondition" },
		{ ComponentId::Condition, "Condition" },
		{ ComponentId::ConditionBase, "ConditionBase" },
		{ ComponentId::DataSource, "DataSource" },
		{ ComponentId::Distinct, "Distinct" },
		{ ComponentId::Expression, "Expression" },
		{ ComponentId::Field, "Field" },
		{ ComponentId::Filter, "Filter" },
		{ ComponentId::JoinClause, "JoinClause" },
		{ ComponentId::LimitClause, "LimitClause" },
		{ ComponentId::ListOfValues, "ListOfValues" },
		{ ComponentId::Literal, "Literal" },
		{ ComponentId::OffsetClause, "OffsetClause" },
		{ ComponentId::OrderByClause, "OrderByClause" },
		{ ComponentId::Parameter, "Parameter" },
		{ ComponentId::ParameterSelectable, "ParameterSelectable" },
		{ ComponentId::ParameterValue, "ParameterValue" },
		{ ComponentId::Query, "Query" },
		{ ComponentId::QueryDataSource, "QueryDataSource" },
		{ ComponentId::QuerySelectable, "QuerySelectable" },
		{ ComponentId::Selectable, "Selectable" },
		{ ComponentId::Table, "Table" },
		{ ComponentId::TableDataSource, "TableDataSource" },
		{ ComponentId::TopClause, "TopClause" },

		// Component Wrappers
		{ ComponentId::SelectableListWrapper, "SelectableListWrapper" },
		{ ComponentId::WhereFilterWrapper, "WhereFilterWrapper" },
		{ ComponentId::JoinClauseListWrapper, "JoinClauseListWrapper" },
		{ ComponentId::GroupByFieldListWrapper, "GroupByFieldListWrapper" },
		{ ComponentId::HavingFilterWrapper, "HavingFilterWrapper" },
		{ ComponentId::OrderByClauseListWrapper, "OrderByClauseListWrapper" },
		{ ComponentId::QueryListWrapper, "QueryListWrapper" },
		{ ComponentId::DistinctWrapper, "DistinctWrapper" }
	};

	// ComparisonMap
	export const EnumMap<Comparison> ComparisonMap
	{
		{ Comparison::Equals, "="},
		{ Comparison::NotEquals, "<>"},
		{ Comparison::Like, "Like"},
		{ Comparison::NotLike, "Not Like"},
		{ Comparison::GreaterThan, ">"},
		{ Comparison::GreaterOrEquals, ">="},
		{ Comparison::LessThan, "<"},
		{ Comparison::LessOrEquals , "<="},
		{ Comparison::In, "In"},
		{ Comparison::NotIn, "Not In"},
		{ Comparison::Between, "Between"},
		{ Comparison::Exists, "Exists"},
		{ Comparison::NotExists, "Not Exists"},
		{ Comparison::Any, "Any"},
		{ Comparison::Some, "Some"},
		{ Comparison::All, "All"}
	};

	// LogicOperatorMap
	export const EnumMap<LogicOperator> LogicOperatorMap
	{
		{ LogicOperator::And, "And" },
		{ LogicOperator::Or, "Or" }
	};

	// JoinTypeMap
	export const EnumMap<JoinType> JoinTypeMap
	{
		{ JoinType::InnerJoin, "Inner Join" },
		{ JoinType::OuterJoin, "Outer Join" },
		{ JoinType::LeftJoin, "Left Join" },
		{ JoinType::RightJoin, "Right Join" }
	};

	// SortOrderMap
	export const EnumMap<SortOrder> SortOrderMap
	{
		{ SortOrder::Ascending, "Asc" },
		{ SortOrder::Descending, "Desc" }
	};

	// AggregateFunctionMap
	export const EnumMap<AggregateFunction> AggregateFunctionMap
	{
		{ AggregateFunction::Sum, "Sum" },
		{ AggregateFunction::Avg, "Avg" },
		{ AggregateFunction::Min, "Min" },
		{ AggregateFunction::Max, "Max" },
		{ AggregateFunction::Count, "Count" },
		{ AggregateFunction::StdDev, "StdDev" },
		{ AggregateFunction::Var, "Var" },
		{ AggregateFunction::First, "First" },
		{ AggregateFunction::Last, "Last" }
	};

	export const EnumMap<ScalarFunction> ScalarFunctionMap
	{
		// String
		{ ScalarFunction::Upper, "Upper" },
		{ ScalarFunction::Lower, "Lower" },
		{ ScalarFunction::Length, "Length"},
		{ ScalarFunction::Trim, "Trim" },
		{ ScalarFunction::Substring, "SubString" },
		{ ScalarFunction::Replace, "Replace" },
		{ ScalarFunction::Concat, "Concat" },
		{ ScalarFunction::Instr, "Instr" },

		// Numeric
		{ ScalarFunction::Abs, "Abs" },
		{ ScalarFunction::Ceil, "Ceil" },
		{ ScalarFunction::Floor, "Floor" },
		{ ScalarFunction::Round, "Round" },
		{ ScalarFunction::Power, "Pow" },
		{ ScalarFunction::Sqrt, "Sqrt" },
		{ ScalarFunction::Random, "Rand" },

		// Date/Time
		{ ScalarFunction::Now, "Now" },
		{ ScalarFunction::Date, "CurDate" },
		{ ScalarFunction::Time, "CurTime" },
		{ ScalarFunction::Year, "Year" },
		{ ScalarFunction::DateDiff, "DateDiff" },
		{ ScalarFunction::DateAdd, "DateAdd" },

		// Conversion
		{ ScalarFunction::Cast, "Cast" },
		{ ScalarFunction::DateFormat, "Date_Format" },

		// Null Handling
		{ ScalarFunction::IfNull, "IfNull" },
		{ ScalarFunction::Coalesce, "Coalesce" }
	};

	export const EnumMap<ScalarFunction> ScalarFunctionTemplate
	{
		// String
			{ ScalarFunction::Upper, "UPPER({})" },
			{ ScalarFunction::Lower, "LOWER({})" },
			{ ScalarFunction::Length, "LENGTH({})"},
			{ ScalarFunction::Trim, "TRIM({})" },
			{ ScalarFunction::Substring, "SUBSTRING({},{},{})" },
			{ ScalarFunction::Replace, "REPLACE({},{},{})" },
			{ ScalarFunction::Concat, "CONCAT({},{})" },
			{ ScalarFunction::Instr, "INSTR({},{})" },

			// Numeric
			{ ScalarFunction::Abs, "ABS({})" },
			{ ScalarFunction::Ceil, "CEIL({})" },
			{ ScalarFunction::Floor, "FLOOR({})" },
			{ ScalarFunction::Round, "ROUND({},{})" },
			{ ScalarFunction::Power, "POW({},{})" },
			{ ScalarFunction::Sqrt, "SQRT({})" },
			{ ScalarFunction::Random, "RAND()" },

			// Date/Time
			{ ScalarFunction::Now, "NOW()" },
			{ ScalarFunction::Date, "CURDATE()" },
			{ ScalarFunction::Time, "CURTIME()" },
			{ ScalarFunction::Year, "YEAR({})" },
			{ ScalarFunction::DateDiff, "DATEDIFF({},{})" },
			{ ScalarFunction::DateAdd, "DATEADD({},INTERVAL {} DAY)" },

			// Conversion
			{ ScalarFunction::Cast, "CAST({} AS {})" },
			{ ScalarFunction::DateFormat, "DATE_FORMAT({},{})" },

			// Null Handling
			{ ScalarFunction::IfNull, "IFNULL({})" },
			{ ScalarFunction::Coalesce, "COALESCE({})" }
	};

	// OperatorMap
	export const EnumMap<Operator> OperatorMap
	{
		{ Operator::Add, "+" },
		{ Operator::Subtract, "-" },
		{ Operator::Multiply, "*" },
		{ Operator::Divide, "/" },
		{ Operator::Modulus, "%" }
	};

	// TopUnitMap
	export const EnumMap<TopUnit> TopUnitMap
	{
		{ TopUnit::Records, "Records" },
		{ TopUnit::Percent, "Percent" }
	};
}
