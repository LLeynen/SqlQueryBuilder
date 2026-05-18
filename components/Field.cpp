// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :Field;

import std;

import :BuilderTypes;
import :Selectable;
import :IBuilder;
import :Variant;

namespace DataAccessLayer::SqlQueryBuilder
{
    class FieldImpl
    {
    public:
        FieldImpl() = default;
        FieldImpl(String  tableName, String  columnName)
            : tableName_{std::move( tableName )}
            , columnName_{std::move( columnName )}
        {}

        FieldImpl(const FieldImpl& other) = default;
        FieldImpl& operator=(const FieldImpl& other) = default;
        FieldImpl(FieldImpl&& other) = default;
        FieldImpl& operator=(FieldImpl&& other) = default;

        String tableName_{};
        String columnName_{};
        Variant value_{};
    };


    Field::Field() noexcept
        : Selectable(ComponentId::Field)
        , impl_{ std::make_unique<FieldImpl>() }
    {}


    Field::Field(String columnName, std::optional<Alias> alias)
        : Selectable(ComponentId::Field)
        , impl_{ std::make_unique<FieldImpl>() }
    {
        impl_->columnName_ = std::move(columnName);

        this->setAlias(std::move(alias));
    }


    Field::Field(String tableName, String columnName, std::optional<Alias> alias)
        : Selectable(ComponentId::Field)
        , impl_{ std::make_unique<FieldImpl>() }
    {
        impl_->tableName_ = std::move(tableName);
        impl_->columnName_ = std::move(columnName);

        this->setAlias(std::move(alias));
    }


    Field::~Field() = default;


    Field::Field(const Field& other)
        : Selectable(other)
        , impl_{ std::make_unique<FieldImpl>(*other.impl_) }
    {}


    Field& Field::operator=(const Field& other)
    {
        if (this != &other)
        {
            Selectable::operator=(other);
            impl_ = std::make_unique<FieldImpl>(*other.impl_);
        }

        return *this;
    }


    Field::Field(Field&& other) noexcept
        : Selectable(std::move(other))
        , impl_{ std::move(other.impl_) }
    {}


    Field& Field::operator=(Field&& other) noexcept
    {
        if (this != &other)
        {
            Selectable::operator=(std::move(other));
            impl_ = std::move(other.impl_);
        }

        return *this;
    }


    SelectablePtr Field::clone() const
    {
        return std::make_shared<Field>(*this);
    }


    const String& Field::tableName() const noexcept
    {
        return impl_->tableName_;
    }


    void Field::setTableName(const String& tableName) const
    {
        impl_->tableName_ = tableName;
    }


    const String& Field::columnName() const noexcept
    {
        return impl_->columnName_;
    }


    void Field::setColumnName(const String& columnName) const
    {
        impl_->columnName_ = columnName;
    }


    const Variant& Field::value() const noexcept
    {
        return impl_->value_;
    }


    void Field::setValue(const Variant& value) const
    {
        impl_->value_ = value;
    }


    bool Field::isNull() const noexcept
    {
        return impl_->value_.isNull();
    }


    String Field::toSql(const IBuilder* builderPtr) const
    {
        return Component::sqlImpl(builderPtr, *this);
    }
}
