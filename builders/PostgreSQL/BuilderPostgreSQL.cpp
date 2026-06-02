// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module BuilderPostgreSQL;

import QueryBuilder;

namespace DataAccessLayer::SqlQueryBuilder
{
    BuilderPostgreSQL::BuilderPostgreSQL() noexcept
        : BuilderBase(builderEngine)
    {
        BuilderPostgreSQL::setupEngineParams();
    }


    void BuilderPostgreSQL::setupEngineParams()
    {
        engineParams_.databaseEngine = builderEngine;
        engineParams_.engineName = DatabaseEngineMap.at(builderEngine);
        engineParams_.startDelimiter = "\"";
        engineParams_.endDelimiter = "\"";
        engineParams_.parameterPlaceHolder = "$1";
        engineParams_.parameterPrefix = "$";
        engineParams_.concatOperator = "||";
        engineParams_.escapeCharacter = "\\";
        engineParams_.columnAsKeyWord = "AS";
        engineParams_.tableAsKeyWord = "AS";
        engineParams_.MatchAll = "%";
        engineParams_.MatchSingle = "_";
        engineParams_.supportsFilterClause = true;
        engineParams_.supportsLimitOffset = true;
        engineParams_.omitSelectInsideExists = true;
    }
}
