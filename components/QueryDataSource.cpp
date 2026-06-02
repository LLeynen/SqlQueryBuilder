// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :QueryDataSource;

import std;

import :BuilderTypes;
import :DataSource;

namespace DataAccessLayer::SqlQueryBuilder
{
    class QueryDataSourceImpl
    {
    public:
        QueryDataSourceImpl() = default;

        QueryDataSourceImpl(QueryBuilder queryBuilder)
            : containedQuery_{ std::make_shared<Query>(std::move(queryBuilder)) }
        {}

        QueryDataSourceImpl(QueryBuilderPtr queryBuilderPtr)
            : containedQuery_{ std::make_shared<Query>(queryBuilderPtr) }
		{}

        QueryDataSourceImpl(String rawSql)
            : containedQuery_{ std::make_shared<Query>(std::move(rawSql)) }
		{}

        ~QueryDataSourceImpl() = default;

        QueryDataSourceImpl(const QueryDataSourceImpl& other)
        {
			copyFrom(other);
		}

        QueryDataSourceImpl& operator=(const QueryDataSourceImpl& other)
        {
            if (this != &other)
            {
                copyFrom(other);
            }
			return *this;
        }

        QueryDataSourceImpl(QueryDataSourceImpl&& other) noexcept
            : containedQuery_{ std::move(other.containedQuery_) }
        {}

        QueryDataSourceImpl& operator=(QueryDataSourceImpl&& other) noexcept
        {
            if (this != &other)
            {
                containedQuery_ = std::move(other.containedQuery_);
            }
            return *this;
        }

        void copyFrom(const QueryDataSourceImpl& other);

        QueryPtr containedQuery_ {};
    };


    QueryDataSource::QueryDataSource() noexcept
        : DataSource(ComponentId::QueryDataSource)
		, impl_{ std::make_unique<QueryDataSourceImpl>() }
    {}


    QueryDataSource::QueryDataSource(QueryBuilder queryBuilder, std::optional<Alias> alias)
        : DataSource(ComponentId::QueryDataSource)
		, impl_{ std::make_unique<QueryDataSourceImpl>(std::move(queryBuilder)) }
    {
        DataSource::setAlias(std::move(alias));
    }


    QueryDataSource::QueryDataSource(QueryBuilderPtr queryBuilderPtr, std::optional<Alias> alias)
        : DataSource(ComponentId::QueryDataSource)
		, impl_{ std::make_unique<QueryDataSourceImpl>(queryBuilderPtr) }
    {
        DataSource::setAlias(std::move(alias));
    }


    QueryDataSource::QueryDataSource(String rawSql, std::optional<Alias> alias)
        : DataSource(ComponentId::QueryDataSource)
		, impl_{ std::make_unique<QueryDataSourceImpl>(std::move(rawSql)) }
    {
        DataSource::setAlias(std::move(alias));
    }


	QueryDataSource::~QueryDataSource() = default;


    QueryDataSource::QueryDataSource(const QueryDataSource& other)
        : DataSource(ComponentId::QueryDataSource)
		, impl_{ std::make_unique<QueryDataSourceImpl>(*other.impl_) }
    {
        setAlias(*other.aliasPtr());
    }


    QueryDataSource& QueryDataSource::operator=(const QueryDataSource& other)
    {
        if (this != &other)
        {
			DataSource::operator=(other);
			impl_ = std::make_unique<QueryDataSourceImpl>(*other.impl_);
        }

        return *this;
    }


    QueryDataSource::QueryDataSource(QueryDataSource&& other) noexcept
        : DataSource(ComponentId::QueryDataSource)
		, impl_{ std::move(other.impl_) }
    {
        setAlias(*other.aliasPtr());
    }


    QueryDataSource& QueryDataSource::operator=(QueryDataSource&& other) noexcept
    {
        if (this != &other)
        {
            DataSource::operator=(std::move(other));
            impl_ = std::move(other.impl_);
        }

        return *this;
    }


    DataSourcePtr QueryDataSource::clone() const
    {
        return std::make_shared<QueryDataSource>(*this);
    }


    QueryPtr QueryDataSource::query() const noexcept
    {
        return impl_->containedQuery_;
    }


    String QueryDataSource::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }


    void QueryDataSourceImpl::copyFrom(const QueryDataSourceImpl& other)
    {
        containedQuery_ = other.containedQuery_;
    }
}
