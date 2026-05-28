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

	/*
	export inline Filter filter(Operand left, Comparison comparison, Operand right)
	{
		return { std::move(left), std::move(comparison), std::move(right) };
	}

	export inline Filter filter(Operand left, LogicOperator logicOperator, Operand right)
	{
		return { std::move(left), std::move(logicOperator), std::move(right) };
	}

	export inline Filter filter(Comparison comparison, Operand operand)
	{
		return { std::move(comparison), std::move(operand) };
	}

	export inline Filter filter(LogicOperator logicOperator, Operand operand)
	{
		return { std::move(logicOperator), std::move(operand) };
	}

	export [[nodiscard]] inline Filter operator&&(Filter lhs, Filter rhs) noexcept
	{
			return {Operand(std::move(lhs)), LogicOperator::And, Operand(std::move(rhs))};
	}

	export [[nodiscard]] inline Filter operator||(Filter lhs, Filter rhs) noexcept
	{
		return {Operand(std::move(lhs)), LogicOperator::Or, Operand(std::move(rhs))};
	}

	export [[nodiscard]] inline Filter operator==(Operand lhs, Operand rhs) noexcept
	{
		return {std::move(lhs), Comparison::Equals, std::move(rhs)};
	}

	export [[nodiscard]] inline Filter operator!=(Operand lhs, Operand rhs) noexcept
	{
		return {std::move(lhs), Comparison::NotEquals, std::move(rhs)};
	}

	export [[nodiscard]] inline Filter operator>(Operand lhs, Operand rhs) noexcept
	{
		return {std::move(lhs), Comparison::GreaterThan, std::move(rhs)};
	}

	export [[nodiscard]] inline Filter operator>=(Operand lhs, Operand rhs) noexcept
	{
		return {std::move(lhs), Comparison::GreaterOrEquals, std::move(rhs)};
	}

	export [[nodiscard]] inline Filter operator<(Operand lhs, Operand rhs) noexcept
	{
		return {std::move(lhs), Comparison::LessThan, std::move(rhs)};
	}

	export [[nodiscard]] inline Filter operator<=(Operand lhs, Operand rhs) noexcept
	{
		return {std::move(lhs), Comparison::LessOrEquals, std::move(rhs)};
	}

	export [[nodiscard]] inline Filter operator!(Operand rhs) noexcept
	{
		return {Comparison::Not, std::move(rhs)};
	}
*/
}
