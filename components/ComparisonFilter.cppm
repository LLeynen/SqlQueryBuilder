// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:ComparisonFilter;

import std;

import :BuilderTypes;
import :FilterBase;
import :Operand;
import :Variant;
import :Parameter;
import :ListOfValues;
import :Query;
import :Concepts;

namespace DataAccessLayer::SqlQueryBuilder
{
	class ComparisonFilterImpl;

	export class ComparisonFilter : public FilterBase
	{
	public:
		ComparisonFilter() noexcept;
		ComparisonFilter(Operand lhs, Comparison comparison, FilterValue filterValue) noexcept;
		ComparisonFilter(const std::initializer_list<const char*> fieldTokens, Comparison comparison, FilterValue filterValue)
			: ComparisonFilter { Operand{ FieldRef{ fieldTokens } }, comparison, std::move(filterValue) }
		{}
		ComparisonFilter(Operand lhs, Comparison comparison, Operand rhs) noexcept;
		ComparisonFilter(Comparison comparison, FilterValue filterValue) noexcept;
		ComparisonFilter(Comparison comparison, Operand operand) noexcept;
		~ComparisonFilter() override;

		ComparisonFilter(const ComparisonFilter&);
		ComparisonFilter& operator=(const ComparisonFilter&);
		ComparisonFilter(ComparisonFilter&&) noexcept;
		ComparisonFilter& operator=(ComparisonFilter&&) noexcept;

		[[nodiscard]] Comparison comparison() const noexcept;
		[[nodiscard]] Operand lhs() const;
		[[nodiscard]] ComparisonValue rhs() const;

		[[nodiscard]] FilterBasePtr clone() const override;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<ComparisonFilterImpl> impl_{};
	};

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
*/

	export [[nodiscard]] inline ComparisonFilter operator==(Operand lhs, Operand rhs) noexcept
	{
		return {std::move(lhs), Comparison::Equals, std::move(rhs)};
	}

	export [[nodiscard]] inline ComparisonFilter operator==(Operand lhs, FilterValue rhs) noexcept
	{
		return {std::move(lhs), Comparison::Equals, std::move(rhs)};
	}

	export [[nodiscard]] inline ComparisonFilter operator!=(Operand lhs, Operand rhs) noexcept
	{
		return {std::move(lhs), Comparison::NotEquals, std::move(rhs)};
	}

	export [[nodiscard]] inline ComparisonFilter operator>(Operand lhs, Operand rhs) noexcept
	{
		return {std::move(lhs), Comparison::GreaterThan, std::move(rhs)};
	}

	export [[nodiscard]] inline ComparisonFilter operator>=(Operand lhs, Operand rhs) noexcept
	{
		return {std::move(lhs), Comparison::GreaterOrEquals, std::move(rhs)};
	}

	export [[nodiscard]] inline ComparisonFilter operator<(Operand lhs, Operand rhs) noexcept
	{
		return {std::move(lhs), Comparison::LessThan, std::move(rhs)};
	}

	export [[nodiscard]] inline ComparisonFilter operator<=(Operand lhs, Operand rhs) noexcept
	{
		return {std::move(lhs), Comparison::LessOrEquals, std::move(rhs)};
	}

	export [[nodiscard]] inline ComparisonFilter operator!(Operand rhs) noexcept
	{
		return {Comparison::Not, std::move(rhs)};
	}

	export [[nodiscard]] ComparisonFilter operator==(Operand lhs, ConvertibleToFilterValue auto rhs) noexcept
		requires (!std::is_same_v<std::decay_t<decltype(rhs)>, Operand>)
	{
		return ComparisonFilter{ std::move(lhs), Comparison::Equals, FilterValue{ std::move(rhs) } };
	}

	export [[nodiscard]] ComparisonFilter operator!=(Operand lhs, ConvertibleToFilterValue auto rhs) noexcept
		requires (!std::is_same_v<std::decay_t<decltype(rhs)>, Operand>)
	{
		return ComparisonFilter{ std::move(lhs), Comparison::NotEquals, FilterValue{ std::move(rhs) } };
	}

	export [[nodiscard]] ComparisonFilter operator>(Operand lhs, ConvertibleToFilterValue auto rhs) noexcept
		requires (!std::is_same_v<std::decay_t<decltype(rhs)>, Operand>)
	{
		return ComparisonFilter{ std::move(lhs), Comparison::GreaterThan, FilterValue{ std::move(rhs) } };
	}

	export [[nodiscard]] ComparisonFilter operator>=(Operand lhs, ConvertibleToFilterValue auto rhs) noexcept
		requires (!std::is_same_v<std::decay_t<decltype(rhs)>, Operand>)
	{
		return ComparisonFilter{ std::move(lhs), Comparison::GreaterOrEquals, FilterValue{ std::move(rhs) } };
	}

	export [[nodiscard]] ComparisonFilter operator<(Operand lhs, ConvertibleToFilterValue auto rhs) noexcept
		requires (!std::is_same_v<std::decay_t<decltype(rhs)>, Operand>)
	{
		return ComparisonFilter{ std::move(lhs), Comparison::LessThan, FilterValue{ std::move(rhs) } };
	}

	export [[nodiscard]] ComparisonFilter operator<=(Operand lhs, ConvertibleToFilterValue auto rhs) noexcept
		requires (!std::is_same_v<std::decay_t<decltype(rhs)>, Operand>)
	{
		return ComparisonFilter{ std::move(lhs), Comparison::LessOrEquals, FilterValue{ std::move(rhs) } };
	}
}
