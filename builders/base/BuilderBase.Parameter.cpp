// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import std;

import :BuilderTypes;
import :Parameter;

namespace DataAccessLayer::SqlQueryBuilder
{
    String BuilderBase::buildComponent(const Parameter& parameter) const
    {
        const String& parameterName = parameter.parameterName();
        const ParameterMapPtr parameterMapPtr = parameter.parameterMap();

        if (parameterMapPtr)
        {
            if (const auto it = parameterMapPtr->find(parameterName); it != parameterMapPtr->end())
            {
                return buildComponent(*it->second);
            }
            else
            {
                throw std::runtime_error("Parameter name not found in ParameterMap.");
            }
        }
        else
        {
            const ParameterValue parameterValue(parameterName);
            return buildComponent(parameterValue);
        }
    }
}
