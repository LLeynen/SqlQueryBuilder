// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:FilterBase;

import std;

import :BuilderTypes;
import :Component;

namespace DataAccessLayer::SqlQueryBuilder
{
	class FilterBaseImpl;

	enum class ConditionMode { Comparison, Logical, Unary };

	export class FilterBase : public Component
	{
	public:
		FilterBase();
		FilterBase(ComponentId componentId, ConditionMode conditionMode) noexcept;
		~FilterBase() override;

		FilterBase(const FilterBase& other);
		FilterBase& operator=(const FilterBase& other);
		FilterBase(FilterBase&&) noexcept;
		FilterBase& operator=(FilterBase&&) noexcept;

		[[nodiscard]] ConditionMode mode() const;

		[[nodiscard]] virtual FilterBasePtr clone() const = 0;

	protected:
		String toSql(const IBuilder* builderPtr) const override = 0;

	private:
		std::unique_ptr<FilterBaseImpl> impl_{};
	};
}
