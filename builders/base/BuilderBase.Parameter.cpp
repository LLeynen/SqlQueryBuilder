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
        return parameter.value().toString();
    }
}
