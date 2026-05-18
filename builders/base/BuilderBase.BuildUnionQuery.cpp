// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import std;

import :BuilderTypes;
import :ComponentWrappers;

namespace DataAccessLayer::SqlQueryBuilder
{
    String BuilderBase::buildUnionQuery(const ComponentMap& componentMap)
    {
        String sqlStatement{ "SELECT " };

        const auto it = componentMap.find(ComponentId::QueryListWrapper);
        if (it == componentMap.end())
        {
            throw std::runtime_error("No queries for UNION query");
        }

        const auto queryListWrapperPtr = std::dynamic_pointer_cast<QueryListWrapper>(it->second);
        if (queryListWrapperPtr and queryListWrapperPtr->queryList()->size() < 2)
        {
            throw std::runtime_error("Union query requires at least 2 subqueries");
        }

        if (queryListWrapperPtr)
        {
            String queryListWrapperString{};

            if (auto queryList = queryListWrapperPtr->queryList(); !queryList->empty())
            {
                for (size_t i = 0; i < queryListWrapperPtr->queryList()->size(); ++i)
                {
                    auto query = queryList->at(i);
                    queryListWrapperString += buildComponent(*query);

                    if (i < queryList->size() - 1)
                    {
                        queryListWrapperString += " UNION ";
                    }
                }
            }
        }

        return sqlStatement;
    }
}
