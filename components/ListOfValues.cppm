// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:ListOfValues;

import std;

import :BuilderTypes;
import :Component;
import :Variant;

namespace DataAccessLayer::SqlQueryBuilder
{
	class ListOfValuesImpl;

	export class ListOfValues : public Component
	{
	public:
		ListOfValues();
		ListOfValues(const VariantList& valueList);
		ListOfValues(std::initializer_list<Variant> valueList);
		~ListOfValues() override;

		ListOfValues(const ListOfValues& other);
		ListOfValues& operator=(const ListOfValues& other);
		ListOfValues(ListOfValues&& other) noexcept;
		ListOfValues& operator=(ListOfValues&& other) noexcept;

		[[nodiscard]] VariantList valueList() const;
		void setValueList(const VariantList& valueList);
		void setValueList(std::initializer_list<Variant> valueList);
		void appendValue(const Variant& value);
		void appendValues(const VariantList& valueList);
		void appendValues(std::initializer_list<Variant> valueList);
		Variant& operator[](size_t index);
		const Variant& operator[](size_t index) const;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<ListOfValuesImpl> impl_;
	};
}
