// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :Selectable;

namespace DataAccessLayer::SqlQueryBuilder
{
    // BuilderBase::buildComponent(Selectable)
    String BuilderBase::buildComponent(const Selectable& selectable) const
    {
        return const_cast<Selectable&>(selectable).sql(this);
    }
}