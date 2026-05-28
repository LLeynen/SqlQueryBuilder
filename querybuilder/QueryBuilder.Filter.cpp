// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import :BuilderTypes;
import :Concepts;
import :FilterSelectable;
import :Impl;

namespace DataAccessLayer::SqlQueryBuilder
{
	QueryBuilder& QueryBuilder::filter(FilterBase& filter, std::optional<Alias> alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		const auto filterSelectable = std::make_shared<FilterSelectable>(std::move(filter), std::move(alias));

		impl_->selectableListPtr_->push_back(filterSelectable);

		return *this;
	}
}