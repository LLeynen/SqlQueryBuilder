// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :EnumMaps;

namespace DataAccessLayer::SqlQueryBuilder
{
	BuilderBase::BuilderBase()
		: databaseEngine_(DatabaseEngine::AnsiSQL)
	{}


	BuilderBase::BuilderBase(const DatabaseEngine databaseEngine)
		: databaseEngine_(databaseEngine)
	{}


	DatabaseEngine BuilderBase::databaseEngine() const noexcept
	{
		return databaseEngine_;
	}


	String BuilderBase::databaseEngineName() const
	{
		return DatabaseEngineMap.at(databaseEngine_);
	}


	void BuilderBase::setupEngineParams()
	{
		engineParams_.engineName = "";
		engineParams_.startDelimiter = "\"";
		engineParams_.endDelimiter = "\"";
		engineParams_.parameterPlaceHolder = "?";
		engineParams_.parameterPrefix = "";
		engineParams_.concatOperator = "||";
		engineParams_.escapeCharacter = "\\";
		engineParams_.MatchAll = "%";
		engineParams_.MatchSingle = "_";

		engineParams_.supportsFilterClause = false;
		engineParams_.supportsLimitOffset = true;
		engineParams_.omitSelectInsideExists = false;
	}
}
