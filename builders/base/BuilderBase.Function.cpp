// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :Function;
import :String;
import :FormulaArgString;

namespace DataAccessLayer::SqlQueryBuilder
{
	String BuilderBase::buildComponent(const Function& scalarFunction) const
	{
		const ScalarFunction function{ scalarFunction.function() };
		String functionTemplate { ScalarFunctionTemplate.at(function) };
		const auto args { scalarFunction.arguments() };

		const auto templateCount = std::ranges::count(functionTemplate, '{');

		if (const auto argCount = args.size(); argCount != templateCount)
		{
			throw std::runtime_error("Wrong number of arguments, template "
				+ std::to_string(templateCount)
				+ ", arguments " + std::to_string(argCount));
		}

//		std::vector<String> resolvedSelectables;
//		for (const auto& selectable : scalarFunction.selectableList())
//		{
//			resolvedSelectables.push_back(selectable->sql());
//		}

		String functionString { functionTemplate };

		for (const auto& arg : args)
		{
			if (const size_t pos = functionString.find("{}"); pos != String::npos)
			{
				if (std::holds_alternative<Operand>(arg))
				{
					if (auto selectablePtr = std::get<Operand>(arg).get())
					{
						selectablePtr->suppressBrackets(true);
					}
				}
				functionString.replace(pos, 2, formulaArgString(this, arg));
			}
		}

		if (scalarFunction.hasAlias())
		{
			functionString += scalarFunction.aliasPtr()->sql(this);
		}

		return functionString;
	}
}
