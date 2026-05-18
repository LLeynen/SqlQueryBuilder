// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import std;

import :BuilderTypes;

namespace DataAccessLayer::SqlQueryBuilder
{
    String BuilderBase::buildQuery(const QueryType queryType, const ComponentMap& componentMap)
    {
        using BuildQueryMethod = String(IBuilder::*)(const ComponentMap&);

        static const std::unordered_map<QueryType, BuildQueryMethod> queryTypeToMethod
        {
               { QueryType::SelectQuery, &IBuilder::buildSelectQuery },
               { QueryType::AppendQuery, &IBuilder::buildAppendQuery },
               { QueryType::UpdateQuery, &IBuilder::buildUpdateQuery },
               { QueryType::DeleteQuery, &IBuilder::buildDeleteQuery },
               { QueryType::UnionQuery,  &IBuilder::buildUnionQuery },
               { QueryType::MakeTableQuery, &IBuilder::buildMakeTableQuery },
               { QueryType::DataDefinitionQuery, &IBuilder::buildDataDefinitionQuery }
        };

        if (const auto it = queryTypeToMethod.find(queryType); it != queryTypeToMethod.end())
        {
            return (this->*(it->second))(componentMap);
        }

        throw std::runtime_error("Unsupported SQL query type");
    }
}
