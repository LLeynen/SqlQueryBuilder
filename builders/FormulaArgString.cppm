// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:FormulaArgString;

import std;

import :BuilderTypes;
import :Operand;
import :FormulaValueVisitor;

namespace DataAccessLayer::SqlQueryBuilder
{
	export String formulaArgString(const IBuilder* builder, const FormulaArg& formulaArg)
	{
		if (std::holds_alternative<Operand>(formulaArg))
		{
			const auto selectablePtr { std::get<Operand>(formulaArg).get() };
			if (selectablePtr)
			{
				selectablePtr->suppressAlias(true);
				return selectablePtr->sql(builder);
			}
			return "";
		}
		else if (std::holds_alternative<FormulaValue>(formulaArg))
		{
			auto formulaValue { std::get<FormulaValue>(formulaArg) };
			return std::visit(FormulaValueVisitor{ builder}, formulaValue);
		}
		else
		{
			return "";
		}
	}
}