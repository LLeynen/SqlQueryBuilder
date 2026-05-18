// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import std;

import :BuilderTypes;

namespace DataAccessLayer::SqlQueryBuilder
{
    String BuilderBase::buildDataDefinitionQuery(const ComponentMap& componentMap)
    {
        throw std::runtime_error("Data Definition query is not implemented yet");
    }
}
