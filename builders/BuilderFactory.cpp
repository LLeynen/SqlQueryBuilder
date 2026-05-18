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

    BuilderFactory BuilderFactory::instance_;

    BuilderFactory& BuilderFactory::instance()
    {
        return instance_;
    }


    IBuilderPtr BuilderFactory::builder(const DatabaseEngine databaseEngine)
    {
        if (const auto it = builderFactory_.find(databaseEngine); it != builderFactory_.end())
        {
            return it->second;
        }
        else
        {
            throw std::runtime_error("BuilderFactory::builder() - No builder registered");
            return nullptr;
        }
    }


    bool BuilderFactory::hasBuilder(const DatabaseEngine databaseEngine) const
    {
        return builderFactory_.find(databaseEngine) != builderFactory_.end();
    }


    DatabaseEngineList BuilderFactory::databaseEngineList() const
    {
        DatabaseEngineList engines;

        engines.reserve(builderFactory_.size());
        for (const auto& databaseEngine : builderFactory_ | std::views::keys)
        {
            engines.push_back(databaseEngine);
        }

        return engines;
    }


    size_t BuilderFactory::builderCount() const noexcept
    {
        return builderFactory_.size();
    }


    DatabaseEngine BuilderFactory::defaultDatabaseEngine() const
    {
        return defaultDatabaseEngine_;
    }


    void BuilderFactory::setDefaultDatabaseEngine(DatabaseEngine databaseEngine)
    {
        defaultDatabaseEngine_ = databaseEngine;
    }


    IBuilderPtr BuilderFactory::defaultBuilder()
    {
        return builder(defaultDatabaseEngine_);
    }


    IBuilderPtr builder(DatabaseEngine databaseEngine)
    {
        return BuilderFactory::instance().builder(databaseEngine);
    }


    DatabaseEngine defaultDatabaseEngine()
    {
        return BuilderFactory::instance().defaultDatabaseEngine();
    }


    IBuilderPtr defaultBuilder()
    {
        return BuilderFactory::instance().defaultBuilder();
    }
}
