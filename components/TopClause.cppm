// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:TopClause;

import std;

import :BuilderTypes;
import :Component;

namespace DataAccessLayer::SqlQueryBuilder
{
	class TopClauseImpl;

	export class TopClause : public Component
	{
	public:
		TopClause() noexcept;
		TopClause(int quantity, TopUnit unit = TopUnit::Records) noexcept;
		~TopClause() override;

		TopClause(const TopClause&);
		TopClause& operator=(const TopClause&);
		TopClause(TopClause&&) noexcept ;
		TopClause& operator=(TopClause&&) noexcept ;

		[[nodiscard]] int quantity() const noexcept;
		void setQuantity(int quantity) const noexcept;
		[[nodiscard]] TopUnit unit() const noexcept;
		void setUnit(TopUnit unit) const noexcept;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<TopClauseImpl> impl_{};
	};
}
