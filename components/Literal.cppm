// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:Literal;

import std;

import :BuilderTypes;
import :Selectable;
import :Variant;
import :Alias;

namespace DataAccessLayer::SqlQueryBuilder
{
	class LiteralImpl;
	export class Literal : public Selectable
	{
	public:
		Literal() noexcept;
		Literal(const Variant& value, std::optional<Alias> alias = std::nullopt);
		~Literal() override;

		Literal(const Literal& other);
		Literal& operator=(const Literal& other);
		Literal(Literal&&) noexcept;
		Literal& operator=(Literal&&) noexcept;

		[[nodiscard]] const Variant& value() const noexcept;
		void setValue(const Variant& value) const;

		[[nodiscard]] SelectablePtr clone() const override;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<LiteralImpl> impl_{};
	};
}
