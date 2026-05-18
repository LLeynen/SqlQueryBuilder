// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderTypes;

import std;

import :BuilderTypes;
import :DataSource;
import :Selectable;
import :ComponentWrappers;
import :ListOfValues;

namespace DataAccessLayer::SqlQueryBuilder
{
    String BuilderBase::buildUpdateQuery(const ComponentMap& componentMap)
    {
        String sqlStatement{ "UPDATE " };

        // data source
        auto it = componentMap.find(ComponentId::DataSource);
        if (it == componentMap.end())
        {
            throw std::runtime_error("No data source for UPDATE query");
        }

        if (auto sqlDataSourcePtr = std::dynamic_pointer_cast<DataSource>(it->second))
        {
            sqlStatement += sqlDataSourcePtr->sql(this);
        }

        sqlStatement += " SET ";

        // fields and values
        const auto selectableListWrapperPtr = std::dynamic_pointer_cast<SelectableListWrapper>(componentMap.at(ComponentId::SelectableListWrapper));
        const auto listOfValuesPtr = std::dynamic_pointer_cast<ListOfValues>(componentMap.at(ComponentId::ListOfValues));
        const auto selectableListPtr = selectableListWrapperPtr->selectableListPtr();
        const auto valueList = listOfValuesPtr->valueList();

        if (selectableListPtr->size() != valueList.size())
        {
            throw std::runtime_error("Number of fields different from number of values");
        }

        for (size_t i = 0; i < selectableListPtr->size(); ++i)
        {
            String selectableString{ (selectableListPtr->at(i))->sql(this) };
            String sqlValue{ valueList.at(i).sqlFormat() };

            sqlStatement += selectableString + " = " + sqlValue;

            if (i < selectableListPtr->size() - 1)
            {
                sqlStatement += ", ";
            }
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
