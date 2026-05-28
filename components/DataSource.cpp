// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :DataSource;

import std;

import :BuilderTypes;
import :Component;
import :Alias;

namespace DataAccessLayer::SqlQueryBuilder
{
    class DataSourceImpl
    {
    public:
        DataSourceImpl() = default;
        ~DataSourceImpl() = default;

        DataSourceImpl(const DataSourceImpl& other) = default;
        DataSourceImpl& operator=(const DataSourceImpl& other) = default;
        DataSourceImpl(DataSourceImpl&& other) noexcept = default;
        DataSourceImpl& operator=(DataSourceImpl&& other) noexcept = default;

        AliasPtr alias_{};
    };

    DataSource::DataSource() noexcept
        : Component(ComponentId::DataSource)
        , impl_{ std::make_unique<DataSourceImpl>() }
    {}


    DataSource::DataSource(const ComponentId componentId)
        : Component(componentId)
        , impl_{ std::make_unique<DataSourceImpl>() }
    {}


    DataSource::~DataSource() = default;


    DataSource::DataSource(const DataSource& other)
        : Component(other)
        , impl_{ std::make_unique<DataSourceImpl>(*other.impl_) }
    {}


    DataSource& DataSource::operator=(const DataSource& other)
    {
        if (this != &other)
        {
            Component::operator=(other);
            impl_ = std::make_unique<DataSourceImpl>(*other.impl_);
        }

        return *this;
    }


    DataSource::DataSource(DataSource&&) noexcept = default;


    DataSource& DataSource::operator=(DataSource&&) noexcept = default;


    AliasPtr DataSource::aliasPtr() const
    {
        return impl_->alias_;
    }


    String DataSource::aliasName() const
    {
        return  impl_->alias_->value();
    }


    void DataSource::setAlias(std::optional<Alias> alias) const
    {
        if (alias.has_value())
        {
            impl_->alias_ = std::make_shared<Alias>(std::move(alias.value()));
            impl_->alias_->setAliasType(AliasType::Table);
        }    }



    bool DataSource::hasAlias() const noexcept
    {
        return (impl_->alias_ != nullptr);
    }
}
