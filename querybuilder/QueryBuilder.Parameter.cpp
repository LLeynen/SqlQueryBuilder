// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import :BuilderTypes;

namespace DataAccessLayer::SqlQueryBuilder
{
	QueryBuilder& QueryBuilder::parameter(Parameter parameter, std::optional<Alias> alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		const auto parameterSelectable = std::make_shared<ParameterSelectable>(std::move(parameter), std::move(alias));

		impl_->selectableListPtr_->push_back(parameterSelectable);

		return *this;
	}


	QueryBuilder& QueryBuilder::parameter(String name, std::optional<Alias> alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		Parameter parameter { std::move(name) };

		const auto parameterSelectable = std::make_shared<ParameterSelectable>(std::move(parameter), std::move(alias));

		impl_->selectableListPtr_->push_back(parameterSelectable);

		return *this;
	}
}
