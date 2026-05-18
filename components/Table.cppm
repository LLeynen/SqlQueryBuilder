// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:Table;

import std;

import :BuilderTypes;
import :Component;

namespace DataAccessLayer::SqlQueryBuilder
{
	class TableImpl;

	export class Table : public Component
	{
	public:
		Table() noexcept;
		Table(const String& tableName);
		~Table() override;

		Table(const Table&);
		Table& operator=(const Table&);
		Table(Table&&) noexcept ;
		Table& operator=(Table&&) noexcept ;

		[[nodiscard]] String tableName() const;
		void setTableName(const String& tableName) const;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<TableImpl> impl_;
	};
}
