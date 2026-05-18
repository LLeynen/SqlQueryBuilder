// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:QueryDataSource;

import std;

import :BuilderTypes;
import :DataSource;
import :Alias;

namespace DataAccessLayer::SqlQueryBuilder
{
	class QueryDataSourceImpl;

	export class QueryDataSource : public DataSource
	{
	public:
		QueryDataSource() noexcept;
		QueryDataSource(const QueryBuilder& queryBuilder, std::optional<Alias> alias = std::nullopt);
		QueryDataSource(std::shared_ptr<QueryBuilder> queryBuilder, std::optional<Alias> alias = std::nullopt);
		QueryDataSource(const String& rawSql, std::optional<Alias> alias = std::nullopt);
		~QueryDataSource() override;

		QueryDataSource(const QueryDataSource& other);
		QueryDataSource(QueryDataSource&& other) noexcept ;
		QueryDataSource& operator=(const QueryDataSource& other);
		QueryDataSource& operator=(QueryDataSource&& other) noexcept;

		[[nodiscard]] QueryPtr query() const noexcept;

		[[nodiscard]] DataSourcePtr clone() const override;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<QueryDataSourceImpl> impl_;
	};
}
