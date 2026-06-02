// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:LogicalFilter;

import std;

import :BuilderTypes;
import :FilterBase;
import :Operand;

namespace DataAccessLayer::SqlQueryBuilder
{
	class LogicalFilterImpl;

	export class LogicalFilter : public FilterBase
	{
	public:
		LogicalFilter() noexcept;
		LogicalFilter(const FilterBase& lhs, LogicOperator logicOperator, const FilterBase& rhs) noexcept;
		LogicalFilter(LogicOperator logicOperator, const FilterBase& filter) noexcept;
		~LogicalFilter() override;

		LogicalFilter(const LogicalFilter&);
		LogicalFilter& operator=(const LogicalFilter&);
		LogicalFilter(LogicalFilter&&) noexcept;
		LogicalFilter& operator=(LogicalFilter&&) noexcept;

		[[nodiscard]] LogicOperator logicOperator() const;
		[[nodiscard]] FilterBasePtr lhs() const noexcept;
		[[nodiscard]] FilterBasePtr rhs() const noexcept;

		[[nodiscard]] FilterBasePtr clone() const override;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<LogicalFilterImpl> impl_{};
	};


	export [[nodiscard]] inline LogicalFilter operator&&(const FilterBase& lhs, const FilterBase& rhs) noexcept
	{
		return {lhs, LogicOperator::And, rhs};
	}

	export [[nodiscard]] inline LogicalFilter operator||(const FilterBase& lhs, const FilterBase& rhs) noexcept
	{
		return {lhs, LogicOperator::Or, rhs};
	}
}
