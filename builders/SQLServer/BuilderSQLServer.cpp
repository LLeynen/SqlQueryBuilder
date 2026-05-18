// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module BuilderSqlServer;

import QueryBuilder;

namespace DataAccessLayer::SqlQueryBuilder
{
    // BuilderSqlServer::SqlServerBuilder
    BuilderSqlServer::BuilderSqlServer() noexcept
        : BuilderBase(builderEngine)
    {
        setupEngineParams();
    }

    // BuilderSqlServer::setupEngineParams
    void BuilderSqlServer::setupEngineParams()
    {
        engineParams_.databaseEngine = builderEngine;
        engineParams_.engineName = DatabaseEngineMap.at(builderEngine);
        engineParams_.startDelimiter = "[";
        engineParams_.endDelimiter = "]";
        engineParams_.parameterPlaceHolder = "?";
        engineParams_.parameterPrefix = "@";
        engineParams_.concatOperator = "+";
        engineParams_.escapeCharacter = "\\";
        engineParams_.columnAsKeyWord = "AS";
        engineParams_.tableAsKeyWord = "AS";
        engineParams_.supportsFilterClause = true;
        engineParams_.supportsLimitOffset = true;
        engineParams_.omitSelectInsideExists = true;
    }
}
