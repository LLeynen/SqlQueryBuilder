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
	/*
		struct FormulaValueVisitor
		{
			FormulaValueVisitor(const BuilderBase* builder)
				: builder_{ builder }
			{}

			const BuilderBase* builder_;

			// Type nullptr_t
			String operator()(const std::nullptr_t&) const
			{
				return "NULL";
			}

			// Type Variant
			String operator()(const Variant& value) const
			{
				if (value.isNull())
				{
					return (*this)(nullptr);
				}
				else
				{
					return value.sqlFormat();
				}
			}

			// Type Parameter
			String operator()(const Parameter& parameter) const
			{
					return parameter.sql(builder_);
			}

			// Type String
			String operator()(const String& value) const
			{
				const Variant variant{ value };
				return variant.sqlFormat();
			}

			// Type const char*
			String operator()(const char* value) const
			{
				return (*this)(String{ value });
			}
		};
*/
	/*
	namespace
	{
		String formulaArgString(const BuilderBase* builder, const FormulaArg& formulaArg)
		{
			if (std::holds_alternative<Operand>(formulaArg))
			{
				auto selectablePtr { std::get<Operand>(formulaArg).get() };
				return selectablePtr->sql(builder);
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

*/
	String BuilderBase::buildComponent(const Expression& expression) const
	{
/*		bool nestedFormula { false };

		const auto& operandLhs = std::get<Operand>(expression.lhs());
		if (auto selectablePtr = operandLhs.get())
		{
			if (selectablePtr->componentId() == ComponentId::Expression
				or selectablePtr->componentId() == ComponentId::Function
				or selectablePtr->componentId() == ComponentId::Aggregate)
			{
				nestedFormula = true;
			}
		}
		const auto& operandRhs = std::get<Operand>(expression.lhs());
		if (auto selectablePtr = operandRhs.get())
		{
			if (selectablePtr->componentId() == ComponentId::Expression
				or selectablePtr->componentId() == ComponentId::Function
				or selectablePtr->componentId() == ComponentId::Aggregate)
			{
				nestedFormula = true;
			}
		}

*/

		String lhsString{ formulaArgString(this, expression.lhs()) };
		String rhsString{ formulaArgString(this, expression.rhs()) };
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
