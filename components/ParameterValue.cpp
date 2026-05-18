// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :ParameterValue;

import std;

import :BuilderTypes;
import :Component;
import :IBuilder;
import :Variant;

namespace DataAccessLayer::SqlQueryBuilder
{
	class ParameterValueImpl
	{
	public:
		ParameterValueImpl() = default;
		ParameterValueImpl(String parameterName, Variant value)
			: parameterName_{std::move( parameterName )}
			, value_{std::move( value )}
		{}
		ParameterValueImpl(String parameterName)
			: parameterName_{std::move( parameterName )}
		{}
		~ParameterValueImpl() = default;

		ParameterValueImpl(const ParameterValueImpl&) = default;
		ParameterValueImpl& operator=(const ParameterValueImpl&) = default;
		ParameterValueImpl(ParameterValueImpl&&) = default;
		ParameterValueImpl& operator=(ParameterValueImpl&&) = default;
	
		String parameterName_{};
		Variant value_{};
	};


	ParameterValue::ParameterValue()
		: Component(ComponentId::ParameterValue)
		, impl_{ std::make_unique<ParameterValueImpl>() }
	{}


	ParameterValue::ParameterValue(const String& parameterName, const Variant& value)
		: Component(ComponentId::ParameterValue)
		, impl_{ std::make_unique<ParameterValueImpl>(parameterName, value) }
	{}


	ParameterValue::ParameterValue(const String& parameterName)
		: Component(ComponentId::ParameterValue)
		, impl_{ std::make_unique<ParameterValueImpl>(parameterName) }
	{}


	ParameterValue::~ParameterValue() = default;


	ParameterValue::ParameterValue(const ParameterValue& other)
		: Component(other)
		, impl_{ std::make_unique<ParameterValueImpl>(*other.impl_) }
	{}


	ParameterValue& ParameterValue::operator=(const ParameterValue& other)
	{
		if (this != &other)
		{
			Component::operator=(other);
			impl_ = std::make_unique<ParameterValueImpl>(*other.impl_);
		}

		return *this;
	}


	ParameterValue::ParameterValue(ParameterValue&& other) noexcept
		: Component(std::move(other))
		, impl_{ std::move(other.impl_) }
	{}


	ParameterValue& ParameterValue::operator=(ParameterValue&& other) noexcept
	{
		if (this != &other)
		{
			Component::operator=(std::move(other));
			impl_ = std::move(other.impl_);
		}
		return *this;
	}


	const String& ParameterValue::parameterName() const noexcept
	{
		return impl_->parameterName_;
	}


	void ParameterValue::setParameterName(const String& parameterName) const
	{
		impl_->parameterName_ = parameterName;
	}


	const Variant& ParameterValue::value() const noexcept
	{
		return impl_->value_;
	}


	void ParameterValue::setValue(const Variant& value) const
	{
		impl_->value_ = value;
	}


	bool ParameterValue::empty() const noexcept
	{
		return impl_->parameterName_.empty();
	}


	String ParameterValue::toSql(const IBuilder* builderPtr) const
	{
		return Component::sqlImpl(builderPtr, *this);
	}
}
