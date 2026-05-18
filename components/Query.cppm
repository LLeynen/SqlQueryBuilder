// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:Query;

import std;

import :BuilderTypes;
//import :DataSource;
import :Component;

namespace DataAccessLayer::SqlQueryBuilder
{
	class QueryImpl;

    // QuerySource type
    export using QuerySourceType = std::variant
        <
        QueryBuilderPtr,
        String
        >;

    export class Query : public Component
    {
    public:
        Query() noexcept;
        Query(const QueryBuilder& queryBuilder);
        Query(std::shared_ptr<QueryBuilder> queryBuilder);
        Query(const String& rawSql);
        ~Query() override;

        Query(const Query& other);
        Query(Query&& other) noexcept ;
        Query& operator=(const Query& other);
        Query& operator=(Query&& other) noexcept;

        [[nodiscard]] QuerySourceType querySource() const;
        void setQuerySource(const QuerySourceType& querySource);

    protected:
        String toSql(const IBuilder* builderPtr) const override;

    private:
		std::unique_ptr<QueryImpl> impl_{};
    };
}
