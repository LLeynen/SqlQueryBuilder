// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

export module QueryBuilder;

import std;

//export import :Alias;
export import :Interface;
import :Concepts;
import :Impl;



export namespace DataAccessLayer::SqlQueryBuilder
{
	class QueryBuilderImpl;

	export class QueryBuilder
	{
	public:
		QueryBuilder(QueryType queryType = QueryType::SelectQuery, DatabaseEngine databaseEngine = defaultDatabaseEngine());
		~QueryBuilder();

		QueryBuilder(const QueryBuilder& other);
		QueryBuilder& operator=(const QueryBuilder& other);
		QueryBuilder(QueryBuilder&&) noexcept;
		QueryBuilder& operator=(QueryBuilder&&) noexcept;

		[[nodiscard]] QueryType queryType() const;
		void setQueryType(QueryType queryType);
		[[nodiscard]] const DatabaseEngine databaseEngine() const;
		void setDatabaseEngine(DatabaseEngine databaseEngine);
		[[nodiscard]] ParameterMapPtr parameterMap() const;
		void setParameterMap(const ParameterMapPtr& parameterMapPtr);

		// distinct
		QueryBuilder& distinct(bool distinct = true);

		// top
		QueryBuilder& top(int quantity, TopUnit topUnit = TopUnit::Records);
		QueryBuilder& topPercent(int top);

		// field
		QueryBuilder& allFields(std::optional<String> tableName = std::nullopt);
        QueryBuilder& field(const FieldRef& fieldRef);
		QueryBuilder& field(const QueryBuilder& queryBuilder, std::optional<Alias> alias = std::nullopt);
		QueryBuilder& field(const String& parameterName, std::optional<Alias> alias = std::nullopt);

        QueryBuilder& fields(std::initializer_list<FieldRef> fieldRefList);
        QueryBuilder& fields(const String& tableName, std::initializer_list<String> columnNameList);

		// aggregate
		QueryBuilder& aggregate(AggregateFunction aggregateFunction, Operand operand, std::optional<Alias> alias = std::nullopt);

		QueryBuilder& sum(Operand operand, std::optional<Alias> alias = std::nullopt)
		{
			return aggregate(AggregateFunction::Sum, std::move(operand), std::move(alias));
		}

		QueryBuilder& avg(Operand operand, const std::optional<Alias>& alias = std::nullopt)
		{
			return aggregate(AggregateFunction::Avg , std::move(operand), std::move(alias));
		}

		QueryBuilder& min(Operand operand, const std::optional<Alias>& alias = std::nullopt)
		{
			return aggregate(AggregateFunction::Min, std::move(operand), std::move(alias));
		}

		QueryBuilder& max(Operand operand, const std::optional<Alias>& alias = std::nullopt)
		{
			return aggregate(AggregateFunction::Max, std::move(operand), std::move(alias));
		}

		QueryBuilder& count(Operand operand, const std::optional<Alias>& alias = std::nullopt)
		{
			return aggregate(AggregateFunction::Count, std::move(operand), std::move(alias));
		}

		QueryBuilder& stddev(Operand operand, const std::optional<Alias>& alias = std::nullopt)
		{
			return aggregate(AggregateFunction::StdDev, std::move(operand), std::move(alias));
		}

		QueryBuilder& var(Operand operand, const std::optional<Alias>& alias = std::nullopt)
		{
			return aggregate(AggregateFunction::Var, std::move(operand), std::move(alias));
		}

		QueryBuilder& first(Operand operand, const std::optional<Alias>& alias = std::nullopt)
		{
			return aggregate(AggregateFunction::First, std::move(operand), std::move(alias));
		}

		QueryBuilder& last(Operand operand, const std::optional<Alias>& alias = std::nullopt)
		{
			return aggregate(AggregateFunction::Last, std::move(operand), std::move(alias));
		}

		// expression
		QueryBuilder& expression(const Expression& expression);
		QueryBuilder& expression(const Operand& left, Operator op, const Operand& right, const std::optional<String>& alias = std::nullopt);
		QueryBuilder& expression(Operator op, const Operand& operand, const std::optional<String>& alias = std::nullopt);
		QueryBuilder& expression(const Selectable& selectable, const std::optional<String>& alias = std::nullopt);
		QueryBuilder& expression(ScalarFunction function, std::initializer_list<Operand> args, const std::optional<String>& alias = std::nullopt);
		QueryBuilder& expression(AggregateFunction function, const Selectable& selectable, const std::optional<String>& alias = std::nullopt);

		// literal
		QueryBuilder& literal(const Variant& sqlLiteral, const std::optional<String>& alias = std::nullopt);
		QueryBuilder& literal(const Literal& literal);

		// from
		QueryBuilder& from(const DataSource& dataSource);
		QueryBuilder& from(const String& tableName, std::optional<Alias> alias = std::nullopt);
		QueryBuilder& from(const QueryBuilder& queryBuilder, std::optional<Alias> alias = std::nullopt);

		// join
		QueryBuilder& join(const JoinClause& joinClause);
		QueryBuilder& join(const FieldRef& primaryKey, Comparison comparison, const FieldRef& foreignKey, JoinType joinType = JoinType::InnerJoin);

		// where
		QueryBuilder& where(const ConditionBase& conditionBase);
		QueryBuilder& where(const FieldRef& fieldRef, Comparison comparison, const ConditionVariant& conditionValue);
//		QueryBuilder& where(const String& columnName, Comparison comparison, const ConditionVariant& conditionValue);
//		QueryBuilder& where(const String& tableName, const String& columnName, Comparison comparison, const ConditionVariant& conditionValue);

		QueryBuilder& andWhere(const ConditionBase& conditionBase);
		QueryBuilder& andWhere(const FieldRef& field, Comparison comparison, const ConditionVariant& conditionValue);
//		QueryBuilder& andWhere(const String& columnName, Comparison comparison, const ConditionVariant& conditionValue);
//		QueryBuilder& andWhere(const String& tableName, const String& columnName, Comparison comparison, const ConditionVariant& conditionValue);

		QueryBuilder& orWhere(const ConditionBase& conditionBase);
		QueryBuilder& orWhere(const FieldRef& fieldRef, Comparison comparison, const ConditionVariant& conditionValue);
//		QueryBuilder& orWhere(const String& columnName, Comparison comparison, const ConditionVariant& conditionValue);
//		QueryBuilder& orWhere(const String& tableName, const String& columnName, Comparison comparison, const ConditionVariant& conditionValue);

		QueryBuilder& whereGroup();
		QueryBuilder& endGroup();

		// order by
		QueryBuilder& orderBy(const FieldRef& fieldRef, SortOrder sortOrder = SortOrder::Ascending);
//		QueryBuilder& orderBy(const String& columnName, SortOrder sortOrder = SortOrder::Ascending);
//		QueryBuilder& orderBy(const String& tableName, const String& columnName, SortOrder sortOrder = SortOrder::Ascending);

		QueryBuilder& orderBy(FieldList& fieldList, SortOrder sortOrder = SortOrder::Ascending);
		QueryBuilder& orderBy(const String& tableName, std::initializer_list<String> columnNameList, SortOrder sortOrder = SortOrder::Ascending);
		QueryBuilder& orderBy(std::initializer_list<String> columnNameList, SortOrder sortOrder = SortOrder::Ascending);

		// group by
		QueryBuilder& groupBy(const FieldRef& fieldRef);
//		QueryBuilder& groupBy(const String& columnName);
//		QueryBuilder& groupBy(const String& tableName, const String& columnName);

		QueryBuilder& groupBy(std::initializer_list<FieldRef> fieldRefList);
		QueryBuilder& groupBy(const String& tableName, std::initializer_list<String> columnNameList);
//		QueryBuilder& groupBy(std::initializer_list<String> columnNameList);

		// having
		QueryBuilder& having(const ConditionBase& conditionBase);
		QueryBuilder& having(const FieldRef& fieldRef, Comparison comparison, const ConditionVariant& conditionValue);
//		QueryBuilder& having(const String& columnName, Comparison comparison, const ConditionVariant& conditionValue);
//		QueryBuilder& having(const String& tableName, const String& columnName, Comparison comparison, const ConditionVariant& conditionValue);

		QueryBuilder& andHaving(const ConditionBase& conditionBase);
		QueryBuilder& andHaving(const FieldRef& fieldRef, Comparison comparison, const ConditionVariant& conditionValue);
//		QueryBuilder& andHaving(const String& columnName, Comparison comparison, const ConditionVariant& conditionValue);
//		QueryBuilder& andHaving(const String& tableName, const String& columnName, Comparison comparison, const ConditionVariant& conditionValue);

		QueryBuilder& orHaving(const ConditionBase& conditionBase);
        QueryBuilder& orHaving(const FieldRef& fieldRef, Comparison comparison, const ConditionVariant& conditionValue);
//      QueryBuilder& orHaving(const String& columnName, Comparison comparison, const ConditionVariant& conditionValue);
//      QueryBuilder& orHaving(const String& tableName, const String& columnName, Comparison comparison, const ConditionVariant& conditionValue);

		QueryBuilder& havingGroup();
		QueryBuilder& endHavingGroup();

		// value list
		QueryBuilder& values(const ListOfValues& values);
		QueryBuilder& values(std::initializer_list<Variant> valueList);
		QueryBuilder& values(const VariantList& valueList);
		QueryBuilder& appendValue(const Variant& value);
		QueryBuilder& appendValues(const VariantList& valueList);
		QueryBuilder& appendValues(std::initializer_list<Variant> valueList);

		// query
		QueryBuilder& query(Query query);
		QueryBuilder& query(const String& sqlString);
		QueryBuilder& query(const QueryBuilder& queryBuilder);
		QueryBuilder& queries(std::initializer_list<QueryBuilder> queryBuilderList);

		// Parameter
		QueryBuilder& parameterValue(const ParameterValue& parameter);
		QueryBuilder& parameterValue(const String& parameterName, const Variant& value = nullptr);
		QueryBuilder& parameterValues(std::initializer_list<ParameterValue> parameterList);

		QueryBuilder& limit(int limit);
		QueryBuilder& offset(int offset);

		// SQL generation
		String sql();
		void clear();

	private:
		std::unique_ptr<QueryBuilderImpl> impl_{ nullptr };
	};
}
