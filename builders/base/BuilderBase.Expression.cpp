// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import std;

import :BuilderTypes;
import :Expression;
import :Alias;

namespace DataAccessLayer::SqlQueryBuilder
{
	String BuilderBase::buildComponent(const Expression& expression) const
	{
		String expressionString{ };

		switch (expression.mode())
		{
			case Mode::Binary:
				expressionString =
					expression.left().get()->sql(this) + " "
					+ OperatorMap.at(expression.op()) + " "
					+ expression.right().get()->sql(this);

				if (!expression.areBracketsSuppressed())
				{
					expressionString = "(" + expressionString + ")";
				}

			std::cout << "BuilderBase::Expression::Binary:" << expressionString << std::endl;
				break;

			case Mode::Unary:
				expressionString =
					"("
					+ OperatorMap.at(expression.op())
					+ expression.left().get()->sql(this)
					+ ")";
				std::cout << "BuilderBase::Expression::Unary:" << expressionString << std::endl;
				break;

			case Mode::Wrapper:
				expressionString =
					expression.left().get()->sql(this);
				std::cout << "BuilderBase::Expression::Wrapper:" << expressionString << std::endl;
				break;
		}

		if (expression.hasAlias())
		{
			expressionString += buildComponent(*expression.aliasPtr());
		}

		return expressionString;
	}
}
