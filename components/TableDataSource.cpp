// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :TableDataSource;

import std;

import :BuilderTypes;
import :DataSource;

namespace DataAccessLayer::SqlQueryBuilder
{
    class TableDataSourceImpl
    {
    public:
        TableDataSourceImpl() = default;

        TableDataSourceImpl(const String& tableName)
            : containedTable_{ std::make_shared<Table>(tableName) }
		{}

        ~TableDataSourceImpl() = default;

        TableDataSourceImpl(const TableDataSourceImpl& other)
        {
			copyFrom(other);
		}

        TableDataSourceImpl& operator=(const TableDataSourceImpl& other)
        {
            if (this != &other)
            {
                copyFrom(other);
            }
			return *this;
        }

        TableDataSourceImpl(TableDataSourceImpl&& other) noexcept
            : containedTable_{ std::move(other.containedTable_) }
        {}

        TableDataSourceImpl& operator=(TableDataSourceImpl&& other) noexcept
        {
            if (this != &other)
            {
                containedTable_ = std::move(other.containedTable_);
            }
            return *this;
        }

        void copyFrom(const TableDataSourceImpl& other);

        TablePtr containedTable_ {};
    };


    TableDataSource::TableDataSource() noexcept
        : DataSource(ComponentId::TableDataSource)
		, impl_{ std::make_unique<TableDataSourceImpl>() }
    {}


    TableDataSource::TableDataSource(const String& tableName, std::optional<Alias> alias)
        : DataSource(ComponentId::TableDataSource)
		, impl_{ std::make_unique<TableDataSourceImpl>(tableName) }
    {
        setAlias(std::move(alias));
    }


	TableDataSource::~TableDataSource() = default;


    TableDataSource::TableDataSource(const TableDataSource& other)
        : DataSource(ComponentId::TableDataSource)
		, impl_{ std::make_unique<TableDataSourceImpl>(*other.impl_) }
    {
        setAlias(other.alias());
    }


    TableDataSource& TableDataSource::operator=(const TableDataSource& other)
    {
        if (this != &other)
        {
			DataSource::operator=(other);
			impl_ = std::make_unique<TableDataSourceImpl>(*other.impl_);
        }

        return *this;
    }


    TableDataSource::TableDataSource(TableDataSource&& other) noexcept
        : DataSource(ComponentId::TableDataSource)
		, impl_{ std::move(other.impl_) }
    {
        setAlias(other.alias());
    }


    TableDataSource& TableDataSource::operator=(TableDataSource&& other) noexcept
    {
        if (this != &other)
        {
            DataSource::operator=(std::move(other));
            impl_ = std::move(other.impl_);
        }

        return *this;
    }


    TablePtr TableDataSource::table() const noexcept
    {
        return impl_->containedTable_;
    }


    DataSourcePtr TableDataSource::clone() const
    {
        return std::make_shared<TableDataSource>(*this);
    }


    String TableDataSource::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }


    void TableDataSourceImpl::copyFrom(const TableDataSourceImpl& other)
    {
        containedTable_ = other.containedTable_;
    }
}
