// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:LimitClause;

import std;

import :BuilderTypes;
import :Component;

namespace DataAccessLayer::SqlQueryBuilder
{
	class LimitClauseImpl;

	export class LimitClause : public Component
	{
	public:
		LimitClause() noexcept;
		LimitClause(int quantity) noexcept;
		~LimitClause() override;

		LimitClause(const LimitClause&);
		LimitClause& operator=(const LimitClause&);
		LimitClause(LimitClause&&) noexcept ;
		LimitClause& operator=(LimitClause&&) noexcept ;

		[[nodiscard]] int quantity() const noexcept;
		void setQuantity(int quantity) const noexcept;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<LimitClauseImpl> impl_;
	};

	export inline LimitClause limit(int quantity)
	{
		return { quantity };
	}
}
