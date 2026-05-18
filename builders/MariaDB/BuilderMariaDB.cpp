// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module BuilderMariaDB;

import QueryBuilder;

namespace DataAccessLayer::SqlQueryBuilder
{
    BuilderMariaDB::BuilderMariaDB() noexcept
        : BuilderBase(builderEngine)
    {
        setupEngineParams();
    }


    String BuilderMariaDB::buildLimitClause(const int limit, const int offset) const
    {
        if (offset > 0)
        {
            return "LIMIT " + toString(limit) + " OFFSET " + toString(offset);
        }

        return "LIMIT " + toString(limit);
    }


    String BuilderMariaDB::buildAutoIncrement() const
    {
        return "AUTO_INCREMENT";
    }


    void BuilderMariaDB::setupEngineParams()
    {
        engineParams_.databaseEngine = builderEngine;
        engineParams_.engineName = DatabaseEngineMap.at(builderEngine);
        engineParams_.startDelimiter = "`";
        engineParams_.endDelimiter = "`";
        engineParams_.parameterPlaceHolder = "?";
        engineParams_.parameterPrefix = "@";
        engineParams_.concatOperator = "CONCAT";
        engineParams_.escapeCharacter = "\\";
        engineParams_.columnAsKeyWord = "AS";
        engineParams_.tableAsKeyWord = "AS";
        engineParams_.supportsFilterClause = true;
        engineParams_.supportsLimitOffset = true;
        engineParams_.omitSelectInsideExists = false;
    }
}
