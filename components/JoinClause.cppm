// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:JoinClause;

import std;

import :BuilderTypes;
import :Component;
import :Field;

namespace DataAccessLayer::SqlQueryBuilder
{
	class JoinClauseImpl;

	export class JoinClause : public Component
	{
	public:
		JoinClause();
		JoinClause(FieldRef fromFieldRef, Comparison sqlComparison, FieldRef toFieldRef, JoinType joinType = JoinType::InnerJoin);
		~JoinClause() override;

		JoinClause(const JoinClause&);
		JoinClause& operator=(const JoinClause&);
		JoinClause(JoinClause&&) noexcept ;
		JoinClause& operator=(JoinClause&&) noexcept ;

		[[nodiscard]] Field fromField() const noexcept;
		void setFromField(FieldRef fromFieldRef) const;
		[[nodiscard]] Comparison comparison() const noexcept;
		void setComparison(Comparison comparison) const noexcept;
		[[nodiscard]] Field toField() const noexcept;
		void setToField( FieldRef toFieldRef);
		[[nodiscard]] JoinType joinType() const noexcept;
		void setJoinType(JoinType joinType) const noexcept;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<JoinClauseImpl> impl_;
	};

	export inline JoinClause join(FieldRef fromFieldRef, Comparison sqlComparison, FieldRef toFieldRef, JoinType joinType = JoinType::InnerJoin)
	{
		return { std::move(fromFieldRef), sqlComparison, std::move(toFieldRef), joinType };
	}
}
