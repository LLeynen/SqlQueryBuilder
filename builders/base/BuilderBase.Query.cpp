// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :Query;
import :String;

namespace DataAccessLayer::SqlQueryBuilder
{
    String BuilderBase::buildComponent(const Query& query) const
    {
        auto querySource = query.querySource();
//        String queryString = query.queryString();
        String queryString{};

        if (std::holds_alternative<QueryBuilderPtr>(querySource))
        {
            auto queryBuilderPtr = std::get<QueryBuilderPtr>(querySource);
//            queryBuilderPtr->setDatabaseEngine(databaseEngine());
//            queryString = queryBuilderPtr->sql();
            queryString = queryBuilderPtr->sql();
        }
        else if (std::holds_alternative<String>(querySource))
        {
            String rawSql = std::get<String>(querySource);
            queryString = rawSql;
        }
        else
        {
            throw std::runtime_error("Query: Cannot generate SQL - no query source available");
        }

        return queryString;
    }
}
