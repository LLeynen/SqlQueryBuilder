// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :QuerySelectable;

import std;

import :BuilderTypes;
import :Query;

namespace DataAccessLayer::SqlQueryBuilder
{
	class QuerySelectableImpl
	{
	public:
		QuerySelectableImpl() = default;

		QuerySelectableImpl(QueryBuilder queryBuilder)
			: containedQuery_{ std::make_shared<Query>(std::move(queryBuilder)) }
		{}

		QuerySelectableImpl(QueryBuilderPtr queryBuilderPtr)
			: containedQuery_{ std::make_shared<Query>(queryBuilderPtr) }
		{}

		QuerySelectableImpl(String rawSql)
			: containedQuery_{ std::make_shared<Query>(std::move(rawSql)) }
		{}

		~QuerySelectableImpl() = default;

		QuerySelectableImpl(const QuerySelectableImpl& other) = default;
		QuerySelectableImpl& operator=(const QuerySelectableImpl& other) = default;
		QuerySelectableImpl(QuerySelectableImpl&&) noexcept = default;
		QuerySelectableImpl& operator=(QuerySelectableImpl&& other) noexcept = default;

		QueryPtr containedQuery_{};
	};


    QuerySelectable::QuerySelectable() noexcept
        : Selectable(ComponentId::QuerySelectable)
		, impl_{ std::make_unique<QuerySelectableImpl>() }
    {}


    QuerySelectable::QuerySelectable(QueryBuilder queryBuilder, std::optional<Alias> alias)
        : Selectable(ComponentId::QuerySelectable)
		, impl_{ std::make_unique<QuerySelectableImpl>(std::move(queryBuilder)) }
    {
	    Selectable::setAlias(std::move(alias));
    }


    QuerySelectable::QuerySelectable(QueryBuilderPtr queryBuilderPtr, std::optional<Alias> alias)
        : Selectable(ComponentId::QuerySelectable)
		, impl_{ std::make_unique<QuerySelectableImpl>(queryBuilderPtr) }
    {
	    Selectable::setAlias(std::move(alias));
    }


    QuerySelectable::QuerySelectable(String rawSql, std::optional<Alias> alias)
        : Selectable(ComponentId::QuerySelectable)
		, impl_{ std::make_unique<QuerySelectableImpl>(std::move(rawSql)) }
    {
	    Selectable::setAlias(std::move(alias));
    }


	QuerySelectable::~QuerySelectable() = default;


    QuerySelectable::QuerySelectable(const QuerySelectable& other)
        : Selectable(ComponentId::QuerySelectable)
		, impl_{ std::make_unique<QuerySelectableImpl>(*other.impl_) }
    {
	    Selectable::setAlias(*other.aliasPtr());
    }


    QuerySelectable& QuerySelectable::operator=(const QuerySelectable& other)
    {
        if (this != &other)
        {
			Selectable::operator=(other);
			impl_ = std::make_unique<QuerySelectableImpl>(*other.impl_);
        }

        return *this;
    }


    QuerySelectable::QuerySelectable(QuerySelectable&& other) noexcept
        : Selectable(ComponentId::QuerySelectable)
		, impl_{ std::move(other.impl_) }
    {
	    Selectable::setAlias(*other.aliasPtr());
    }


    QuerySelectable& QuerySelectable::operator=(QuerySelectable&& other) noexcept
    {
        if (this != &other)
        {
            Selectable::operator=(std::move(other));
            impl_ = std::move(other.impl_);
        }

        return *this;
    }


	SelectablePtr QuerySelectable::clone() const
    {
    	return std::make_shared<QuerySelectable>(*this);
    }


    QueryPtr QuerySelectable::query() const
    {
        return impl_->containedQuery_;
    }


    void QuerySelectable::setQuery(Query query) const
    {
        impl_->containedQuery_ = std::make_shared<Query>(std::move(query));
    }


    String QuerySelectable::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }
}
