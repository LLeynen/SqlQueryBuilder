// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:Expression;

import std;

import :BuilderTypes;
import :Selectable;
import :Operand;
//import :Enums;

namespace DataAccessLayer::SqlQueryBuilder
{
	class ExpressionImpl;

	enum class Mode { Binary, Unary, Wrapper };

	export class Expression : public Selectable
	{
	public:

		Expression() noexcept;
		Expression(const Operand& left, Operator op, const Operand& right, std::optional<Alias> alias = std::nullopt) noexcept;
		Expression(Operator op, const Operand& operand, std::optional<Alias> alias = std::nullopt) noexcept;
		Expression(const Selectable& selectable, std::optional<Alias> alias = std::nullopt) noexcept;
		Expression(ScalarFunction scalarFunction, std::initializer_list<Operand> args, std::optional<Alias> alias = std::nullopt);
		Expression(AggregateFunction aggregateFunction, const Selectable& selectable, std::optional<Alias> alias = std::nullopt) noexcept;

		~Expression() override;

		Expression(const Expression&);
		Expression& operator=(const Expression&);
		Expression(Expression&&) noexcept;
		Expression& operator=(Expression&&) noexcept;

		[[nodiscard]] Mode mode() const;
		[[nodiscard]] Operand left() const;
		[[nodiscard]] Operator op() const;
		[[nodiscard]] Operand right() const;

		[[nodiscard]] SelectablePtr clone() const override;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<ExpressionImpl> impl_{};
	};
}
