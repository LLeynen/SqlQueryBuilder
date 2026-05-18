// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :Function;
import :String;

namespace DataAccessLayer::SqlQueryBuilder
{
	String BuilderBase::buildComponent(const Function& scalarFunction) const
	{
		const ScalarFunction function{ scalarFunction.function() };
		String functionTemplate { ScalarFunctionTemplate.at(function) };

		const auto templateCount = std::ranges::count(functionTemplate, '{');

		if (const auto selectableCount = scalarFunction.selectableList().size(); selectableCount != templateCount)
		{
			throw std::runtime_error("Wrong number of arguments, template "
				+ std::to_string(templateCount)
				+ ", selectables " + std::to_string(selectableCount));
		}

		std::vector<String> resolvedSelectables;
		for (const auto& selectable : scalarFunction.selectableList())
		{
			resolvedSelectables.push_back(selectable->sql());
		}

		String functionString { functionTemplate };
		for (const auto& resolvedSelectable : resolvedSelectables)
		{
			if (const size_t pos = functionString.find("{}"); pos != String::npos)
			{
				functionString.replace(pos, 2, resolvedSelectable);
			}
		}

		if (scalarFunction.hasAlias())
		{
			functionString += buildComponent(*scalarFunction.aliasPtr());
		}

		return functionString;
	}
}
