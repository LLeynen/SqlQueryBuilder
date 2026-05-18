// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:OrderByClause;

import std;

import :BuilderTypes;
import :Component;

namespace DataAccessLayer::SqlQueryBuilder
{
	class OrderByClauseImpl;

	export class OrderByClause : public Component
	{
	public:
		OrderByClause() noexcept;
		OrderByClause(const Field& field, SortOrder sortOrder = SortOrder::Ascending);
		~OrderByClause() override;

		OrderByClause(const OrderByClause&);
		OrderByClause& operator=(const OrderByClause&);
		OrderByClause(OrderByClause&&) noexcept ;
		OrderByClause& operator=(OrderByClause&&) noexcept ;

		[[nodiscard]] const Field field() const;
		void setField(const Field& field);
		[[nodiscard]] SortOrder sortOrder() const noexcept;
		void setSortOrder(SortOrder sortOrder) noexcept;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<OrderByClauseImpl> impl_;
	};
}
