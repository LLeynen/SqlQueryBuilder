// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:BuilderFactory;

import std;

import :BuilderTypes;
import :IBuilder;

namespace DataAccessLayer::SqlQueryBuilder
{
    export using DatabaseEngineList = std::vector<DatabaseEngine>;

    template<typename T>
    concept IsRegisterableBuilder =
        std::derived_from<T, IBuilder> && // Must be an IBuilder
        requires
        {
            { T::use() } -> std::same_as<void>; // Must have the static use() method
        };

    export class BuilderFactory
    {
    public:
        BuilderFactory(const BuilderFactory&) = delete;
        BuilderFactory(BuilderFactory&&) = delete;

        static BuilderFactory& instance();
        template<IsRegisterableBuilder BuilderType> bool registerBuilder();
        IBuilderPtr builder(DatabaseEngine databaseEngine);

        BuilderFactory& operator=(const BuilderFactory&) = delete;
        BuilderFactory& operator=(BuilderFactory&&) = delete;

        [[nodiscard]] bool hasBuilder(DatabaseEngine databaseEngine) const;
        [[nodiscard]] DatabaseEngineList databaseEngineList() const;
        [[nodiscard]] size_t builderCount() const noexcept;

        [[nodiscard]] DatabaseEngine defaultDatabaseEngine() const;
        void setDefaultDatabaseEngine(DatabaseEngine databaseEngine);
        IBuilderPtr defaultBuilder();

    private:
        BuilderFactory();
        ~BuilderFactory();

        static BuilderFactory instance_;
        BuilderFactoryMap builderFactory_{};
        DatabaseEngine defaultDatabaseEngine_{ DatabaseEngine::AnsiSQL };
    };


    export template<IsRegisterableBuilder BuilderType>
    bool BuilderFactory::registerBuilder()
    {
        auto builderPtr = std::make_shared<BuilderType>();
        DatabaseEngine databaseEngine = builderPtr->databaseEngine();

        bool result = true;

        if (!hasBuilder(databaseEngine))
        {
            result = builderFactory_.insert({ databaseEngine, builderPtr }).second;
        }

        if (builderCount() == 1)
        {
            defaultDatabaseEngine_ = databaseEngine;
        }

        return result;
    }


    export template<IsRegisterableBuilder BuilderType>
    bool registerBuilder()
    {
        return BuilderFactory::instance().registerBuilder<BuilderType>();
    }


    export IBuilderPtr builder(DatabaseEngine databaseEngine);
    export DatabaseEngine defaultDatabaseEngine();
    export IBuilderPtr defaultBuilder();
}
