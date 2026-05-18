// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:Selectable;

import std;

import :BuilderTypes;
import :Component;

namespace DataAccessLayer::SqlQueryBuilder
{
	class SelectableImpl;

	export class Selectable : public Component
	{
	public:
		Selectable();
		Selectable(ComponentId componentId);
		~Selectable() override;

		Selectable(const Selectable&);
		Selectable& operator=(const Selectable&);
		Selectable(Selectable&&) noexcept ;
		Selectable& operator=(Selectable&&) noexcept ;

		[[nodiscard]] AliasPtr aliasPtr() const;
		[[nodiscard]] const String& alias() const;
		void setAlias(std::optional<Alias> alias) const;
		[[nodiscard]] bool hasAlias() const noexcept;

		void suppressAlias(bool suppressFlag) const noexcept;
		[[nodiscard]] bool isAliasSuppressed() const noexcept;

		void suppressBrackets(bool suppressFlag) const noexcept;
		[[nodiscard]] bool areBracketsSuppressed() const noexcept;

		[[nodiscard]] virtual SelectablePtr clone() const = 0;

	protected:
		String toSql(const IBuilder* builderPtr) const override = 0;

	private:
		std::unique_ptr<SelectableImpl> impl_{};
	};
}
