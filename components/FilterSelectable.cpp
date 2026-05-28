// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :FilterSelectable;

import std;

import :BuilderTypes;
import :FilterBase;

namespace DataAccessLayer::SqlQueryBuilder
{
	class FilterSelectableImpl
	{
	public:
		FilterSelectableImpl() = default;

		FilterSelectableImpl(const FilterBase& filter)
			: containedFilter_{ filter.clone() }
		{}

		~FilterSelectableImpl() = default;

		FilterSelectableImpl(const FilterSelectableImpl& other) = default;
		FilterSelectableImpl& operator=(const FilterSelectableImpl& other) = default;
		FilterSelectableImpl(FilterSelectableImpl&&) noexcept = default;
		FilterSelectableImpl& operator=(FilterSelectableImpl&& other) noexcept = default;

		FilterBasePtr containedFilter_{};
	};


    FilterSelectable::FilterSelectable() noexcept
        : Selectable(ComponentId::FilterSelectable)
		, impl_{ std::make_unique<FilterSelectableImpl>() }
    {}


    FilterSelectable::FilterSelectable(const FilterBase& filter, std::optional<Alias> alias)
        : Selectable(ComponentId::FilterSelectable)
		, impl_{ std::make_unique<FilterSelectableImpl>(std::move(filter)) }
    {
	    Selectable::setAlias(std::move(alias));
    }


	FilterSelectable::~FilterSelectable() = default;


    FilterSelectable::FilterSelectable(const FilterSelectable& other)
        : Selectable(ComponentId::FilterSelectable)
		, impl_{ std::make_unique<FilterSelectableImpl>(*other.impl_) }
    {
	    Selectable::setAlias(*other.aliasPtr());
    }


    FilterSelectable& FilterSelectable::operator=(const FilterSelectable& other)
    {
        if (this != &other)
        {
			Selectable::operator=(other);
			impl_ = std::make_unique<FilterSelectableImpl>(*other.impl_);
        }

        return *this;
    }


    FilterSelectable::FilterSelectable(FilterSelectable&& other) noexcept
        : Selectable(ComponentId::FilterSelectable)
		, impl_{ std::move(other.impl_) }
    {
	    Selectable::setAlias(*other.aliasPtr());
    }


    FilterSelectable& FilterSelectable::operator=(FilterSelectable&& other) noexcept
    {
        if (this != &other)
        {
            Selectable::operator=(std::move(other));
            impl_ = std::move(other.impl_);
        }

        return *this;
    }


	SelectablePtr FilterSelectable::clone() const
    {
    	return std::make_shared<FilterSelectable>(*this);
    }


    FilterBasePtr FilterSelectable::filter() const
    {
        return impl_->containedFilter_;
    }


    void FilterSelectable::setFilter(const FilterBase& filter) const
    {
        impl_->containedFilter_ = filter.clone();
    }


    String FilterSelectable::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }
}
