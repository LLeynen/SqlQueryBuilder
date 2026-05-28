// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:ListOfValues;

import std;

import :BuilderTypes;
import :Selectable;
import :Variant;
import :Alias;

namespace DataAccessLayer::SqlQueryBuilder
{
	class ListOfValuesImpl;

	export class ListOfValues : public Selectable
	{
	public:
		ListOfValues();
		ListOfValues(VariantList valueList);
		ListOfValues(std::initializer_list<Variant> valueList);
		~ListOfValues() override;

		ListOfValues(const ListOfValues& other);
		ListOfValues& operator=(const ListOfValues& other);
		ListOfValues(ListOfValues&& other) noexcept;
		ListOfValues& operator=(ListOfValues&& other) noexcept;

		[[nodiscard]] VariantList valueList() const;
		void setValueList(VariantList valueList) const;
		void setValueList(std::initializer_list<Variant> valueList) const;
		void appendValue(Variant value) const;
		void appendValues(VariantList valueList) const;
		void appendValues(std::initializer_list<Variant> valueList) const;
		Variant operator[](size_t index);
		Variant operator[](size_t index) const;

		[[nodiscard]] SelectablePtr clone() const override;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<ListOfValuesImpl> impl_;
	};

	export inline ListOfValues listOfValues(VariantList valueList)
	{
		return { std::move(valueList) };
	}

	export inline ListOfValues listOfValues(std::initializer_list<Variant> valueList)
	{
		return { std::move(valueList) };
	}
}
