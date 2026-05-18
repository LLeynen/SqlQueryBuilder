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
//        std::optional<String> alias_{ std::nullopt };
    };

	// DataSource::DataSource
    DataSource::DataSource() noexcept
        : Component(ComponentId::DataSource)
        , impl_{ std::make_unique<DataSourceImpl>() }
    {}

	// DataSource::DataSource(ComponentId, const std::optional<String>&)
    DataSource::DataSource(ComponentId componentId)
        : Component(componentId)
        , impl_{ std::make_unique<DataSourceImpl>() }
    {}

	// DataSource::~DataSource
    DataSource::~DataSource() = default;

	// DataSource::DataSource(const DataSource&)
    DataSource::DataSource(const DataSource& other)
        : Component(other)
        , impl_{ std::make_unique<DataSourceImpl>(*other.impl_) }
    {}

	// DataSource::operator=(const DataSource&)
    DataSource& DataSource::operator=(const DataSource& other)
    {
        if (this != &other)
        {
            Component::operator=(other);
            impl_ = std::make_unique<DataSourceImpl>(*other.impl_);
        }

        return *this;
    }


	// DataSource::DataSource(DataSource&&)
    DataSource::DataSource(DataSource&&) noexcept = default;


	// DataSource::operator=(DataSource&&)
    DataSource& DataSource::operator=(DataSource&&) noexcept = default;


    AliasPtr DataSource::aliasPtr() const
    {
        return impl_->alias_;
    }

    const String& DataSource::alias() const
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
