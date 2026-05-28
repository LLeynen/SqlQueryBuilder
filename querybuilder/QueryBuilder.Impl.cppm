// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

export module QueryBuilder:Impl;

import std;

export import :BuilderTypes;
import :Variant;

namespace DataAccessLayer::SqlQueryBuilder
{
	class QueryBuilderImpl
	{
	public:
		QueryBuilderImpl() = default;
		~QueryBuilderImpl() = default;

		QueryBuilderImpl(const QueryBuilderImpl&) = default;
		QueryBuilderImpl& operator=(const QueryBuilderImpl&) = default;
		QueryBuilderImpl(QueryBuilderImpl&&) = default;
		QueryBuilderImpl& operator=(QueryBuilderImpl&&) = default;

		QueryType queryType_{ QueryType::SelectQuery };
		DatabaseEngine databaseEngine_{DatabaseEngine::AnsiSQL};
		IBuilderPtr builderPtr_{};

		Variant distinct_{ nullptr };
		TopClausePtr topClausePtr_{};
		FilterBasePtr whereFilterPtr_{};
		DataSourcePtr dataSourcePtr_{};
		SelectableListPtr selectableListPtr_{};
		JoinClauseListPtr joinClauseListPtr_{};
		FieldListPtr groupByFieldListPtr_{};
		FilterBasePtr havingFilterPtr_{};
		OrderByClauseListPtr orderByClauseListPtr_{};
		ListOfValuesPtr listOfValuesPtr_{};
		QueryListPtr queryListPtr_{};
//		ParameterMapPtr parameterMapPtr_{};
		bool parameterChange_{ false };
		LimitClausePtr limitClausePtr_{};
		OffsetClausePtr offsetClausePtr_{};

//		CompositeConditionPtr currentWhereChainPtr_{};
//		CompositeConditionList whereGroupStack_{};
//		bool isWhereChaining_{ false };

//		CompositeConditionPtr currentHavingChainPtr_{};
//		CompositeConditionList havingGroupStack_{};
//		bool isHavingChaining_{ false };

//		void addConditionToWhereChain(const ConditionBase& conditionBase, LogicOperator logicOperator);
//		void addConditionToHavingChain(const ConditionBase& conditionBase, LogicOperator logicOperator);

		ComponentMapPtr componentMapPtr_{};
		void populateComponents();
	};
}
