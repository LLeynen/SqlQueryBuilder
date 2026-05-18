// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import :BuilderTypes;
import :JoinClause;
import :Table;
import :Variant;
import :Field;
import :Condition;
import :Parameter;
import :ListOfValues;
import :Query;
import :EnumMaps;

namespace DataAccessLayer::SqlQueryBuilder
{
	String BuilderBase::buildComponent(const JoinClause& joinClause) const
	{
		const Table table{ joinClause.toField().tableName() };

		String joinClauseString{ JoinTypeMap.at(joinClause.joinType()) + " " + buildComponent(table) + " ON " };

		const Condition condition(joinClause.fromField(), joinClause.comparison(), joinClause.toField());

		joinClauseString += buildComponent(condition);

		return joinClauseString;
	}
}
