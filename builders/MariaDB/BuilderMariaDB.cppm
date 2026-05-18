// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module BuilderMariaDB;

//import QueryBuilder:BuilderFactory; // import the factory so we can call registerBuilder
import QueryBuilder; // keep existing import for public QueryBuilder API

namespace DataAccessLayer::SqlQueryBuilder
{
    export class BuilderMariaDB : public BuilderBase
    {
        // Database engine constant
        static constexpr DatabaseEngine builderEngine{ DatabaseEngine::MariaDB };

    public:
        BuilderMariaDB() noexcept;
        ~BuilderMariaDB() override = default;

        // Override buildComponent methods only if MariaDB needs different behavior
        // String buildComponent(const SqlTable& sqlTable) const override;
        // String buildComponent(const SqlField& sqlField) const override;
        // String buildComponent(const SqlSelectable& sqlSelectable) const override;

        // MariaDB-specific methods
        [[nodiscard]] String buildLimitClause(int limit, int offset = 0) const;
        [[nodiscard]] String buildAutoIncrement() const;

        static void use();

        void setupEngineParams() override;
    };

    // Auto-register the MariaDB builder when this module is imported.
    // Export the inline variable so the module import forces the symbol to be linked
    // and its initializer to run. The lambda performs the registration once.
//    export inline bool builderMariaDB_registered = []() -> bool 
//    {
//        return registerBuilder<BuilderMariaDB>();
//    }();

//    export void __declspec(dllexport) ensureMariaDBRegistered()
//    {
//        (void)builderMariaDB_registered;
//    }


    // BuilderMariaDB::use

    void BuilderMariaDB::use()
    {
        registerBuilder<BuilderMariaDB>();
    }
}
