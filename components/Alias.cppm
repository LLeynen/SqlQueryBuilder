// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:Alias;

import std;

import :BuilderTypes;
import :Component;

namespace DataAccessLayer::SqlQueryBuilder
{
	enum class AliasType { Column, Table };

	class AliasImpl;

	export class Alias : public Component
	{
	public:
		Alias() noexcept;
		Alias(String aliasValue);
		~Alias() override;

		Alias(const Alias& other);
		Alias& operator=(const Alias& other);
		Alias(Alias&&) noexcept;
		Alias& operator=(Alias&&) noexcept;

		[[nodiscard]] AliasType aliasType() const noexcept;
		void setAliasType(AliasType aliasType) const;
		[[nodiscard]] String value() const noexcept;
		void setValue(String value) const;

		void suppress(bool suppress) const noexcept;
		[[nodiscard]] bool isSuppressed() const noexcept;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<AliasImpl> impl_{};
	};


	export inline Alias as(String aliasValue)
	{
		return { std::move(aliasValue) };
	}
}
