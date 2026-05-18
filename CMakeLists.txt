cmake_minimum_required(VERSION 4.2)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
#set(CMAKE_EXPERIMENTAL_CXX_MODULE_STD ON)

project (SqlQueryBuilder LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_MODULE_STD ON)
if(MSVC)
    add_compile_options(/utf-8 /permissive-)
endif()
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")

add_library(SqlQueryBuilder)
set_target_properties(SqlQueryBuilder PROPERTIES CXX_MODULE_STD ON)

target_sources (
        SqlQueryBuilder
        PUBLIC
            FILE_SET CXX_MODULES FILES
                common/Enums.cppm
                common/BuilderTypes.cppm
                common/StringStd.cppm
                common/String.cppm
                common/Variant.cppm
                common/EnumMap.cppm
                common/EnumMaps.cppm
				common/Operand.cppm
                components/Component.cppm
				components/Alias.cppm
                components/Selectable.cppm
                components/Expression.cppm
                components/Field.cppm
                components/Aggregate.cppm
                components/Function.cppm
                components/Literal.cppm
		 		components/QuerySelectable.cppm
                components/ListOfValues.cppm
				components/ParameterValue.cppm
				components/Parameter.cppm
                components/ParameterSelectable.cppm
                components/ConditionBase.cppm
                components/CompositeCondition.cppm
                components/Condition.cppm
                components/DataSource.cppm
				components/TableDataSource.cppm
				components/QueryDataSource.cppm
                components/Table.cppm
				components/Query.cppm
                components/Filter.cppm
                components/TopClause.cppm
                components/OffsetClause.cppm
                components/LimitClause.cppm
                components/JoinClause.cppm
                components/OrderByClause.cppm
                components/ComponentWrappers.cppm
                querybuilder/QueryBuilder.cppm
                querybuilder/QueryBuilder.Impl.cppm
                querybuilder/QueryBuilder.Concepts.cppm
                querybuilder/QueryBuilder.Interface.cppm
                builders/IBuilder.cppm
                builders/BuilderFactory.cppm
                builders/base/BuilderBase.cppm
                builders/MariaDB/BuilderMariaDB.cppm
                builders/PostgreSQL/BuilderPostgreSQL.cppm
                builders/SQLServer/BuilderSQLServer.cppm

        PRIVATE
            common/Variant.cpp
            components/Component.cpp
			components/Alias.cpp
            components/Selectable.cpp
            components/Expression.cpp
            components/Field.cpp
            components/Aggregate.cpp
            components/Function.cpp
            components/Literal.cpp
			components/QuerySelectable.cpp
            components/ListOfValues.cpp
			components/ParameterValue.cpp
			components/Parameter.cpp
			components/ParameterSelectable.cpp
            components/ConditionBase.cpp
            components/CompositeCondition.cpp
            components/Condition.cpp
            components/DataSource.cpp
			components/TableDataSource.cpp
			components/QueryDataSource.cpp
            components/Table.cpp
			components/Query.cpp
            components/Filter.cpp
            components/TopClause.cpp
            components/OffsetClause.cpp
            components/LimitClause.cpp
            components/JoinClause.cpp
            components/OrderByClause.cpp
            components/ComponentWrappers.cpp
            querybuilder/QueryBuilder.Impl.cpp
            querybuilder/QueryBuilder.cpp
            querybuilder/QueryBuilder.Aggregate.cpp
            querybuilder/QueryBuilder.Distinct.cpp
            querybuilder/QueryBuilder.Expression.cpp
            querybuilder/QueryBuilder.Field.cpp
            querybuilder/QueryBuilder.From.cpp
            querybuilder/QueryBuilder.GroupBy.cpp
            querybuilder/QueryBuilder.Having.cpp
            querybuilder/QueryBuilder.LimitOffset.cpp
            querybuilder/QueryBuilder.Literal.cpp
            querybuilder/QueryBuilder.OrderBy.cpp
			querybuilder/QueryBuilder.ParameterValue.cpp
            querybuilder/QueryBuilder.Query.cpp
            querybuilder/QueryBuilder.Sql.cpp
            querybuilder/QueryBuilder.Top.cpp
            querybuilder/QueryBuilder.Values.cpp
            querybuilder/QueryBuilder.Where.cpp
            builders/BuilderFactory.cpp
            builders/base/BuilderBase.cpp
            builders/base/BuilderBase.Aggregate.cpp
			builders/base/BuilderBase.Alias.cpp
            builders/base/BuilderBase.AppendQuery.cpp
            builders/base/BuilderBase.BuildDataDefinitionQuery.cpp
            builders/base/BuilderBase.BuildDeleteQuery.cpp
            builders/base/BuilderBase.BuildMakeTableQuery.cpp
            builders/base/BuilderBase.BuildQuery.cpp
            builders/base/BuilderBase.BuildSelectQuery.cpp
            builders/base/BuilderBase.BuildUnionQuery.cpp
            builders/base/BuilderBase.BuildUpdateQuery.cpp
            builders/base/BuilderBase.ComponentWrappers.cpp
            builders/base/BuilderBase.CompositeCondition.cpp
            builders/base/BuilderBase.Condition.cpp
            builders/base/BuilderBase.Expression.cpp
            builders/base/BuilderBase.Field.cpp
            builders/base/BuilderBase.Filter.cpp
            builders/base/BuilderBase.Function.cpp
            builders/base/BuilderBase.JoinClause.cpp
            builders/base/BuilderBase.LimitClause.cpp
            builders/base/BuilderBase.ListOfValues.cpp
            builders/base/BuilderBase.Literal.cpp
            builders/base/BuilderBase.OffsetClause.cpp
            builders/base/BuilderBase.OrderByClause.cpp
			builders/base/BuilderBase.ParameterValue.cpp
			builders/base/BuilderBase.Parameter.cpp
            builders/base/BuilderBase.ParameterSelectable.cpp
			builders/base/BuilderBase.Query.cpp
			builders/base/BuilderBase.QueryDataSource.cpp
            builders/base/BuilderBase.Selectable.cpp
			builders/base/BuilderBase.QuerySelectable.cpp
            builders/base/BuilderBase.Table.cpp
			builders/base/BuilderBase.TableDataSource.cpp
            builders/base/BuilderBase.TopClause.cpp
            builders/MariaDB/BuilderMariaDB.cpp
            builders/PostgreSQL/BuilderPostgreSQL.cpp
            builders/SQLServer/BuilderSQLServer.cpp
            )

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(SqlQueryBuilder PRIVATE -fmodules-ts)
endif()
