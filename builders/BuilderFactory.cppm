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

    // Concept IBuilderDerived
//    template <typename BuilderType>
//    concept IBuilderDerived = std::is_base_of_v<IBuilder, BuilderType>;


     template<typename T>
    concept IsRegisterableBuilder =
        std::derived_from<T, IBuilder> && // Must be an IBuilder
        requires
        {
            { T::use() } -> std::same_as<void>; // Must have the static use() method
        };

    // Builder must have a static use() method
/*
    template<typename T>
    concept IsValidBuilder = requires
    { { T::use() } -> std::same_as<void>; };
*/
    export class BuilderFactory
    {
    public:
        static BuilderFactory& instance();
        template<IsRegisterableBuilder BuilderType> bool registerBuilder();
        IBuilderPtr builder(DatabaseEngine databaseEngine);

        [[nodiscard]] bool hasBuilder(DatabaseEngine databaseEngine) const;
        [[nodiscard]] DatabaseEngineList databaseEngineList() const;
        [[nodiscard]] size_t builderCount() const noexcept;

        [[nodiscard]] DatabaseEngine defaultDatabaseEngine() const;
        void setDefaultDatabaseEngine(DatabaseEngine databaseEngine);
        IBuilderPtr defaultBuilder();

    private:
        BuilderFactory();
        ~BuilderFactory();

        BuilderFactory(const BuilderFactory&) = delete;
        BuilderFactory& operator=(const BuilderFactory&) = delete;
        BuilderFactory(BuilderFactory&&) = delete;
        BuilderFactory& operator=(BuilderFactory&&) = delete;

        static BuilderFactory instance_;
        BuilderFactoryMap builderFactory_{};
        DatabaseEngine defaultDatabaseEngine_{ DatabaseEngine::AnsiSQL };
    };

    // BuilderFactory::registerBuilder
    export template<IsRegisterableBuilder BuilderType>
    bool BuilderFactory::registerBuilder()
    {
/*
        auto builderPtr = std::make_shared<BuilderType>();

        if (hasBuilder(builderPtr->databaseEngine()))
        {
            return true;
        }

        auto result = builderFactory_.insert({ builderPtr->databaseEngine(), builderPtr }).second;
        return result;
*/
        auto builderPtr = std::make_shared<BuilderType>();
        DatabaseEngine databaseEngine = builderPtr->databaseEngine();

        bool result = true;

        if (!hasBuilder(databaseEngine))
        {
            auto result = builderFactory_.insert({ databaseEngine, builderPtr }).second;
        }

        if (builderCount() == 1)
        {
            defaultDatabaseEngine_ = databaseEngine;
        }

        return result;
    }

    // BuilderFactory::registerBuilder helper function
    export template<IsRegisterableBuilder BuilderType>
    bool registerBuilder()
    {
        return BuilderFactory::instance().registerBuilder<BuilderType>();
    }

    // Helper functions
    export IBuilderPtr builder(DatabaseEngine databaseEngine);
    export DatabaseEngine defaultDatabaseEngine();
    export IBuilderPtr defaultBuilder();
}
