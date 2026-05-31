// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import :BuilderBase;

import :BuilderTypes;
import :JoinClause;
import :Table;
import :Variant;
import :Field;
import :ComparisonFilter;
import :Parameter;
import :ListOfValues;
import :Query;
import :EnumMaps;

namespace DataAccessLayer::SqlQueryBuilder
{
	String BuilderBase::buildComponent(const JoinClause& joinClause) const
	{
		std::cout << "buildComponent(JoinClause)" << std::endl;

		const Table table{ joinClause.fromField().tableName() };

		std::cout << "table = " << table.sql() << std::endl;
		std::cout << "joinType = " << JoinTypeMap.at(joinClause.joinType()) << std::endl;

		String joinClauseString{ JoinTypeMap.at(joinClause.joinType()) + " " + table.sql(this) + " ON " };

		const ComparisonFilter filter(FieldRef{joinClause.fromField()}, joinClause.comparison(), FieldRef{joinClause.toField()});

		std::cout << "filter = " << filter.sql() << std::endl;

		joinClauseString += filter.sql(this);

		return joinClauseString;
	}
}
