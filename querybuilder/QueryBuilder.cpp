// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

//import QueryBuilder;

import std;

import :BuilderTypes;
import :BuilderFactory;
import :Variant;
import :Impl;

namespace DataAccessLayer::SqlQueryBuilder
{
	// QueryBuilder::QueryBuilder(QueryType, DatabaseEngine)
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

	// QueryBuilder::~QueryBuilder
	QueryBuilder::~QueryBuilder() = default;

	// QueryBuilder::QueryBuilder(QueryBuilder&)
	QueryBuilder::QueryBuilder(const QueryBuilder& other)
		: impl_{ std::make_unique<QueryBuilderImpl>(*other.impl_) }
	{}

	// QueryBuilder::operator=(QueryBuilder&)
	QueryBuilder& QueryBuilder::operator=(const QueryBuilder& other)
	{
		if (this != &other)
		{
			impl_ = std::make_unique<QueryBuilderImpl>(*other.impl_);
		}

		return *this;
	}

	// QueryBuilder::QueryBuilder(QueryBuilder&&)
	QueryBuilder::QueryBuilder(QueryBuilder&& other) noexcept
		: impl_{ std::move(other.impl_) }
	{}

	// QueryBuilder::operator=(QueryBuilder&&)
	QueryBuilder& QueryBuilder::operator=(QueryBuilder&& other) noexcept
	{
		if (this != &other)
		{
			impl_ = std::move(other.impl_);
		}

		return *this;
	}

	// QueryBuilder::setDefaultDatabaseEngine
	//void setDefaultDatabaseEngine(const DatabaseEngine databaseEngine)
	//{
	//	defaultDatabaseEngine = databaseEngine;
	//}

	// QueryBuilder::queryType
	QueryType QueryBuilder::queryType() const
	{
		return impl_->queryType_;
	}

	// QueryBuilder::setQueryType
	void QueryBuilder::setQueryType(const QueryType queryType)
	{
		impl_->queryType_ = queryType;
	}

	// QueryBuilder::databaseEngine
	const DatabaseEngine QueryBuilder::databaseEngine() const
	{
		return impl_->databaseEngine_;
	}

	// QueryBuilder::setDatabaseEngine
	void QueryBuilder::setDatabaseEngine(const DatabaseEngine databaseEngine)
	{
		impl_->databaseEngine_ = databaseEngine;
		impl_->builderPtr_ = BuilderFactory::instance().builder(databaseEngine);
	}

	void QueryBuilder::setParameterMap(const ParameterMapPtr& parameterMapPtr)
	{
		impl_->parameterMapPtr_ = parameterMapPtr;
	}
}
