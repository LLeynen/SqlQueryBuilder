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
		{ ComponentId::ComparisonFilter, "ComparisonFilter" },
		{ ComponentId::DataSource, "DataSource" },
		{ ComponentId::Distinct, "Distinct" },
		{ ComponentId::Expression, "Expression" },
		{ ComponentId::Field, "Field" },
		{ ComponentId::FilterBase, "FilterBase" },
		{ ComponentId::FilterSelectable, "FilterSelectable" },
		{ ComponentId::JoinClause, "JoinClause" },
		{ ComponentId::LimitClause, "LimitClause" },
		{ ComponentId::ListOfValues, "ListOfValues" },
		{ ComponentId::Literal, "Literal" },
		{ ComponentId::LogicalFilter, "LogicalFilter" },
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
		{ Comparison::Not, "NOT"},
		{ Comparison::Like, "LIKE"},
		{ Comparison::NotLike, "NOT LIKE"},
		{ Comparison::GreaterThan, ">"},
		{ Comparison::GreaterOrEquals, ">="},
		{ Comparison::LessThan, "<"},
		{ Comparison::LessOrEquals , "<="},
		{ Comparison::In, "IN"},
		{ Comparison::NotIn, "NOT IN"},
		{ Comparison::Between, "BETWEEN"},
		{ Comparison::Exists, "EXISTS"},
		{ Comparison::NotExists, "NOT EXISTS"},
		{ Comparison::Any, "ANY"},
		{ Comparison::Some, "SOME"},
		{ Comparison::All, "ALL"}
	};

	// LogicOperatorMap
	export const EnumMap<LogicOperator> LogicOperatorMap
	{
		{ LogicOperator::And, "AND" },
		{ LogicOperator::Or, "OR" },
		{ LogicOperator::Not, "NOT" }
	};

	// JoinTypeMap
	export const EnumMap<JoinType> JoinTypeMap
	{
		{ JoinType::InnerJoin, "INNER JOIN" },
		{ JoinType::OuterJoin, "OUTER JOIN" },
		{ JoinType::LeftJoin, "LEFT JOIN" },
		{ JoinType::RightJoin, "RIGHT JOIN" }
	};

	// SortOrderMap
	export const EnumMap<SortOrder> SortOrderMap
	{
		{ SortOrder::Ascending, "ASC" },
		{ SortOrder::Descending, "DESC" }
	};

	// AggregateFunctionMap
	export const EnumMap<AggregateFunction> AggregateFunctionMap
	{
		{ AggregateFunction::Sum, "SUM" },
		{ AggregateFunction::Avg, "AVG" },
		{ AggregateFunction::Min, "MIN" },
		{ AggregateFunction::Max, "MAX" },
		{ AggregateFunction::Count, "COUNT" },
		{ AggregateFunction::StdDev, "STDDEV" },
		{ AggregateFunction::Var, "VAR" },
		{ AggregateFunction::First, "FIRST" },
		{ AggregateFunction::Last, "LAST" }
	};

	export const EnumMap<ScalarFunction> ScalarFunctionMap
	{
		// String
		{ ScalarFunction::Upper, "UPPER" },
		{ ScalarFunction::Lower, "LOWER" },
		{ ScalarFunction::Length, "LENGTH"},
		{ ScalarFunction::Trim, "TRIM" },
		{ ScalarFunction::Substring, "SUBSTRING" },
		{ ScalarFunction::Replace, "REPLACE" },
		{ ScalarFunction::Concat, "CONCAT" },
		{ ScalarFunction::Instr, "INSTR" },

		// Numeric
		{ ScalarFunction::Abs, "ABS" },
		{ ScalarFunction::Ceil, "CEIL" },
		{ ScalarFunction::Floor, "FLOOR" },
		{ ScalarFunction::Round, "ROUND" },
		{ ScalarFunction::Power, "POW" },
		{ ScalarFunction::Sqrt, "SQRT" },
		{ ScalarFunction::Random, "RAND" },

		// Date/Time
		{ ScalarFunction::Now, "NOW" },
		{ ScalarFunction::CurrentDate, "CURDATE" },
		{ ScalarFunction::CurrentTime, "CURTIME" },
		{ ScalarFunction::Year, "YEAR" },
		{ ScalarFunction::DateDiff, "DATEDIFF" },
		{ ScalarFunction::DateAdd, "DATEADD" },

		// Conversion
		{ ScalarFunction::Cast, "CAST" },
		{ ScalarFunction::DateFormat, "DATE_FORMAT" },

		// Null Handling
		{ ScalarFunction::IfNull, "IFNULL" },
		{ ScalarFunction::Coalesce, "COALESCE" }
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
			{ ScalarFunction::CurrentDate, "CURDATE()" },
			{ ScalarFunction::CurrentTime, "CURTIME()" },
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
		{ TopUnit::Records, "RECORDS" },
		{ TopUnit::Percent, "PERCENT" }
	};
}
