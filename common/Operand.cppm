// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:Operand;

import std;

import :BuilderTypes;
import :Literal;
import :Field;

namespace DataAccessLayer::SqlQueryBuilder
{
	template <typename T>
	concept VariantCompatible =
	std::is_constructible_v<Variant,T>;

	template <typename T>
	concept OperandCompatible =
		VariantCompatible<T> ||
		std::is_base_of_v<Selectable, std::remove_cvref_t<T>>;

	class Operand
	{
	public:
		Operand() = default;
		Operand(const Selectable& selectable);
		Operand(const SelectablePtr& selectablePtr);
		Operand(const FieldRef& fieldRef);
		template<VariantCompatible T>
		Operand(T&& value);

		[[nodiscard]] SelectablePtr get() const;

	private:
		SelectablePtr node{};
	};

	Operand::Operand(const Selectable& selectable)
	{
		auto cloned = selectable.clone();
		cloned->suppressAlias(true);
		node = std::move(cloned);
	}


	Operand::Operand(const SelectablePtr& selectablePtr)
	{
		auto cloned = selectablePtr->clone();
		cloned->suppressAlias(true);
		node = std::move(cloned);
	}

	Operand::Operand(const FieldRef& fieldRef)
	{
		node = std::make_shared<Field>(fieldRef.get());
	}

	template <VariantCompatible T>
	Operand::Operand(T&& value)
		: node(std::make_shared<Literal>(Variant(std::forward<T>(value))))
	{}


	SelectablePtr Operand::get() const
	{
		return node;
	}
}
