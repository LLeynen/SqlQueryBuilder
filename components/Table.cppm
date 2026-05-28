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
		Table(String name);
		~Table() override;

		Table(const Table&);
		Table& operator=(const Table&);
		Table(Table&&) noexcept ;
		Table& operator=(Table&&) noexcept ;

		[[nodiscard]] String name() const;
		void setName(String name) const;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<TableImpl> impl_;
	};

	export inline Table table(String name)
	{
		return { name };
	}
}
