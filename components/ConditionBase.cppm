// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:ConditionBase;

import std;

import :BuilderTypes;
import :Component;

namespace DataAccessLayer::SqlQueryBuilder
{
	class ConditionBaseImpl;

	export class ConditionBase : public Component
	{
	public:
		using ConditionBasePtr = std::shared_ptr<ConditionBase>;

		ConditionBase() noexcept;
		ConditionBase(ComponentId componentId) noexcept;
		~ConditionBase() override;

		ConditionBase(const ConditionBase&);
		ConditionBase& operator=(const ConditionBase&);
		ConditionBase(ConditionBase&&) noexcept ;
		ConditionBase& operator=(ConditionBase&&) noexcept ;

		[[nodiscard]] virtual ConditionBasePtr clone() const = 0;

	protected:
		String toSql(const IBuilder* builderPtr) const override = 0;

	private:
		std::unique_ptr<ConditionBaseImpl> impl_;
	};
}
