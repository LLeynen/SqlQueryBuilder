// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:ParameterSelectable;

import std;

import :BuilderTypes;
import :Selectable;
import :Alias;

namespace DataAccessLayer::SqlQueryBuilder
{
    class ParameterSelectableImpl;

    export class ParameterSelectable : public Selectable
    {
    public:
        ParameterSelectable() noexcept;
        ParameterSelectable(const String& parameterName, std::optional<Alias> alias = std::nullopt);
        ~ParameterSelectable() override;

        ParameterSelectable(const ParameterSelectable&);
        ParameterSelectable& operator=(const ParameterSelectable&);
        ParameterSelectable(ParameterSelectable&&) noexcept;
        ParameterSelectable& operator=(ParameterSelectable&&) noexcept;

        [[nodiscard]] ParameterPtr parameterPtr() const;
        void setParameter(const Parameter& parameterReference) const;
        [[nodiscard]] String parameterName() const noexcept;
        void setParameterName(const String& parameterName) const;

        [[nodiscard]] SelectablePtr clone() const override;

    protected:
        String toSql(const IBuilder* builderPtr) const override;

    private:
        std::unique_ptr<ParameterSelectableImpl> impl_{};
    };
}
