// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:Condition;

import std;

//import :BuilderTypes;
import :ConditionBase;

namespace DataAccessLayer::SqlQueryBuilder
{
	class ConditionImpl;

	// ConditionVariant
	export using ConditionVariant = std::variant
		<
		std::nullptr_t,
		Variant,
		Parameter,
		Field,
		ListOfValues,
		Query,
		String,
		const char*
		>;

	export class Condition : public ConditionBase
	{
	public:
		Condition() noexcept;
		Condition(const Field& field, Comparison comparison, const ConditionVariant& conditionValue);
		Condition(const Field& field, const ConditionVariant& conditionValue);
		~Condition() override;

		Condition(const Condition& other);
		Condition& operator=(const Condition& other);
		Condition(Condition&& other) noexcept;
		Condition& operator=(Condition&& other) noexcept;

		[[nodiscard]] const Field& field() const noexcept;
		void setField(const Field& field);
		[[nodiscard]] const Comparison& comparison() const noexcept;
		void setComparison(Comparison comparison) noexcept;
		[[nodiscard]] const ConditionVariant& conditionValue() const noexcept;
		void setConditionValue(const ConditionVariant& conditionValue);

		[[nodiscard]] ConditionBasePtr clone() const override;
		CompositeCondition operator&(const ConditionBase& other) const;
		CompositeCondition operator|(const ConditionBase& other) const;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<ConditionImpl> impl_;
	};
}
