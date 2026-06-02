// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:OrderByClause;

import std;

import :BuilderTypes;
import :Component;
import :Field;

namespace DataAccessLayer::SqlQueryBuilder
{
	class OrderByClauseImpl;

	export class OrderByClause : public Component
	{
	public:
		OrderByClause() noexcept;
		OrderByClause(FieldRef fieldRef, SortOrder sortOrder = SortOrder::Ascending);
		~OrderByClause() override;

		OrderByClause(const OrderByClause&);
		OrderByClause& operator=(const OrderByClause&);
		OrderByClause(OrderByClause&&) noexcept ;
		OrderByClause& operator=(OrderByClause&&) noexcept ;

		[[nodiscard]] Field field() const;
		void setField(FieldRef fieldRef) const;
		[[nodiscard]] SortOrder sortOrder() const noexcept;
		void setSortOrder(SortOrder sortOrder) const noexcept;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<OrderByClauseImpl> impl_;
	};


	export inline OrderByClause orderBy(FieldRef fieldRef, SortOrder sortOrder = SortOrder::Ascending)
	{
		return { std::move(fieldRef), sortOrder };
	}
}
