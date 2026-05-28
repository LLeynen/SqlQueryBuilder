// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :LogicalFilter;

import :BuilderTypes;
import :Selectable;
import :Operand;

namespace DataAccessLayer::SqlQueryBuilder
{
	class LogicalFilterImpl
	{
	public:
		LogicalFilterImpl() = default;

		LogicalFilterImpl(const FilterBase& lhs, const LogicOperator logicOperator, const FilterBase& rhs) noexcept
			: lhs_{ lhs.clone() }
			, logicOperator_ { logicOperator }
			, rhs_{ rhs.clone() }
		{}

		LogicalFilterImpl(const LogicOperator logicOperator, const FilterBase& rhs) noexcept
			: lhs_ { nullptr }
			, logicOperator_{ logicOperator }
			, rhs_{ rhs.clone() }
		{}

		~LogicalFilterImpl() = default;

		LogicalFilterImpl(const LogicalFilterImpl& other) = default;
		LogicalFilterImpl& operator=(const LogicalFilterImpl& other) = default;
		LogicalFilterImpl(LogicalFilterImpl&& other) noexcept = default;
		LogicalFilterImpl& operator=(LogicalFilterImpl&& other) noexcept = default;

		FilterBasePtr lhs_{};
		LogicOperator logicOperator_{};
		FilterBasePtr rhs_{};
	};


	LogicalFilter::LogicalFilter() noexcept
		: FilterBase{ComponentId::LogicalFilter, ConditionMode::Logical }
		, impl_{ std::make_unique<LogicalFilterImpl>() }
	{}


	LogicalFilter::LogicalFilter(const FilterBase& lhs, LogicOperator logicOperator, const FilterBase& rhs) noexcept
		: FilterBase{ ComponentId::LogicalFilter, ConditionMode::Logical }
		, impl_ { std::make_unique<LogicalFilterImpl>(lhs, logicOperator, rhs) }
	{}


	LogicalFilter::LogicalFilter(LogicOperator logicOperator, const FilterBase& rhs) noexcept
		: FilterBase{ ComponentId::LogicalFilter, ConditionMode::Logical }
		, impl_{ std::make_unique<LogicalFilterImpl>(logicOperator, rhs) }
	{}


	LogicalFilter::~LogicalFilter() = default;


	LogicalFilter::LogicalFilter(const LogicalFilter& other)
		: FilterBase(other)
		, impl_{ std::make_unique<LogicalFilterImpl>(*other.impl_) }
	{}


	LogicalFilter& LogicalFilter::operator=(const LogicalFilter& other)
	{
		if (this != &other)
		{
			FilterBase::operator=(other);
			impl_ = std::make_unique<LogicalFilterImpl>(*other.impl_);
		}

		return *this;
	}


	LogicalFilter::LogicalFilter(LogicalFilter&& other) noexcept
		: FilterBase(std::move(other))
		, impl_{ std::move(other.impl_) }
	{}


	LogicalFilter& LogicalFilter::operator=(LogicalFilter&& other) noexcept
	{
		if (this != &other)
		{
			FilterBase::operator=(std::move(other));
			impl_ = std::move(other.impl_);
		}

		return *this;
	}


	FilterBasePtr LogicalFilter::lhs() const noexcept
	{
		return impl_->lhs_ ? impl_->lhs_->clone() : nullptr;
	}


	LogicOperator LogicalFilter::logicOperator() const
	{
		return impl_->logicOperator_;
	}


	FilterBasePtr LogicalFilter::rhs() const noexcept
	{
		return impl_->rhs_ ? impl_->rhs_->clone() : nullptr;
	}


	FilterBasePtr LogicalFilter::clone() const
	{
		return std::make_shared<LogicalFilter>(*this);
	}


	String LogicalFilter::toSql(const IBuilder* builderPtr) const
	{
		return Component::sqlImpl(builderPtr, *this);
	}
}
