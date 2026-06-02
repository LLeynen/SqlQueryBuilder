// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

export module QueryBuilder;

import std;

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
		void setQueryType(QueryType queryType) const;
		[[nodiscard]] DatabaseEngine databaseEngine() const;
		void setDatabaseEngine(DatabaseEngine databaseEngine) const;

		// distinct
		QueryBuilder& distinct(bool distinct = true);

		// top
		QueryBuilder& top(int quantity, TopUnit topUnit = TopUnit::Records);
		QueryBuilder& topPercent(int quantity);

		// selectables
		QueryBuilder& field(FieldRef fieldRef);
		QueryBuilder& field(FieldRef fieldRef, std::optional<Alias> alias);
		QueryBuilder& allFields(std::optional<String> tableName = std::nullopt);
		QueryBuilder& fields(std::initializer_list<FieldRef> fieldRefList);
		QueryBuilder& fields(String tableName, std::initializer_list<String> columnNameList);
		QueryBuilder& fields(std::initializer_list<const char*> flatNames);

		QueryBuilder& subQuery(QueryBuilder queryBuilder, std::optional<Alias> alias = std::nullopt);
		QueryBuilder& subQuery(Query query, std::optional<Alias> alias = std::nullopt);
		QueryBuilder& subQuery(String rawSql, std::optional<Alias> alias = std::nullopt);

		QueryBuilder& parameter(Parameter parameter, std::optional<Alias> alias = std::nullopt);
		QueryBuilder& parameter(String name, std::optional<Alias> alias = std::nullopt);
		QueryBuilder& filter(FilterBase& filter, std::optional<Alias> alias = std::nullopt);
		QueryBuilder& literal(Literal literal);
		QueryBuilder& literal(Variant literal, std::optional<Alias> alias = std::nullopt);

		// aggregate
		QueryBuilder& aggregate(Aggregate aggregate);
		QueryBuilder& aggregate(AggregateFunction aggregateFunction, Operand operand, std::optional<Alias> alias = std::nullopt);
		QueryBuilder& aggregate(AggregateFunction aggregateFunction, FieldRef fieldRef, std::optional<Alias> alias = std::nullopt)
		{
			return aggregate(aggregateFunction, Operand{ std::move(fieldRef) }, std::move(alias));
		}

		// aggregate helpers
		QueryBuilder& sum(Operand operand, std::optional<Alias> alias = std::nullopt)
		{
			return aggregate(AggregateFunction::Sum, std::move(operand), std::move(alias));
		}

		QueryBuilder& sum(FieldRef fieldRef, std::optional<Alias> alias = std::nullopt)
		{
			return sum(Operand{ std::move(fieldRef) }, std::move(alias));
		}

		QueryBuilder& avg(Operand operand, std::optional<Alias> alias = std::nullopt)
		{
			return aggregate(AggregateFunction::Avg , std::move(operand), std::move(alias));
		}

		QueryBuilder& avg(FieldRef fieldRef, std::optional<Alias> alias = std::nullopt)
		{
			return avg(Operand{ std::move(fieldRef) }, std::move(alias));
		}

		QueryBuilder& min(Operand operand, std::optional<Alias> alias = std::nullopt)
		{
			return aggregate(AggregateFunction::Min, std::move(operand), std::move(alias));
		}

		QueryBuilder& min(FieldRef fieldRef, std::optional<Alias> alias = std::nullopt)
		{
			return min(Operand{ std::move(fieldRef) }, std::move(alias));
		}

		QueryBuilder& max(Operand operand, std::optional<Alias> alias = std::nullopt)
		{
			return aggregate(AggregateFunction::Max, std::move(operand), std::move(alias));
		}

		QueryBuilder& max(FieldRef fieldRef, std::optional<Alias> alias = std::nullopt)
		{
			return max(Operand{ std::move(fieldRef) }, std::move(alias));
		}

		QueryBuilder& count(Operand operand, std::optional<Alias> alias = std::nullopt)
		{
			return aggregate(AggregateFunction::Count, std::move(operand), std::move(alias));
		}

		QueryBuilder& count(FieldRef fieldRef, std::optional<Alias> alias = std::nullopt)
		{
			return count(Operand{ std::move(fieldRef) }, std::move(alias));
		}

		QueryBuilder& stddev(Operand operand, std::optional<Alias> alias = std::nullopt)
		{
			return aggregate(AggregateFunction::StdDev, std::move(operand), std::move(alias));
		}

		QueryBuilder& stddev(FieldRef fieldRef, std::optional<Alias> alias = std::nullopt)
		{
			return stddev(Operand{ std::move(fieldRef) }, std::move(alias));
		}

		QueryBuilder& var(Operand operand, std::optional<Alias> alias = std::nullopt)
		{
			return aggregate(AggregateFunction::Var, std::move(operand), std::move(alias));
		}

		QueryBuilder& var(FieldRef fieldRef, std::optional<Alias> alias = std::nullopt)
		{
			return var(Operand{ std::move(fieldRef) }, std::move(alias));
		}

		QueryBuilder& first(Operand operand, std::optional<Alias> alias = std::nullopt)
		{
			return aggregate(AggregateFunction::First, std::move(operand), std::move(alias));
		}

		QueryBuilder& first(FieldRef fieldRef, std::optional<Alias> alias = std::nullopt)
		{
			return first(Operand{ std::move(fieldRef) }, std::move(alias));
		}

		QueryBuilder& last(Operand operand, std::optional<Alias> alias = std::nullopt)
		{
			return aggregate(AggregateFunction::Last, std::move(operand), std::move(alias));
		}

		QueryBuilder& last(FieldRef fieldRef, std::optional<Alias> alias = std::nullopt)
		{
			return last(Operand{ std::move(fieldRef) }, std::move(alias));
		}

		// Function
		QueryBuilder& function(Function function);
		QueryBuilder& function(ScalarFunction scalarFunction, std::vector<FormulaArg> args, std::optional<Alias> alias = std::nullopt);

		// expression
		QueryBuilder& expression(Expression expression);

		QueryBuilder& expression(Operand lhs, Operator op, Operand rhs, std::optional<Alias> alias = std::nullopt);
		QueryBuilder& expression(Operand lhs, Operator op, FormulaValue formulaValue, std::optional<Alias> alias = std::nullopt);
		QueryBuilder& expression(FormulaValue formulaValue, Operator op, Operand rhs, std::optional<Alias> alias = std::nullopt);
		QueryBuilder& expression(Operator op, Operand operand, std::optional<Alias> alias = std::nullopt);
		QueryBuilder& expression(Operator op, FormulaValue formulaValue, std::optional<Alias> alias = std::nullopt);

		QueryBuilder& expression(FieldRef lhs, Operator op, FieldRef rhs, std::optional<Alias> alias = std::nullopt)
		{
			ensureSharedPtr(impl_->selectableListPtr_);
			impl_->selectableListPtr_->push_back(std::make_unique<Expression>(Operand{std::move(lhs)}, op, Operand{std::move(rhs)}, std::move(alias)));
			return *this;
		}

		QueryBuilder& expression(FieldRef lhs, Operator op, FormulaValue rhs, std::optional<Alias> alias = std::nullopt)
		{
			ensureSharedPtr(impl_->selectableListPtr_);
			impl_->selectableListPtr_->push_back(std::make_unique<Expression>(Operand{std::move(lhs)}, op, std::move(rhs), std::move(alias)));
			return *this;
		}

		QueryBuilder& expression(Operator op, FieldRef lhs, std::optional<Alias> alias = std::nullopt)
		{
			ensureSharedPtr(impl_->selectableListPtr_);
			impl_->selectableListPtr_->push_back(std::make_unique<Expression>(op, Operand{std::move(lhs)}, std::move(alias)));
			return *this;
		}

		QueryBuilder& expression(FieldRef lhs, Operator op, const std::initializer_list<const char*> rhsTokens, std::optional<Alias> alias = std::nullopt)
		{
			ensureSharedPtr(impl_->selectableListPtr_);
			impl_->selectableListPtr_->push_back(std::make_unique<Expression>(Operand{std::move(lhs)}, op, Operand{FieldRef{rhsTokens}}, std::move(alias)));
			return *this;
		}

		QueryBuilder& expression(ScalarFunction scalarFunction, std::vector<FormulaArg> args, std::optional<Alias> alias = std::nullopt);
		QueryBuilder& expression(AggregateFunction aggregateFunction, FormulaArg arg, std::optional<Alias> alias = std::nullopt) noexcept;

		// from
		QueryBuilder& from(const DataSource& dataSource);
		QueryBuilder& from(String tableName, std::optional<Alias> alias = std::nullopt);
		QueryBuilder& from(QueryBuilder queryBuilder, std::optional<Alias> alias = std::nullopt);

		// join
		QueryBuilder& join(const JoinClause& joinClause);
		QueryBuilder& join(FieldRef primaryKey, Comparison comparison, FieldRef foreignKey, JoinType joinType = JoinType::InnerJoin);

		// where
		QueryBuilder& where(const FilterBase& filter);

		QueryBuilder& where(Operand lhs, Comparison comparison, FilterValue filterValue)
		{
			return where (ComparisonFilter { std::move(lhs), comparison, std::move(filterValue) });
		}

		QueryBuilder& where(const std::initializer_list<const char*> fieldTokens, Comparison comparison, FilterValue filterValue)
		{
			return where (ComparisonFilter { Operand{ FieldRef{ fieldTokens } }, comparison, std::move(filterValue) });
		}

		// order by
		QueryBuilder& orderBy(FieldRef fieldRef, SortOrder sortOrder = SortOrder::Ascending);
		QueryBuilder& orderBy(String tableName, std::initializer_list<String> columnNameList, SortOrder sortOrder = SortOrder::Ascending);
		QueryBuilder& orderBy(std::initializer_list<FieldRef> fieldRefList, SortOrder sortOrder = SortOrder::Ascending);

		// group by
		QueryBuilder& groupBy(FieldRef fieldRef);
		QueryBuilder& groupBy(std::initializer_list<FieldRef> fieldRefList);
		QueryBuilder& groupBy(String tableName, std::initializer_list<String> columnNameList);

		// having
		QueryBuilder& having(const FilterBase& filter);
		QueryBuilder& having(Operand lhs, const Comparison comparison, FilterValue filterValue)
		{
			return having(ComparisonFilter { std::move(lhs), comparison, std::move(filterValue) });
		}
		QueryBuilder& having(const std::initializer_list<const char*> fieldTokens, Comparison comparison, FilterValue filterValue)
		{
			return having (ComparisonFilter { Operand{ FieldRef{ fieldTokens } }, comparison, std::move(filterValue) });
		}

		// value list
		QueryBuilder& values(ListOfValues values);
		QueryBuilder& values(std::initializer_list<Variant> valueList);
		QueryBuilder& values(VariantList valueList);
		QueryBuilder& appendValue(Variant value);
		QueryBuilder& appendValues(VariantList valueList);
		QueryBuilder& appendValues(std::initializer_list<Variant> valueList);

		// query
		QueryBuilder& query(Query query);
		QueryBuilder& query(String rawSql);
		QueryBuilder& query(QueryBuilder queryBuilder);
		QueryBuilder& queries(std::initializer_list<QueryBuilder> queryBuilderList);

		// Offset/Limit
		QueryBuilder& limit(int limit);
		QueryBuilder& offset(int offset);

		// SQL generation
		[[nodiscard]] String sql() const;
		void clear() const;

	private:
		std::unique_ptr<QueryBuilderImpl> impl_{ nullptr };
	};
}
