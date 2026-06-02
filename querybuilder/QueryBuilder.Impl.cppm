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
		bool parameterChange_{ false };
		LimitClausePtr limitClausePtr_{};
		OffsetClausePtr offsetClausePtr_{};

		ComponentMapPtr componentMapPtr_{};
		void populateComponents();
	};
}
