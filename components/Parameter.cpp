// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :Parameter;

import std;

import :BuilderTypes;
import :ParameterRegistry;

namespace DataAccessLayer::SqlQueryBuilder
{
    class ParameterImpl
    {
    public:
        ParameterImpl() = default;
        ParameterImpl(String name)
            : name_{std::move( name )}
        {}
        ~ParameterImpl() = default;

        ParameterImpl(const ParameterImpl& other) = default;
        ParameterImpl& operator=(const ParameterImpl& other) = default;
        ParameterImpl(ParameterImpl&&) noexcept = default;
        ParameterImpl& operator=(ParameterImpl&&) noexcept ;

        String name_{};
    };


    Parameter::Parameter()
        : Component(ComponentId::Parameter)
        , impl_{ std::make_unique<ParameterImpl>() }
    {}


    Parameter::Parameter(String name)
        : Component(ComponentId::Parameter)
        , impl_{ std::make_unique<ParameterImpl>(std::move(name)) }
    {
        if (ParameterRegistry::get(impl_->name_).isNull())
        {
            ParameterRegistry::set(impl_->name_, Variant{});
        }
    }


    Parameter::Parameter(String name, Variant value)
        : Component(ComponentId::Parameter)
        , impl_{ std::make_unique<ParameterImpl>(std::move(name)) }
    {
        ParameterRegistry::set(impl_->name_, std::move(value));
    }

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


    [[nodiscard]] String Parameter::name() const noexcept
    {
        return impl_->name_;
    }


    void Parameter::setName(String name) const
    {
        impl_->name_ = std::move(name);
    }


    [[nodiscard]] Variant Parameter::value() const noexcept
    {
        return ParameterRegistry::get(impl_->name_);
    }


    void Parameter::setValue(Variant value) const noexcept
    {
        ParameterRegistry::set(impl_->name_, std::move(value));
    }


    bool Parameter::empty() const noexcept
    {
        return impl_->name_.empty();
    }


    bool Parameter::isNull() const noexcept
    {
        return value().isNull();
    }


    Parameter& Parameter::operator=(Variant value) noexcept
    {
        setValue(std::move(value));
        return *this;
    }


    String Parameter::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }


    Parameter parameter(String name)
    {
        return { std::move(name) };
    }


    Parameter parameter(String name, Variant value)
    {
        return { std::move(name), std::move(value) };
    }
}
