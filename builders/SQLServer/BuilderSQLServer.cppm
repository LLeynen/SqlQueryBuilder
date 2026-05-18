// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module BuilderSqlServer;

import QueryBuilder;

namespace DataAccessLayer::SqlQueryBuilder
{
    export class BuilderSqlServer : public BuilderBase
    {
        // Database Engine constant
        static constexpr DatabaseEngine builderEngine{ DatabaseEngine::SQLServer };
    
    public:
        BuilderSqlServer() noexcept;
        ~BuilderSqlServer() override = default;
        static void use();
        void setupEngineParams() override;
    };


    // BuilderSQLServer::use

    void BuilderSqlServer::use()
    {
        registerBuilder<BuilderSqlServer>();
    }
}
