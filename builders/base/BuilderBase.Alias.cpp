// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :Alias;

namespace DataAccessLayer::SqlQueryBuilder
{
	String BuilderBase::buildComponent(const Alias& alias) const
	{
		if (alias.value().empty() or alias.isSuppressed())
		{
			return "";
		}

		String aliasString{ (alias.aliasType() == AliasType::Column)
			? engineParams_.columnAsKeyWord : engineParams_.tableAsKeyWord };

		if (!aliasString.empty())
		{
			aliasString = " " + aliasString + " ";
		}

		aliasString += alias.value();

		return aliasString;
	}
}
