// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:Expression;

import std;

import :BuilderTypes;
import :Selectable;
import :Operand;
import :Variant;
import :Parameter;
import :Concepts;

namespace DataAccessLayer::SqlQueryBuilder
{
	class ExpressionImpl;

	enum class Mode { Binary, Unary, Wrapper };

	export class Expression : public Selectable
	{
	public:
		Expression() noexcept;
		Expression(Operand lhs, Operator op, Operand rhs, std::optional<Alias> alias = std::nullopt);
		Expression(std::initializer_list<const char*> lhsTokens, Operator op, std::initializer_list<const char*> rhsTokens, std::optional<Alias> alias = std::nullopt)
			: Expression(Operand{ FieldRef{ lhsTokens } }, op, Operand{ FieldRef{ rhsTokens } }, std::move(alias))
		{}
		Expression(Operand lhs, Operator op, FormulaValue rhs, std::optional<Alias> alias = std::nullopt);
		Expression(FormulaValue lhs, Operator op, Operand rhs, std::optional<Alias> alias = std::nullopt);
		Expression(Operator op, FormulaValue lhs, std::optional<Alias> alias = std::nullopt);
		Expression(Operator op, Operand lhs, std::optional<Alias> alias = std::nullopt);
		Expression(ScalarFunction scalarFunction, std::vector<FormulaArg> args, std::optional<Alias> alias = std::nullopt);
		Expression(AggregateFunction aggregateFunction, FormulaArg arg, std::optional<Alias> alias = std::nullopt) noexcept;

		~Expression() override;

		Expression(const Expression&);
		Expression& operator=(const Expression&);
		Expression(Expression&&) noexcept;
		Expression& operator=(Expression&&) noexcept;

		[[nodiscard]] Mode mode() const;
		[[nodiscard]] FormulaArg lhs() const;
		[[nodiscard]] Operator op() const;
		[[nodiscard]] FormulaArg rhs() const;

		[[nodiscard]] SelectablePtr clone() const override;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<ExpressionImpl> impl_{};


	};

	// 1. Operand * Operand (Handles FieldRef * FieldRef via implicit conversion to Operand)
	inline Expression operator*(Operand lhs, Operand rhs) {
		return Expression(std::move(lhs), Operator::Multiply, std::move(rhs));
	}

	// 2. Operand * FormulaValue (Handles FieldRef * 1.10 for calculations like adding taxes)
	inline Expression operator*(Operand lhs, FormulaValue rhs) {
		return Expression(std::move(lhs), Operator::Multiply, std::move(rhs));
	}

	// 3. FormulaValue * Operand (Handles 100 * FieldRef)
	inline Expression operator*(FormulaValue lhs, Operand rhs) {
		return Expression(std::move(lhs), Operator::Multiply, std::move(rhs));
	}

}
