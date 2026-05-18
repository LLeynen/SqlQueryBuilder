// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :Parameter;

import std;

import :BuilderTypes;
import :Component;
import :IBuilder;

namespace DataAccessLayer::SqlQueryBuilder
{
    class ParameterImpl
    {
    public:
        ParameterImpl() = default;
        ParameterImpl(String parameterName)
            : parameterName_{std::move( parameterName )}
        {}
        ParameterImpl(String parameterName, ParameterMapPtr parameterMapPtr)
            : parameterMapPtr_{std::move( parameterMapPtr )}
            , parameterName_{std::move( parameterName )}
        {}
        ~ParameterImpl() = default;

        ParameterMapPtr parameterMapPtr_{};
        String parameterName_{};
    };


    Parameter::Parameter()
        : Component(ComponentId::Parameter)
        , impl_{ std::make_unique<ParameterImpl>() }
    {}


    Parameter::Parameter(const String& parameterName)
        : Component(ComponentId::Parameter)
        , impl_{ std::make_unique<ParameterImpl>(parameterName) }
    {}


    Parameter::Parameter(const String& parameterName, const ParameterMapPtr& parameterMapPtr)
        : Component(ComponentId::Parameter)
        , impl_{ std::make_unique<ParameterImpl>(parameterName, parameterMapPtr) }
    {}


    Parameter::~Parameter() = default;


    Parameter::Parameter(const Parameter& other)
        : Component(other)
        , impl_{ std::make_unique<ParameterImpl>(*other.impl_) }
    {}


    Parameter& Parameter::operator=(const Parameter& other)
    {
        if (this != &other)
        {
            Component::operator=(other);
            impl_ = std::make_unique<ParameterImpl>(*other.impl_);
        }

        return *this;
    }


    Parameter::Parameter(Parameter&& other) noexcept
        : Component(std::move(other))
        , impl_{ std::move(other.impl_) }
    {}


    Parameter& Parameter::operator=(Parameter&& other) noexcept
    {
        if (this != &other)
        {
            Component::operator=(std::move(other));
            impl_ = std::move(other.impl_);
        }

        return *this;
    }


    const String& Parameter::parameterName() const noexcept
    {
        return impl_->parameterName_;
    }


    void Parameter::setParameterName(const String& parameterName) const
    {
        impl_->parameterName_ = parameterName;
    }


    ParameterMapPtr Parameter::parameterMap() const noexcept
    {
        return impl_->parameterMapPtr_;
    }


    void Parameter::setParameterMap(const ParameterMapPtr& parameterMapPtr) const noexcept
    {
        impl_->parameterMapPtr_ = parameterMapPtr;
    }


    bool Parameter::empty() const noexcept
    {
        return impl_->parameterName_.empty();
    }


    String Parameter::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }


    Parameter parameter(const String& parameterName, const ParameterMapPtr& parameterMapPtr)
    {
        return { parameterName, parameterMapPtr};
    }


    Parameter parameter(const String& parameterName)
    {
        return Parameter(parameterName);
    }
}
