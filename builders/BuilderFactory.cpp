// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderFactory;

import std;

import :BuilderTypes;

namespace DataAccessLayer::SqlQueryBuilder
{
    BuilderFactory::BuilderFactory() = default;
    
    BuilderFactory::~BuilderFactory() = default;

    // BuilderFactory::instance
    BuilderFactory BuilderFactory::instance_;

    BuilderFactory& BuilderFactory::instance()
    {
        return instance_;
    }

    // BuilderFactory::builder
    IBuilderPtr BuilderFactory::builder(DatabaseEngine databaseEngine)
    {
        auto it = builderFactory_.find(databaseEngine);

        if (it != builderFactory_.end())
        {
            return it->second;
        }
        else
        {
            throw std::runtime_error("BuilderFactory::builder() - No builder registered");
            return nullptr;
        }
    }

    // BuilderFactory::hasBuilder
    bool BuilderFactory::hasBuilder(const DatabaseEngine databaseEngine) const
    {
        return builderFactory_.find(databaseEngine) != builderFactory_.end();
    }

    // BuilderFactory::databaseEngineList
    DatabaseEngineList BuilderFactory::databaseEngineList() const
    {
        DatabaseEngineList engines;

        engines.reserve(builderFactory_.size());
        for (const auto& [databaseEngine, _] : builderFactory_)
        {
            engines.push_back(databaseEngine);
        }

        return engines;
    }

    // BuilderFactory::builderCount
    size_t BuilderFactory::builderCount() const noexcept
    {
        return builderFactory_.size();
    }

    // BuilderFactory::defaultDatabaseEngine
    DatabaseEngine BuilderFactory::defaultDatabaseEngine() const
    {
        return defaultDatabaseEngine_;
    }

    // BuilderFactory::setDefaultDatabaseEngine
    void BuilderFactory::setDefaultDatabaseEngine(DatabaseEngine databaseEngine)
    {
        defaultDatabaseEngine_ = databaseEngine;
    }

    // BuilderFactory::defaultBuilder()
    IBuilderPtr BuilderFactory::defaultBuilder()
    {
        return builder(defaultDatabaseEngine_);
    }

    // builder helper function
    IBuilderPtr builder(DatabaseEngine databaseEngine)
    {
        return BuilderFactory::instance().builder(databaseEngine);
    }

    // defaultDatabaseEngine helper function
    DatabaseEngine defaultDatabaseEngine()
    {
        return BuilderFactory::instance().defaultDatabaseEngine();
    }

    // defaultBuilder helper function
    IBuilderPtr defaultBuilder()
    {
        return BuilderFactory::instance().defaultBuilder();
    }
}
