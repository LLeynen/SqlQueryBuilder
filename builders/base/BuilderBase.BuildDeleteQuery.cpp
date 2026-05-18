// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import std;

import :BuilderTypes;
import :ComponentWrappers;
import :DataSource;

namespace DataAccessLayer::SqlQueryBuilder
{
    String BuilderBase::buildDeleteQuery(const ComponentMap& componentMap)
    {
        String sqlStatement{ "DELETE FROM " };

        auto it = componentMap.find(ComponentId::DataSource);
        if (it == componentMap.end())
        {
            throw std::runtime_error("No data source for DELETE query");
        }

        if (const auto dataSourcePtr = std::dynamic_pointer_cast<DataSource>(it->second))
        {
            sqlStatement += dataSourcePtr->sql(this);
        }

        // where
        it = componentMap.find(ComponentId::WhereFilterWrapper);
        if (it != componentMap.end())
        {
            if (const auto whereFilterWrapperPtr = std::dynamic_pointer_cast<WhereFilterWrapper>(it->second))
            {
                sqlStatement += " WHERE " + whereFilterWrapperPtr->sql(this);
            }
        }

        return sqlStatement;
    }
}
