// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :Selectable;

import std;

import :BuilderTypes;
import :Component;
import :Alias;

namespace DataAccessLayer::SqlQueryBuilder
{
    class SelectableImpl
    {
    public:
        SelectableImpl() = default;
		~SelectableImpl() = default;

        SelectableImpl(const SelectableImpl& other) = default;
		SelectableImpl& operator=(const SelectableImpl&) = default;
		SelectableImpl(SelectableImpl&&) = default;
		SelectableImpl& operator=(SelectableImpl&&) = default;

        AliasPtr alias_{};
        bool suppressBrackets_{ false };
    };


    Selectable::Selectable()
        : Component(ComponentId::Selectable)
        , impl_{ std::make_unique<SelectableImpl>() }
    {}


    Selectable::Selectable(const ComponentId componentId)
        : Component(componentId)
        , impl_{ std::make_unique<SelectableImpl>() }
    {}


	Selectable::Selectable(const Selectable& other)
        : Component(other)
        , impl_{ std::make_unique<SelectableImpl>(*other.impl_) }
    {}


    Selectable& Selectable::operator=(const Selectable& other)
    {
        if (this != &other)
        {
            Component::operator=(other);
            impl_ = std::make_unique<SelectableImpl>(*other.impl_);
        }

        return *this;
    }


    Selectable::~Selectable() = default;


    Selectable::Selectable(Selectable&&) noexcept = default;


    Selectable& Selectable::operator=(Selectable&&) noexcept = default;


    AliasPtr Selectable::aliasPtr() const
    {
        return impl_->alias_;
    }


    const String& Selectable::alias() const
    {
        return  impl_->alias_->value();
    }


    void Selectable::setAlias(std::optional<Alias> alias) const
    {
        if (alias.has_value())
        {
            impl_->alias_ = std::make_shared<Alias>(std::move(alias.value()));
            impl_->alias_->setAliasType(AliasType::Column);
        }
    }


    bool Selectable::hasAlias() const noexcept
    {
        return (impl_->alias_ != nullptr);
    }


    void Selectable::suppressAlias(const bool suppressFlag) const noexcept
    {
        if (hasAlias())
        {
            impl_->alias_->suppress(suppressFlag);
        }
    }


    [[nodiscard]] bool Selectable::isAliasSuppressed() const noexcept
    {
        if (hasAlias())
        {
            return impl_->alias_->isSuppressed();
        }
        else
        {
            return false;
        }
    }


    void Selectable::suppressBrackets(bool suppressFlag) const noexcept
    {
        impl_->suppressBrackets_ = suppressFlag;
    }


    [[nodiscard]] bool Selectable::areBracketsSuppressed() const noexcept
    {
        return impl_->suppressBrackets_;
    }
}
