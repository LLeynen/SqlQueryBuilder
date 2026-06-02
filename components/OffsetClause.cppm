// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:OffsetClause;

import std;

import :BuilderTypes;
import :Component;

namespace DataAccessLayer::SqlQueryBuilder
{
	class OffsetClauseImpl;

	export class OffsetClause : public Component
	{
	public:
		OffsetClause() noexcept;
		OffsetClause(int quantity) noexcept;
		~OffsetClause() override;

		OffsetClause(const OffsetClause&);
		OffsetClause& operator=(const OffsetClause&);
		OffsetClause(OffsetClause&&) noexcept ;
		OffsetClause& operator=(OffsetClause&&) noexcept ;

		[[nodiscard]] int quantity() const noexcept;
		void setQuantity(int quantity) const noexcept;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<OffsetClauseImpl> impl_;
	};


	export inline OffsetClause offset(int quantity)
	{
		return { quantity };
	}
}
