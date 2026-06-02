// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :ParameterSelectable;

import std;

import :BuilderTypes;
import :Selectable;
import :Alias;

namespace DataAccessLayer::SqlQueryBuilder
{
	class ParameterSelectableImpl
	{
	public:
		ParameterSelectableImpl() = default;

		ParameterSelectableImpl(String parameterName)
			: containedParameter_{ std::make_shared<Parameter>(std::move(parameterName)) }
		{}

		ParameterSelectableImpl(Parameter parameter)
			: containedParameter_{ std::make_shared<Parameter>(std::move(parameter)) }
		{}

		~ParameterSelectableImpl() = default;

		ParameterSelectableImpl(const ParameterSelectableImpl& other) = default;
		ParameterSelectableImpl& operator=(const ParameterSelectableImpl& other) = default;
		ParameterSelectableImpl(ParameterSelectableImpl&& other) noexcept = default;
		ParameterSelectableImpl& operator=(ParameterSelectableImpl&& other) noexcept = default;

		ParameterPtr containedParameter_{};
		};


	ParameterSelectable::ParameterSelectable() noexcept
        : Selectable(ComponentId::ParameterSelectable)
		, impl_{ std::make_unique<ParameterSelectableImpl>() }
    {}


	ParameterSelectable::ParameterSelectable(String parameterName, std::optional<Alias> alias)
        : Selectable(ComponentId::ParameterSelectable)
		, impl_{ std::make_unique<ParameterSelectableImpl>(Parameter(std::move(parameterName))) }
    {
	    Selectable::setAlias(std::move(alias));
    }


	ParameterSelectable::ParameterSelectable(Parameter parameter, std::optional<Alias> alias)
		: Selectable(ComponentId::ParameterSelectable)
		, impl_{ std::make_unique<ParameterSelectableImpl>(std::move(parameter)) }
	{
		std::cout << "ParameterSelectable::ParameterSelectable(parameter, alias)" << std::endl;
		Selectable::setAlias(std::move(alias));
	}


	ParameterSelectable::~ParameterSelectable() = default;


    ParameterSelectable::ParameterSelectable(const ParameterSelectable& other)
        : Selectable(ComponentId::ParameterSelectable)
		, impl_{ std::make_unique<ParameterSelectableImpl>(*other.impl_) }
    {
	    Selectable::setAlias(*other.aliasPtr());
    }


	ParameterSelectable& ParameterSelectable::operator=(const ParameterSelectable& other)
    {
        if (this != &other)
        {
			Selectable::operator=(other);
			impl_ = std::make_unique<ParameterSelectableImpl>(*other.impl_);
        }

        return *this;
    }


    ParameterSelectable::ParameterSelectable(ParameterSelectable&& other) noexcept
        : Selectable(ComponentId::ParameterSelectable)
		, impl_{ std::move(other.impl_) }
    {
	    Selectable::setAlias(*other.aliasPtr());
    }


    ParameterSelectable& ParameterSelectable::operator=(ParameterSelectable&& other) noexcept
    {
        if (this != &other)
        {
            Selectable::operator=(std::move(other));
            impl_ = std::move(other.impl_);
        }

        return *this;
    }


	SelectablePtr ParameterSelectable::clone() const
    {
    	return std::make_shared<ParameterSelectable>(*this);
    }


	[[nodiscard]] ParameterPtr ParameterSelectable::parameterPtr() const
    {
    	return impl_->containedParameter_;
    }


	void ParameterSelectable::setParameter(Parameter parameter) const
	{
	    impl_->containedParameter_ = std::make_shared<Parameter>(std::move(parameter));
    }


    String ParameterSelectable::parameterName() const noexcept
    {
        return impl_->containedParameter_->name();
    }


    void ParameterSelectable::setParameterName(String parameterName) const
    {
    	impl_->containedParameter_->setName(std::move(parameterName));
    }


    String ParameterSelectable::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }
}
