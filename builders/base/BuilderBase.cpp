// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :EnumMaps;

namespace DataAccessLayer::SqlQueryBuilder
{
	// BuilderBase::BuilderBase
	BuilderBase::BuilderBase()
		: databaseEngine_(DatabaseEngine::AnsiSQL)
	{
//		setupEngineParams();
	}

	// BuilderBase::BuilderBase(DatabaseEngine)
	BuilderBase::BuilderBase(DatabaseEngine databaseEngine)
		: databaseEngine_(databaseEngine)
	{
//		setupEngineParams();
	}

	// BuilderBase::databaseEngine
	DatabaseEngine BuilderBase::databaseEngine() const noexcept
	{
		return databaseEngine_;
	}

	// BuilderBase::databaseEngineName
	const String BuilderBase::databaseEngineName() const
	{
		return DatabaseEngineMap.at(databaseEngine_);
	}

	// BuilderBase::setupEngineParams
//	void BuilderBase::setupEngineParams()
//	{
		/*
		engineParams_.engineName = "";
		engineParams_.startDelimiter = "\"";
		engineParams_.endDelimiter = "\"";
		engineParams_.parameterPlaceHolder = "?";
		engineParams_.parameterPrefix = "";
		engineParams_.concatOperator = "||";
		engineParams_.escapeCharacter = "\\";
		engineParams_.supportsFilterClause = false;
		engineParams_.supportsLimitOffset = true;
		engineParams_.omitSelectInsideExists = false;
		*/
//	}

	/*
	String BuilderBase::escapeIdentifier(const String& identifier) const
	{
		// Common escaping logic that can be overridden
		if (identifier.empty()) return identifier;

		String result = identifier;
		std::replace(result.begin(), result.end(), ' ', '_');
		return result;
	}

	String BuilderBase::formatParameter(const String& parameter) const
	{
		// Common parameter formatting
		return engineParams_.parameterPrefix + parameter;
	}
	*/
}
