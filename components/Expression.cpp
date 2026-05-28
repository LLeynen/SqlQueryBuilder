// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :Expression;

import :BuilderTypes;
import :Selectable;
import :Operand;

namespace DataAccessLayer::SqlQueryBuilder
{
	class ExpressionImpl
	{
	public:
		ExpressionImpl() = default;

		ExpressionImpl(FormulaArg lhs, const Operator op, FormulaArg rhs)
			: mode_ { Mode::Binary }
			, lhs_{ std::move(lhs) }
			, op_{ op }
			, rhs_{ std::move(rhs) }
		{}

		ExpressionImpl(const Operator op, FormulaArg lhs)
			: mode_{ Mode::Unary }
			, lhs_{ std::move(lhs) }
			, op_{ op }
		{}

		ExpressionImpl(Function func) noexcept
			: mode_ { Mode::Wrapper }
			, lhs_ {std::move(func) }
		{}

		ExpressionImpl(Aggregate aggregate) noexcept
			: mode_ { Mode::Wrapper }
			, lhs_ {std::move(aggregate) }
		{}


		~ExpressionImpl() = default;

		ExpressionImpl(const ExpressionImpl& other) = default;
		ExpressionImpl& operator=(const ExpressionImpl& other) = default;
		ExpressionImpl(ExpressionImpl&& other) noexcept = default;
		ExpressionImpl& operator=(ExpressionImpl&& other) noexcept = default;

		Mode mode_{ Mode::Binary };
		FormulaArg lhs_{std::monostate{}};
		Operator op_{};
		FormulaArg rhs_{std::monostate{}};
	};

	Expression::Expression() noexcept
		: Selectable{ ComponentId::Expression }
		, impl_{ std::make_unique<ExpressionImpl>() }
	{}

	Expression::Expression(Operand lhs, Operator op, Operand rhs, std::optional<Alias> alias)
		: Selectable{ ComponentId::Expression }
		, impl_ { std::make_unique<ExpressionImpl>(std::move(lhs), op, std::move(rhs)) }
	{
		Selectable::setAlias(std::move(alias));
	}

	Expression::Expression(Operand lhs, Operator op, FormulaValue rhs, std::optional<Alias> alias)
		: Selectable{ ComponentId::Expression }
		, impl_ { std::make_unique<ExpressionImpl>(std::move(lhs), op, std::move(rhs)) }
	{
		Selectable::setAlias(std::move(alias));
	}

	Expression::Expression(FormulaValue lhs, Operator op, Operand rhs, std::optional<Alias> alias)
		: Selectable{ ComponentId::Expression }
		, impl_ { std::make_unique<ExpressionImpl>(std::move(lhs), op, std::move(rhs)) }
	{
		Selectable::setAlias(std::move(alias));
	}

	Expression::Expression(Operator op, FormulaValue lhs, std::optional<Alias> alias)
		: Selectable{ ComponentId::Expression }
		, impl_ { std::make_unique<ExpressionImpl>(op, std::move(lhs)) }
	{
		Selectable::setAlias(std::move(alias));
	}

	Expression::Expression(Operator op, Operand lhs, std::optional<Alias> alias)
		: Selectable{ ComponentId::Expression }
	, impl_ { std::make_unique<ExpressionImpl>(op, std::move(lhs)) }
	{
		Selectable::setAlias(std::move(alias));
	}


	Expression::Expression(ScalarFunction scalarFunction, std::vector<FormulaArg> args, std::optional<Alias> alias)
	{
		std::vector<Operand> processedArgs;
//		processedArgs.reserve(args.size());

//		for (const auto& arg : args)
//		{
//			if (arg.get())
//			{
//				arg.get()->suppressBrackets(true);
//				processedArgs.push_back(std::move(arg));
//			}
//		}

//		const auto function = std::make_shared<Function>(scalarFunction, processedArgs);
//		impl_ = std::make_unique<ExpressionImpl>(*function);
		impl_ = std::make_unique<ExpressionImpl>(Function(scalarFunction, args));
		Selectable::setAlias(std::move(alias));
	}


	Expression::Expression(AggregateFunction aggregateFunction, FormulaArg arg, std::optional<Alias> alias) noexcept
	{
		/*
		auto subjectClone = selectable.clone();

		subjectClone->suppressBrackets(true);
		auto aggregate = std::make_shared<Aggregate>(aggregateFunction, std::move(subjectClone));
		impl_ = std::make_unique<ExpressionImpl>(*aggregate);
*/

		impl_ = std::make_unique<ExpressionImpl>(Aggregate(aggregateFunction, arg));
		Selectable::setAlias(std::move(alias));
	}


	Expression::~Expression() = default;


	Expression::Expression(const Expression& other)
		: Selectable(other) 
		, impl_{ std::make_unique<ExpressionImpl>(*other.impl_) } 
	{}


	Expression& Expression::operator=(const Expression& other)
	{
		if (this != &other) 
		{
			Selectable::operator=(other);
			impl_ = std::make_unique<ExpressionImpl>(*other.impl_); 
		}

		return *this;
	}


	Expression::Expression(Expression&& other) noexcept
		: Selectable(std::move(other))
		, impl_{ std::move(other.impl_) } 
	{}


	Expression& Expression::operator=(Expression&& other) noexcept
	{
		if (this != &other)
		{
			Selectable::operator=(std::move(other));
			impl_ = std::move(other.impl_); 
		}

		return *this;
	}


	Mode Expression::mode() const
	{
		return impl_->mode_;
	}


	FormulaArg Expression::lhs() const
	{
		return impl_->lhs_;
	}


	Operator Expression::op() const
	{
		return impl_->op_;
	}


	FormulaArg Expression::rhs() const
	{
		return impl_->rhs_;
	}


	SelectablePtr Expression::clone() const
	{
		return std::make_shared<Expression>(*this);
	}


	String Expression::toSql(const IBuilder* builderPtr) const
	{
		return Component::sqlImpl(builderPtr, *this);
	}
}
