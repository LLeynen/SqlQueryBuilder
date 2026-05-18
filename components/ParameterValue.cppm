// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:ParameterValue;

import std;

import :BuilderTypes;
import :Component;

namespace DataAccessLayer::SqlQueryBuilder
{
	class ParameterValueImpl;

	export class ParameterValue : public Component
	{
	public:
		ParameterValue();
		ParameterValue(const String& parameterName, const Variant& varParameterValue);
		ParameterValue(const String& parameterName);
		~ParameterValue() override;

		ParameterValue(const ParameterValue&);
		ParameterValue& operator=(const ParameterValue&);
		ParameterValue(ParameterValue&&) noexcept ;
		ParameterValue& operator=(ParameterValue&&) noexcept ;

		[[nodiscard]] const String& parameterName() const noexcept;
		void setParameterName(const String& parameterName) const;
		[[nodiscard]] const Variant& value() const noexcept;
		void setValue(const Variant& value) const;

		[[nodiscard]] bool empty() const noexcept;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<ParameterValueImpl> impl_;
	};
}
