// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :Function;

import std;

import :BuilderTypes;
import :Selectable;
import :Alias;

namespace DataAccessLayer::SqlQueryBuilder
{
	class FunctionImpl
	{
	public:
		FunctionImpl() = default;

		FunctionImpl(const ScalarFunction function)
			: function_{ function }
		{}

		~FunctionImpl() = default;

		FunctionImpl(const FunctionImpl& other) = default;
		FunctionImpl& operator=(const FunctionImpl& other) = default;
		FunctionImpl(FunctionImpl&& other) noexcept = default;
		FunctionImpl& operator=(FunctionImpl&& other) noexcept = default;

		ScalarFunction function_ {};
		SelectableList selectableList_ {};
	};


    Function::Function() noexcept
        : Selectable(ComponentId::Function)
		, impl_{ std::make_unique<FunctionImpl>() }
    {}

	Function::Function(ScalarFunction scalarFunction, const std::initializer_list<Operand> args, std::optional<Alias> alias) noexcept
		: Selectable(ComponentId::Function)
		, impl_{ std::make_unique<FunctionImpl>(scalarFunction) }
    {
    	impl_->selectableList_.reserve(args.size());

    	for (const auto& arg : args)
    	{
    		impl_->selectableList_.push_back(arg.get());
    	}

    	Selectable::setAlias(std::move(alias));
    }


	Function::Function(ScalarFunction scalarFunction, std::vector<Operand> args, std::optional<Alias> alias) noexcept
		: Selectable(ComponentId::Function)
		, impl_{ std::make_unique<FunctionImpl>(scalarFunction) }
    {
    	impl_->selectableList_.reserve(args.size());

    	for (const auto& arg : args)
    	{
    		impl_->selectableList_.push_back(std::move(arg.get()));
    	}

    	Selectable::setAlias(alias);
    }

	Function::~Function() = default;


    Function::Function(const Function& other)
        : Selectable(ComponentId::Function)
		, impl_{ std::make_unique<FunctionImpl>(*other.impl_) }
    {
	    Selectable::setAlias(other.alias());
    }


    Function& Function::operator=(const Function& other)
    {
        if (this != &other)
        {
			Selectable::operator=(other);
			impl_ = std::make_unique<FunctionImpl>(*other.impl_);
        }

        return *this;
    }


    Function::Function(Function&& other) noexcept
        : Selectable(ComponentId::Function)
		, impl_{ std::move(other.impl_) }
    {
	    Selectable::setAlias(other.alias());
    }


    Function& Function::operator=(Function&& other) noexcept
    {
        if (this != &other)
        {
            Selectable::operator=(std::move(other));
            impl_ = std::move(other.impl_);
        }

        return *this;
    }


	SelectablePtr Function::clone() const
    {
    	return std::make_shared<Function>(*this);
    }


    ScalarFunction Function::function() const noexcept
    {
        return impl_->function_;
    }


    void Function::setFunction(const ScalarFunction function) const noexcept
    {
        impl_->function_ = function;
    }


	SelectableList Function::selectableList() const noexcept
    {
	    return impl_->selectableList_;
    }

	void Function::setSelectableList(const SelectableList& selectableList) const noexcept
    {
	    impl_->selectableList_ = selectableList;
    }


    String Function::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }
}
