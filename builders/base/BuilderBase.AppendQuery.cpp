// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import std;

import :BuilderTypes;
import :ComponentWrappers;
import :DataSource;
import :ListOfValues;

namespace DataAccessLayer::SqlQueryBuilder
{
    String BuilderBase::buildAppendQuery(const ComponentMap& componentMap)
    {
        String sqlStatement{ "INSERT INTO " };

        // data source
        auto it = componentMap.find(ComponentId::DataSource);
        if (it == componentMap.end())
        {
            throw std::runtime_error("No data source for APPEND query");
        }

        if (const auto dataSourcePtr = std::dynamic_pointer_cast<DataSource>(it->second))
        {
            sqlStatement += dataSourcePtr->sql(this);
        }

        // selectables
        it = componentMap.find(ComponentId::SelectableListWrapper);
        if (it == componentMap.end())
        {
            throw std::runtime_error("No selectable items for APPEND query");
        }

        const auto selectableListWrapperPtr = std::dynamic_pointer_cast<SelectableListWrapper>(it->second);
        if (selectableListWrapperPtr)
        {
            sqlStatement += " (" + selectableListWrapperPtr->sql(this) + ")";
        }

        // query or values
        it = componentMap.find(ComponentId::QueryListWrapper);
        if (it != componentMap.end())
        {
            const auto queryListWrapperPtr = std::dynamic_pointer_cast<QueryListWrapper>(it->second);
            if (queryListWrapperPtr->queryList()->size() != 1)
            {
                throw std::runtime_error("Append query can have only 1 subquery");
            }
            sqlStatement += " " + queryListWrapperPtr->sql(this);
        }
        else
        {
            it = componentMap.find(ComponentId::ListOfValues);
            if (it == componentMap.end())
            {
                throw std::runtime_error("No values specified for Append query");
            }

            const auto listOfValuesPtr = std::dynamic_pointer_cast<ListOfValues>(it->second);
            if (listOfValuesPtr->valueList().size() != selectableListWrapperPtr->selectableListPtr()->size())
            {
                throw std::runtime_error("Number of values does not match with number of fields");
            }

            sqlStatement += " VALUES " + listOfValuesPtr->sql(this);
        }

        return sqlStatement;
    }
}
