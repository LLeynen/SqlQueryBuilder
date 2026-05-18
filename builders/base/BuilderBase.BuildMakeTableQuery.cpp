// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import std;

import :BuilderTypes;

namespace DataAccessLayer::SqlQueryBuilder
{
    String BuilderBase::buildMakeTableQuery(const ComponentMap& componentMap)
    {
        throw std::runtime_error("Make Table query is not implemented yet");
    }
}
