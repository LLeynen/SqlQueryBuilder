// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:Filter;

import std;

import :BuilderTypes;
import :Component;

namespace DataAccessLayer::SqlQueryBuilder
{
	class FilterImpl;
	export class Filter : public Component
	{
	public:
		Filter() noexcept;
		Filter(const ConditionBase& condition);
		~Filter() override;

		Filter(const Filter&);
		Filter& operator=(const Filter&);
		Filter(Filter&&) noexcept ;
		Filter& operator=(Filter&&) noexcept ;

		[[nodiscard]] ConditionBasePtr conditionBase() const noexcept;

		void setCondition(const ConditionBase& condition);
		void clear() noexcept;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<FilterImpl> impl_;
	};
}
