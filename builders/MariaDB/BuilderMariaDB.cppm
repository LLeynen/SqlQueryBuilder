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

        // Override buildComponent methods only if MariaDB needs different behavior
        [[nodiscard]] String buildComponent(const Table& table) const override;
        [[nodiscard]] String buildComponent(const Field& field) const override;

        // MariaDB-specific methods
        [[nodiscard]] String buildLimitClause(int limit, int offset = 0) const;
        [[nodiscard]] String buildAutoIncrement() const;

        static void use();

    protected:
        void setupEngineParams() override;
    };


    void BuilderMariaDB::use()
    {
        registerBuilder<BuilderMariaDB>();
    }
}
