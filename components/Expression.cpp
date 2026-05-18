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

		ExpressionImpl(const Operand& left, const Operator op, const Operand& right)
			: mode_ { Mode::Binary }
			, left_{ left }
			, op_{ op }
			, right_{ right }
		{}

		ExpressionImpl(const Operator op, const Operand& operand)
			: mode_ { Mode::Unary }
			, left_ { operand }
			, op_ { op }
		{}

		ExpressionImpl(const Operand& wrapped)
			: mode_ { Mode::Wrapper }
			, left_ { wrapped }
		{}

		~ExpressionImpl() = default;

		ExpressionImpl(const ExpressionImpl& other) = default;
		ExpressionImpl& operator=(const ExpressionImpl& other) = default;
		ExpressionImpl(ExpressionImpl&& other) noexcept = default;
		ExpressionImpl& operator=(ExpressionImpl&& other) noexcept = default;

		Mode mode_{};
		Operand left_{};
		Operator op_{};
		Operand right_{};
	};


	Expression::Expression() noexcept
		: Selectable{ ComponentId::Expression }
		, impl_{ std::make_unique<ExpressionImpl>() }
	{}


	Expression::Expression(const Operand& left, Operator op, const Operand& right, std::optional<Alias> alias) noexcept
		: Selectable{ ComponentId::Expression }
		, impl_ { std::make_unique<ExpressionImpl>(left, op, right) }
	{
		Selectable::setAlias(std::move(alias));
	}


	Expression::Expression(Operator op, const Operand& operand, std::optional<Alias> alias) noexcept
		: Selectable{ ComponentId::Expression}
		, impl_{ std::make_unique<ExpressionImpl>(op, operand) }
	{
		Selectable::setAlias(std::move(alias));
	}


	Expression::Expression(const Selectable& selectable, std::optional<Alias> alias) noexcept
		: Selectable{ ComponentId::Expression}
	{
		auto subjectClone = selectable.clone();

		impl_ = std::make_unique<ExpressionImpl>(Operand(std::move(subjectClone)));

		Selectable::setAlias(std::move(alias));
	}


	Expression::Expression(const ScalarFunction scalarFunction, const std::initializer_list<Operand> args, std::optional<Alias> alias)
		: Selectable{ ComponentId::Expression}
	{
		std::vector<Operand> processedArgs;
		processedArgs.reserve(args.size());

		for (const auto& arg : args)
		{
			if (arg.get())
			{
				const auto clonedArg = arg.get()->clone();
				clonedArg->suppressBrackets(true);
				processedArgs.push_back(clonedArg);
			}
		}

		const auto function = std::make_shared<Function>(scalarFunction, processedArgs);
		impl_ = std::make_unique<ExpressionImpl>(Operand(function));

		Selectable::setAlias(std::move(alias));
	}


	Expression::Expression(AggregateFunction aggregateFunction, const Selectable& selectable, std::optional<Alias> alias) noexcept
		: Selectable{ ComponentId::Expression}
	{
		auto subjectClone = selectable.clone();
		subjectClone->suppressBrackets(true);

		auto aggregate = std::make_shared<Aggregate>(aggregateFunction, std::move(subjectClone));
		impl_ = std::make_unique<ExpressionImpl>(Operand(aggregate));

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


	Operand Expression::left() const
	{
		return impl_->left_;
	}


	Operator Expression::op() const
	{
		return impl_->op_;
	}


	Operand Expression::right() const
	{
		return impl_->right_;
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
