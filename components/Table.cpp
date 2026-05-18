// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :Table;

import std;

import :BuilderTypes;
//import :DataSource;
//import :IBuilder;

namespace DataAccessLayer::SqlQueryBuilder
{
	class TableImpl
	{
	public:
		TableImpl() = default;
		TableImpl(String  tableName)
			: tableName_{std::move( tableName )}
		{}
		~TableImpl() = default;

		TableImpl(const TableImpl&) = default;
		TableImpl& operator=(const TableImpl&) = default;
		TableImpl(TableImpl&&) = default;
		TableImpl& operator=(TableImpl&&) = default;

		String tableName_;
	};


	Table::Table() noexcept
		: Component(ComponentId::Table)
		, impl_{ std::make_unique<TableImpl>() }
	{}


	Table::Table(const String& tableName)
		: Component(ComponentId::Table)
		, impl_{ std::make_unique<TableImpl>(tableName) }
	{}


	Table::~Table() = default;


	Table::Table(const Table& other)
		: Component(ComponentId::Table)
		, impl_{  std::make_unique<TableImpl>(*other.impl_) }
	{}


	Table& Table::operator=(const Table& other)
	{
		if (this != &other)
		{
			Component::operator=(other);
			impl_ = std::make_unique<TableImpl>(*other.impl_);
		}

		return *this;
	}


	Table::Table(Table&& other) noexcept
		: Component(std::move(other))
		, impl_{ std::move(other.impl_) }
	{}


	Table& Table::operator=(Table&& other) noexcept
	{
		if (this != &other)
		{
			Component::operator=(std::move(other));
			impl_ =  std::move(other.impl_);
		}

		return *this;
	}


	String Table::tableName() const
	{
		return impl_->tableName_;
	}


	void Table::setTableName(const String& tableName) const
	{
		impl_->tableName_ = tableName;
	}


	String Table::toSql(const IBuilder* builderPtr) const
	{
		return Component::sqlImpl(builderPtr, *this);
	}
}
