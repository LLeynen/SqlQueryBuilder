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
        setupEngineParams();
    }


    void BuilderPostgreSQL::setupEngineParams()
    {
        engineParams_.databaseEngine = builderEngine;
        engineParams_.engineName = DatabaseEngineMap.at(builderEngine);
        engineParams_.startDelimiter = "\"";
        engineParams_.endDelimiter = "\"";
        engineParams_.parameterPlaceHolder = "$1"; // PostgreSQL uses $1, $2, etc.
        engineParams_.parameterPrefix = "$";
        engineParams_.concatOperator = "||";
        engineParams_.escapeCharacter = "\\";
        engineParams_.columnAsKeyWord = "AS";
        engineParams_.tableAsKeyWord = "AS";
        engineParams_.supportsFilterClause = true;
        engineParams_.supportsLimitOffset = true;
        engineParams_.omitSelectInsideExists = true;
    }

    /*
    String PostgreSQLBuilder::buildTableName(const SqlTable& sqlTable) const
    {
        String result = engineParams_.startDelimiter + sqlTable.tableName() + engineParams_.endDelimiter;

        if (!sqlTable.alias().empty()) {
            result += " " + engineParams_.tableAsKeyWord + " " +
                     engineParams_.startDelimiter + sqlTable.alias() + engineParams_.endDelimiter;
        }

        return result;
    }

    String PostgreSQLBuilder::buildColumnName(const String& columnName) const
    {
        return engineParams_.startDelimiter + columnName + engineParams_.endDelimiter;
    }

    String PostgreSQLGenerator::buildParameter(const String& parameterName) const
    {
        // PostgreSQL uses numbered parameters
        return engineParams_.parameterPlaceHolder;
    }

    String PostgreSQLBuilder::buildLimitClause(int limit, int offset) const
    {
        if (offset > 0) {
            return std::format("LIMIT {} OFFSET {}", limit, offset);
        }
        return std::format("LIMIT {}", limit);
    }

    String PostgreSQLBuilder::buildSerial() const
    {
        return "SERIAL";
    }

    String PostgreSQLBuilder::buildArrayType(const String& elementType) const
    {
        return elementType + "[]";
    }
    */
}
