// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderTypes;
import :Concepts;
import :Function;
import :Impl;

namespace DataAccessLayer::SqlQueryBuilder
{
	QueryBuilder& QueryBuilder::function(Function function)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		impl_->selectableListPtr_->push_back(std::make_shared<Function>(std::move(function)));

		return *this;
	}


	QueryBuilder& QueryBuilder::function(ScalarFunction scalarFunction, std::vector<FormulaArg> args, std::optional<Alias> alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		impl_->selectableListPtr_->push_back(std::make_shared<Function>(scalarFunction, args, std::move(alias)));

		return *this;
	}
}

