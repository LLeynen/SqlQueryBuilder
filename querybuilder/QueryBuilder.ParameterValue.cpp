// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import :BuilderTypes;
import :Concepts;
import :ParameterValue;
import :Variant;
import :Impl;

namespace DataAccessLayer::SqlQueryBuilder
{
	QueryBuilder& QueryBuilder::parameterValue(const ParameterValue& paramValue)
	{
		ensureSharedPtr(impl_->parameterMapPtr_);

		auto parameterValuePtr = std::make_shared<ParameterValue>(paramValue);
		auto it = impl_->parameterMapPtr_->find(paramValue.parameterName());
		if (it != impl_->parameterMapPtr_->end())
		{
			it->second = parameterValuePtr;
		}
		else
		{
			auto newParameterValue = std::pair<String, ParameterValuePtr>(paramValue.parameterName(), parameterValuePtr);
			impl_->parameterMapPtr_->insert(newParameterValue);
		}
		return *this;
	}


	QueryBuilder& QueryBuilder::parameterValue(const String& parameterName, const Variant& value)
	{
		ensureSharedPtr(impl_->parameterMapPtr_);

		auto it = impl_->parameterMapPtr_->find(parameterName);
		if (it != impl_->parameterMapPtr_->end())
		{
			if (!value.isNull())
			{
				it->second->setValue(value);
			}
			impl_->parameterChange_ = true;
		}
		else
		{
			auto parameterValuePtr = std::make_shared<ParameterValue>(parameterName, value);
			auto newParameter = std::pair<String, ParameterValuePtr>(parameterName, parameterValuePtr);
			impl_->parameterMapPtr_->insert(newParameter);
			if (!value.isNull())
			{
				impl_->parameterChange_ = true;
			}
		}

		return *this;
	}


	QueryBuilder& QueryBuilder::parameterValues(std::initializer_list<ParameterValue> parameterValueList)
	{
		ensureSharedPtr(impl_->parameterMapPtr_);

		for (const auto& parameterValue : parameterValueList)
		{
			auto parameterValuePtr = std::make_shared<ParameterValue>(parameterValue);
			auto it = impl_->parameterMapPtr_->find(parameterValue.parameterName());
			if (it != impl_->parameterMapPtr_->end())
			{
				it->second = parameterValuePtr;
			}
			else
			{
				auto newParameterValue = std::pair<String, ParameterValuePtr>(parameterValue.parameterName(), parameterValuePtr);
				impl_->parameterMapPtr_->insert(newParameterValue);
			}
		}

		return *this;
	}

	// QueryBuilder::parameterMap
	ParameterMapPtr QueryBuilder::parameterMap() const
	{
		return impl_->parameterMapPtr_;
	}
}
