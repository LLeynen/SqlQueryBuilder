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
}
