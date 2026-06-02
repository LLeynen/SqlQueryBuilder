// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module BuilderPostgreSQL;

import QueryBuilder;

namespace DataAccessLayer::SqlQueryBuilder
{
    class BuilderPostgreSQL : public BuilderBase
    {
        static constexpr auto builderEngine{ DatabaseEngine::PostgreSQL };

    public:
        BuilderPostgreSQL() noexcept;
        ~BuilderPostgreSQL() override = default;

        static void use();

        void setupEngineParams() override;
    };


    void BuilderPostgreSQL::use()
    {
        registerBuilder<BuilderPostgreSQL>();
    }
}
