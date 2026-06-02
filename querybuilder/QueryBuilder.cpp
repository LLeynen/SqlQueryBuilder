// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import :BuilderTypes;
import :BuilderFactory;
import :Variant;
import :Impl;

namespace DataAccessLayer::SqlQueryBuilder
{
	QueryBuilder::QueryBuilder(const QueryType queryType, const DatabaseEngine databaseEngine)
		: impl_{ std::make_unique<QueryBuilderImpl>() }
	{
		impl_->queryType_ = queryType;
		impl_->databaseEngine_ = databaseEngine;
		impl_->builderPtr_ = BuilderFactory::instance().builder(databaseEngine);

		if (impl_->builderPtr_ == nullptr)
		{
			throw std::runtime_error("No Sql Builder registered for engine");
		}
	}


	QueryBuilder::~QueryBuilder() = default;


	QueryBuilder::QueryBuilder(const QueryBuilder& other)
		: impl_{ std::make_unique<QueryBuilderImpl>(*other.impl_) }
	{}


	QueryBuilder& QueryBuilder::operator=(const QueryBuilder& other)
	{
		if (this != &other)
		{
			impl_ = std::make_unique<QueryBuilderImpl>(*other.impl_);
		}

		return *this;
	}


	QueryBuilder::QueryBuilder(QueryBuilder&& other) noexcept
		: impl_{ std::move(other.impl_) }
	{}


	QueryBuilder& QueryBuilder::operator=(QueryBuilder&& other) noexcept
	{
		if (this != &other)
		{
			impl_ = std::move(other.impl_);
		}

		return *this;
	}


	QueryType QueryBuilder::queryType() const
	{
		return impl_->queryType_;
	}


	void QueryBuilder::setQueryType(const QueryType queryType) const
	{
		impl_->queryType_ = queryType;
	}


	DatabaseEngine QueryBuilder::databaseEngine() const
	{
		return impl_->databaseEngine_;
	}


	void QueryBuilder::setDatabaseEngine(const DatabaseEngine databaseEngine) const
	{
		impl_->databaseEngine_ = databaseEngine;
		impl_->builderPtr_ = BuilderFactory::instance().builder(databaseEngine);
	}
}
