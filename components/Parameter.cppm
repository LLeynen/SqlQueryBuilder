// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:Parameter;

import std;

import :BuilderTypes;
import :Component;

namespace DataAccessLayer::SqlQueryBuilder
{
    class ParameterImpl;

    export class Parameter : public Component
    {
    public:
        Parameter();
        explicit Parameter(const String& parameterName);
        Parameter(const String& parameterName, const ParameterMapPtr& parameterMapPtr);
        ~Parameter() override;

        Parameter(const Parameter& other);
        Parameter& operator=(const Parameter& other);
        Parameter(Parameter&&) noexcept ;
        Parameter& operator=(Parameter&&) noexcept ;

        [[nodiscard]] const String& parameterName() const noexcept;
        void setParameterName(const String& parameterName) const;
        [[nodiscard]] ParameterMapPtr parameterMap() const noexcept;
        void setParameterMap(const ParameterMapPtr& parameterMapPtr) const noexcept;

        [[nodiscard]] bool empty() const noexcept;

    protected:
        String toSql(const IBuilder* builderPtr) const override;

    private:
        std::unique_ptr<ParameterImpl> impl_;
    };

    export Parameter parameter(const String& parameterName);

    export Parameter parameter(const String& parameterName, const ParameterMapPtr& parameterMapPtr);
}
