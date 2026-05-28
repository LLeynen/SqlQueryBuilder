// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :Query;

import std;

import :BuilderTypes;
import :IBuilder;

import QueryBuilder;

namespace DataAccessLayer::SqlQueryBuilder
{
    class QueryImpl
    {
    public:
        QueryImpl() = default;
        QueryImpl(QueryBuilder queryBuilder)
            : querySource_{ std::make_shared<QueryBuilder>(std::move(queryBuilder)) }
        {}
        QueryImpl(QueryBuilderPtr queryBuilderPtr)
            : querySource_{ queryBuilderPtr }
		{}
        QueryImpl(String rawSql)
            : querySource_{ std::move(rawSql) }
		{}
        ~QueryImpl() = default;

        QueryImpl(const QueryImpl& other)
        {
			copyFrom(other);
		}

        QueryImpl& operator=(const QueryImpl& other)
        {
            if (this != &other)
            {
                copyFrom(other);
            }
			return *this;
        }

        QueryImpl(QueryImpl&& other) noexcept
            : querySource_{ std::move(other.querySource_) }
        {}

        QueryImpl& operator=(QueryImpl&& other) noexcept
        {
            if (this != &other)
            {
                querySource_ = std::move(other.querySource_);
            }
            return *this;
        }

        void copyFrom(const QueryImpl& other);

        QuerySourceType querySource_{};
    };


    Query::Query() noexcept
        : Component(ComponentId::Query)
		, impl_{ std::make_unique<QueryImpl>() }
    {}


    Query::Query(QueryBuilder queryBuilder)
        : Component(ComponentId::Query)
		, impl_{ std::make_unique<QueryImpl>(std::move(queryBuilder)) }
    {}


    Query::Query(QueryBuilderPtr queryBuilderPtr) noexcept
        : Component(ComponentId::Query)
		, impl_{ std::make_unique<QueryImpl>(queryBuilderPtr) }
    {}


    Query::Query(String rawSql)
        : Component(ComponentId::Query)
		, impl_{ std::make_unique<QueryImpl>(std::move(rawSql)) }
    {}


	Query::~Query() = default;


    Query::Query(const Query& other)
        : Component(ComponentId::Query)
		, impl_{ std::make_unique<QueryImpl>(*other.impl_) }
    {}


    Query& Query::operator=(const Query& other)
    {
        if (this != &other)
        {
			Component::operator=(other);
			impl_ = std::make_unique<QueryImpl>(*other.impl_);
        }

        return *this;
    }


    Query::Query(Query&& other) noexcept
        : Component(ComponentId::Query)
		, impl_{ std::move(other.impl_) }
    {}


    Query& Query::operator=(Query&& other) noexcept
    {
        if (this != &other)
        {
            Component::operator=(std::move(other));
            impl_ = std::move(other.impl_);
        }

        return *this;
    }


    QuerySourceType Query::querySource() const
    {
        return impl_->querySource_;
    }


    void Query::setQuerySource(QuerySourceType querySource) const
    {
        impl_->querySource_ = std::move(querySource);
    }


    String Query::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }


    void QueryImpl::copyFrom(const QueryImpl& other)
    {
        if (std::holds_alternative<std::shared_ptr<QueryBuilder>>(other.querySource_))
        {
            if (const auto otherQueryBuilder = std::get<std::shared_ptr<QueryBuilder>>(other.querySource_))
            {
                querySource_ = std::make_shared<QueryBuilder>(*otherQueryBuilder);
            }
            else
            {
                querySource_ = std::shared_ptr<QueryBuilder>{};
            }
        }
        else
        {
            querySource_ = std::get<String>(other.querySource_);
        }
    }
}
