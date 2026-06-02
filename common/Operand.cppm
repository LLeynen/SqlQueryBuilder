// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:Operand;

import std;

import :BuilderTypes;
import :Field;

namespace DataAccessLayer::SqlQueryBuilder
{
	export template <typename T>
	concept OperandCompatible =
		std::is_base_of_v<Selectable, std::remove_cvref_t<T>>;

	export class Operand
	{
	public:
		Operand();
		Operand(FieldRef fieldRef);
		Operand(Expression expression);
		Operand(Function func);
		Operand(Aggregate aggregate);
		Operand(ParameterSelectable parameterSelectable);
		Operand(Literal literal);
		Operand(QueryBuilder queryBuilder);
		~Operand();

		[[nodiscard]] SelectablePtr get() const &;
		[[nodiscard]] SelectablePtr get() && noexcept;

	private:
		SelectablePtr node_{};
	};
}
