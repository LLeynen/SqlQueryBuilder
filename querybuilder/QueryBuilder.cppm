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
//		QueryBuilder& sum(const std::initializer_list<const char*> fieldTokens, std::optional<Alias> alias = std::nullopt)
//		{
//			return sum(Operand{ FieldRef{ fieldTokens } }, std::move(alias));
//		}

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

		template <typename LhsType, typename RhsType>
		QueryBuilder& expression(LhsType&& lhs, Operator op, RhsType&& rhs, std::optional<Alias> alias = std::nullopt)
		{
			ensureSharedPtr(impl_->selectableListPtr_);
			impl_->selectableListPtr_->push_back(
				std::make_unique<Expression>(
					std::forward<LhsType>(lhs),
					op,
					std::forward<RhsType>(rhs),
					std::move(alias)
				)
			);

			return *this;
		}

		QueryBuilder& expression(Operator op, Operand operand, std::optional<Alias> alias = std::nullopt);
		QueryBuilder& expression(Operator op, FormulaValue formulaValue, std::optional<Alias> alias = std::nullopt);

		template <typename LhsType>
		QueryBuilder& expression(Operator op, LhsType&& lhs, std::optional<Alias> alias = std::nullopt)
		{
			ensureSharedPtr(impl_->selectableListPtr_);
			impl_->selectableListPtr_->push_back(
				std::make_unique<Expression>(
					op,
					std::forward<LhsType>(lhs),
					std::move(alias)
				)
			);

			return *this;
		}

		// 1. Binary Math: Handles Column-to-Column operations
		// Captures: .expression({"Quantity"}, Multiply, {"Price"})
		QueryBuilder& expression(FieldRef lhs, Operator op, FieldRef rhs, std::optional<Alias> alias = std::nullopt)
		{
			ensureSharedPtr(impl_->selectableListPtr_);
			impl_->selectableListPtr_->push_back(std::make_unique<Expression>(Operand{lhs}, op, Operand{rhs}, std::move(alias)));
			return *this;
		}

		// 2. Binary Math: Handles Column-to-Value operations
		// Captures: .expression({"Price"}, Multiply, 1.10)
		QueryBuilder& expression(FieldRef lhs, Operator op, FormulaValue rhs, std::optional<Alias> alias = std::nullopt)
		{
			ensureSharedPtr(impl_->selectableListPtr_);
			impl_->selectableListPtr_->push_back(std::make_unique<Expression>(Operand{lhs}, op, std::move(rhs), std::move(alias)));
			return *this;
		}

		// 3. Unary Math: Handles operations like NOT or IS NULL
		// Captures: .expression(Operator::Not, {"IsActive"})
		QueryBuilder& expression(Operator op, FieldRef lhs, std::optional<Alias> alias = std::nullopt)
		{
			ensureSharedPtr(impl_->selectableListPtr_);
			impl_->selectableListPtr_->push_back(std::make_unique<Expression>(op, Operand{lhs}, std::move(alias)));
			return *this;
		}

		QueryBuilder& expression(FieldRef lhs, Operator op, std::initializer_list<const char*> rhsTokens, std::optional<Alias> alias = std::nullopt)
		{
			ensureSharedPtr(impl_->selectableListPtr_);
			impl_->selectableListPtr_->push_back(std::make_unique<Expression>(Operand{lhs}, op, Operand{FieldRef{rhsTokens}}, std::move(alias)));
			return *this;
		}

/*
		QueryBuilder& expression(const std::initializer_list<const char*> fieldTokensLhs, const Operator op, const std::initializer_list<const char*> fieldTokensRhs, std::optional<Alias> alias = std::nullopt)
		{
			return expression (Operand{ FieldRef{ fieldTokensLhs }} , op, Operand{ FieldRef{ fieldTokensRhs } }, alias);
		}

		QueryBuilder& expression(const std::initializer_list<const char*> fieldTokensLhs, const Operator op, FormulaValue formulaValue, std::optional<Alias> alias = std::nullopt)
		{
			return expression (Operand{ FieldRef{ fieldTokensLhs }} , op, std::move(formulaValue), alias);
		}

		QueryBuilder& expression(FormulaValue formulaValue, const Operator op, const std::initializer_list<const char*> fieldTokensRhs, std::optional<Alias> alias = std::nullopt)
		{
			return expression (std::move(formulaValue), op, Operand{ FieldRef{ fieldTokensRhs }}, alias);
		}
*/
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

		//QueryBuilder& where(Operand lhs, Comparison comp, Operand rhs);
/*
		QueryBuilder& where(FieldRef lhs, Comparison comp, Operand rhs)
		{
			return where(ComparisonFilter(std::move(lhs), comp, std::move(rhs)));
		}
		QueryBuilder& where(FieldRef lhs, Comparison comp, FieldRef rhs) {
			return where(ComparisonFilter(std::move(lhs), comp, std::move(rhs)));
		}
		QueryBuilder& where(Expression lhs, Comparison comp, Operand rhs)
		{
			return where(ComparisonFilter(std::move(lhs), comp, std::move(rhs)));
		}
*/
		// order by
		QueryBuilder& orderBy(FieldRef fieldRef, SortOrder sortOrder = SortOrder::Ascending);
		QueryBuilder& orderBy(String tableName, std::initializer_list<String> columnNameList, SortOrder sortOrder = SortOrder::Ascending);
		QueryBuilder& orderBy(std::initializer_list<FieldRef> fieldRefList, SortOrder sortOrder = SortOrder::Ascending);

		// group by
		QueryBuilder& groupBy(FieldRef fieldRef);
		QueryBuilder& groupBy(std::initializer_list<FieldRef> fieldRefList);
//		QueryBuilder& groupBy(std::initializer_list<String> columnNameList);
		QueryBuilder& groupBy(String tableName, std::initializer_list<String> columnNameList);

		// having
		QueryBuilder& having(const FilterBase& filter);
		QueryBuilder& having(Operand lhs, Comparison comparison, FilterValue filterValue)
		{
			return having(ComparisonFilter { std::move(lhs), comparison, std::move(filterValue) });
		}
		QueryBuilder& having(const std::initializer_list<const char*> fieldTokens, Comparison comparison, FilterValue filterValue)
		{
			return having (ComparisonFilter { Operand{ FieldRef{ fieldTokens } }, comparison, std::move(filterValue) });
		}


//		QueryBuilder& having(Operand lhs, Comparison comp, Operand rhs);

/*
		QueryBuilder& having(FieldRef lhs, Comparison comp, Operand rhs)
		{
			return having(Operand{ std::move(lhs) }, comp, std::move(rhs));
		}

		QueryBuilder& having(Operand lhs, Comparison comp, FieldRef rhs)
		{
			return having(std::move(lhs), comp, Operand{ std::move(rhs) });
		}

		QueryBuilder& having(FieldRef lhs, Comparison comp, FieldRef rhs) {
			return having(Operand{ std::move(lhs) }, comp, Operand{ std::move(rhs) });
		}
*/

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
