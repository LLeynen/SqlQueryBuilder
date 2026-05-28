// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:TableDataSource;

import std;

import :BuilderTypes;
import :DataSource;
import :Alias;

namespace DataAccessLayer::SqlQueryBuilder
{
	class TableDataSourceImpl;

	export class TableDataSource : public DataSource
	{
	public:
		TableDataSource() noexcept;
		TableDataSource(String name, std::optional<Alias> alias = std::nullopt);
		~TableDataSource() override;

		TableDataSource(const TableDataSource& other);
		TableDataSource(TableDataSource&& other) noexcept ;
		TableDataSource& operator=(const TableDataSource& other);
		TableDataSource& operator=(TableDataSource&& other) noexcept;

		[[nodiscard]] TablePtr table() const noexcept;

		[[nodiscard]] DataSourcePtr clone() const override;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<TableDataSourceImpl> impl_;
	};
}
