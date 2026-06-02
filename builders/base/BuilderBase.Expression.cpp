// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import std;

import :BuilderTypes;
import :Expression;
import :Alias;
import :FormulaValueVisitor;
import :FormulaArgString;

namespace DataAccessLayer::SqlQueryBuilder
{
	String BuilderBase::buildComponent(const Expression& expression) const
	{
		const String lhsString{ formulaArgString(this, expression.lhs()) };
		const String rhsString{ formulaArgString(this, expression.rhs()) };
		String expressionString{ };

		switch (expression.mode())
		{
		case Mode::Binary:
			{
				expressionString = lhsString + " " + OperatorMap.at(expression.op()) + " " + rhsString;
				if (!expression.areBracketsSuppressed())
				{
					expressionString = "(" + expressionString + ")";
				}
			}
			break;

		case Mode::Unary:
			{
				expressionString = "(" + OperatorMap.at(expression.op()) + " " + lhsString + ")";
			}
			break;

		case Mode::Wrapper:
			{
				auto operand = std::get<Operand>(expression.lhs());
				expressionString = operand.get()->sql(this);
			}
			break;
		}

		if (expression.hasAlias())
		{
			expressionString += expression.aliasPtr()->sql(this);
		}

		return expressionString;
	}
}
