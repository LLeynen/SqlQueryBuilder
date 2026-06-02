// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module BuilderMariaDB;

import QueryBuilder;

namespace DataAccessLayer::SqlQueryBuilder
{
    export class BuilderMariaDB : public BuilderBase
    {
        static constexpr auto builderEngine{ DatabaseEngine::MariaDB };

    public:
        BuilderMariaDB() noexcept;
        ~BuilderMariaDB() override = default;

        [[nodiscard]] String buildComponent(const Table& table) const override;
        [[nodiscard]] String buildComponent(const Field& field) const override;

        static void use();

        void setupEngineParams() override;
    };


    void BuilderMariaDB::use()
    {
        registerBuilder<BuilderMariaDB>();
    }
}
