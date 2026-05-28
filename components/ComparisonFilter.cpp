// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :ComparisonFilter;

import :BuilderTypes;
import :FilterBase;
import :Operand;

namespace DataAccessLayer::SqlQueryBuilder
{
	class ComparisonFilterImpl
	{
	public:
		ComparisonFilterImpl() = default;

		ComparisonFilterImpl(Operand lhs, Comparison comparison, FilterValue filterValue) noexcept
			: lhs_{ std::move(lhs) }
			, comparison_ { comparison }
			, rhs_{ std::move(filterValue) }
		{}

		ComparisonFilterImpl(Operand lhs, Comparison comparison, Operand rhs) noexcept
			: lhs_{ std::move(lhs) }
			, comparison_ { comparison }
			, rhs_{ std::move(rhs) }
		{}

		ComparisonFilterImpl(Comparison comparison, FilterValue filterValue) noexcept
			: lhs_ {}
			, comparison_ { comparison }
			, rhs_ { std::move(filterValue) }
		{}

		ComparisonFilterImpl(Comparison comparison, Operand operand) noexcept
			: lhs_ {}
			, comparison_ { comparison }
			, rhs_ { std::move(operand) }
		{}

		~ComparisonFilterImpl() = default;

		ComparisonFilterImpl(const ComparisonFilterImpl& other) = default;
		ComparisonFilterImpl& operator=(const ComparisonFilterImpl& other) = default;
		ComparisonFilterImpl(ComparisonFilterImpl&& other) noexcept = default;
		ComparisonFilterImpl& operator=(ComparisonFilterImpl&& other) noexcept = default;

		Operand lhs_{};
		Comparison comparison_{};
		ComparisonValue rhs_{};
	};


	ComparisonFilter::ComparisonFilter() noexcept
		: FilterBase{ ComponentId::ComparisonFilter, ConditionMode::Comparison }
		, impl_{ std::make_unique<ComparisonFilterImpl>() }
	{}


	ComparisonFilter::ComparisonFilter(Operand lhs, Comparison comparison, FilterValue filterValue) noexcept
		: FilterBase{ ComponentId::ComparisonFilter, ConditionMode::Comparison }
		, impl_ { std::make_unique<ComparisonFilterImpl>(std::move(lhs), comparison, std::move(filterValue)) }
	{}


	ComparisonFilter::ComparisonFilter(Operand lhs, Comparison comparison, Operand rhs) noexcept
		: FilterBase{ ComponentId::ComparisonFilter, ConditionMode::Comparison }
	, impl_ { std::make_unique<ComparisonFilterImpl>(std::move(lhs), comparison, std::move(rhs)) }
	{}


	ComparisonFilter::ComparisonFilter(Comparison comparison, FilterValue filterValue) noexcept
		: FilterBase{ ComponentId::ComparisonFilter, ConditionMode::Unary }
	, impl_{ std::make_unique<ComparisonFilterImpl>(comparison, std::move(filterValue)) }
	{}


	ComparisonFilter::ComparisonFilter(Comparison comparison, Operand operand) noexcept
		: FilterBase{ ComponentId::ComparisonFilter, ConditionMode::Unary }
		, impl_{ std::make_unique<ComparisonFilterImpl>(comparison, std::move(operand)) }
	{}


	ComparisonFilter::~ComparisonFilter() = default;


	ComparisonFilter::ComparisonFilter(const ComparisonFilter& other)
		: FilterBase(other)
		, impl_{ std::make_unique<ComparisonFilterImpl>(*other.impl_) }
	{}


	ComparisonFilter& ComparisonFilter::operator=(const ComparisonFilter& other)
	{
		if (this != &other)
		{
			FilterBase::operator=(other);
			impl_ = std::make_unique<ComparisonFilterImpl>(*other.impl_);
		}

		return *this;
	}


	ComparisonFilter::ComparisonFilter(ComparisonFilter&& other) noexcept
		: FilterBase(std::move(other))
		, impl_{ std::move(other.impl_) }
	{}


	ComparisonFilter& ComparisonFilter::operator=(ComparisonFilter&& other) noexcept
	{
		if (this != &other)
		{
			FilterBase::operator=(std::move(other));
			impl_ = std::move(other.impl_);
		}

		return *this;
	}


	Comparison ComparisonFilter::comparison() const noexcept
	{
		return impl_->comparison_;
	}


	Operand ComparisonFilter::lhs() const
	{
		return impl_->lhs_;
	}


	ComparisonValue ComparisonFilter::rhs() const
	{
		return impl_->rhs_;
	}


	FilterBasePtr ComparisonFilter::clone() const
	{
		return std::make_shared<ComparisonFilter>(*this);
	}


	String ComparisonFilter::toSql(const IBuilder* builderPtr) const
	{
		return Component::sqlImpl(builderPtr, *this);
	}
}
