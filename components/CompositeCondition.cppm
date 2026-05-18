// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:CompositeCondition;

import std;

//import :BuilderTypes;
import :ConditionBase;

namespace DataAccessLayer::SqlQueryBuilder
{
	class CompositeConditionImpl;

	export class CompositeCondition : public ConditionBase
	{
	public:
		CompositeCondition() noexcept;
		CompositeCondition(const ConditionBase& left, LogicOperator logicOperator, const ConditionBase& right);
		CompositeCondition(LogicOperator logicOperator, ConditionBaseList conditionBaseList) noexcept;
		CompositeCondition(LogicOperator logicOperator, std::initializer_list<ConditionBasePtr> conditionBaseList) noexcept;
		~CompositeCondition() override;

		CompositeCondition(const CompositeCondition& other);
		CompositeCondition& operator=(const CompositeCondition& other);
		CompositeCondition(CompositeCondition&&) noexcept ;
		CompositeCondition& operator=(CompositeCondition&&) noexcept ;

		[[nodiscard]] LogicOperator logicOperator() const noexcept;
		void setLogicOperator(LogicOperator logicOperator) const noexcept;
		[[nodiscard]] const ConditionBaseList conditionBaseList() const;
		void setConditionBaseList(ConditionBaseList conditionsBaseList);
		void addCondition(const ConditionBase& sqlConditionBase);

		[[nodiscard]] ConditionBasePtr clone() const override;
		CompositeCondition operator&(const ConditionBase& other) const;
		CompositeCondition operator|(const ConditionBase& other) const;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<CompositeConditionImpl> impl_;
		void copyFrom(const CompositeCondition& other);
	};
}
