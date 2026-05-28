// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:FilterSelectable;

import std;

import :BuilderTypes;
import :Selectable;
import :FilterBase;
import :Alias;

namespace DataAccessLayer::SqlQueryBuilder
{
	class FilterSelectableImpl;

	export class FilterSelectable : public Selectable
	{
	public:
		FilterSelectable() noexcept;

		FilterSelectable(const FilterBase& filter, std::optional<Alias> alias = std::nullopt);

		~FilterSelectable() override;

		FilterSelectable(const FilterSelectable&);
		FilterSelectable& operator=(const FilterSelectable&);
		FilterSelectable(FilterSelectable&&) noexcept;
		FilterSelectable& operator=(FilterSelectable&&) noexcept;

		[[nodiscard]] FilterBasePtr filter() const;
		void setFilter(const FilterBase& filter) const;

		[[nodiscard]] SelectablePtr clone() const override;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<FilterSelectableImpl> impl_;
	};
}
