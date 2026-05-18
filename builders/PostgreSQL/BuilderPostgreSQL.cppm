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
        // Override only the database-specific methods
        // String buildTableName(const SqlTable& sqlTable) const override;
        // String buildColumnName(const String& columnName) const override;
        // String buildParameter(const String& parameterName) const override;

        // PostgreSQL-specific methods
        // String buildLimitClause(int limit, int offset = 0) const;
        // String buildSerial() const;
        // String buildArrayType(const String& elementType) const;
    };


    void BuilderPostgreSQL::use()
    {
        registerBuilder<BuilderPostgreSQL>();
    }
}
