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
        Parameter(String name);
        Parameter(String name, Variant value);
        ~Parameter() override;

        Parameter(const Parameter& other);
        Parameter& operator=(const Parameter& other);
        Parameter(Parameter&&) noexcept ;
        Parameter& operator=(Parameter&&) noexcept ;

        [[nodiscard]] String name() const noexcept;
        void setName(String parameterName) const;
        [[nodiscard]] Variant value() const noexcept;
        void setValue(Variant value) const noexcept;

        [[nodiscard]] bool empty() const noexcept;

        Parameter& operator=(Variant value) noexcept;

    protected:
        String toSql(const IBuilder* builderPtr) const override;

    private:
        std::unique_ptr<ParameterImpl> impl_{};
    };

    export [[nodiscard]] Parameter parameter(String name);
    export [[nodiscard]] Parameter parameter(String name, Variant value);
}
