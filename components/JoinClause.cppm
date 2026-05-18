// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:JoinClause;

import std;

import :BuilderTypes;
import :Component;

namespace DataAccessLayer::SqlQueryBuilder
{
	class JoinClauseImpl;

	export class JoinClause : public Component
	{
	public:
		JoinClause();
		JoinClause(const Field& fromSqlField, Comparison sqlComparison, const Field& toSqlField, JoinType sqlJoinType = JoinType::InnerJoin);
		~JoinClause() override;

		JoinClause(const JoinClause&);
		JoinClause& operator=(const JoinClause&);
		JoinClause(JoinClause&&) noexcept ;
		JoinClause& operator=(JoinClause&&) noexcept ;

		[[nodiscard]] const Field& fromField() const noexcept;
		void setFromField(const Field& fromField);
		[[nodiscard]] const Comparison comparison() const noexcept;
		void setComparison(Comparison comparison) noexcept;
		[[nodiscard]] const Field& toField() const noexcept;
		void setToField(const Field& toField);
		[[nodiscard]] const JoinType joinType() const noexcept;
		void setJoinType(JoinType joinType) noexcept;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<JoinClauseImpl> impl_;
	};
}
