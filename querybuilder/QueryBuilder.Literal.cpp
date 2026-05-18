// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import :BuilderTypes;
import :Concepts;
import :Literal;
import :Impl;

namespace DataAccessLayer::SqlQueryBuilder
{
	// QueryBuilder::literal(Literal&)
	QueryBuilder& QueryBuilder::literal(const Literal& sqlLiteral)
	{
		ensureSharedPtr(impl_->selectableListPtr_);
		impl_->selectableListPtr_->push_back(std::make_shared<Literal>(sqlLiteral));
		return *this;
	}

	// QueryBuilder::literal(Variant, optional<String>)
	QueryBuilder& QueryBuilder::literal(const Variant& literalVariant, const std::optional<String>& alias)
	{
		ensureSharedPtr(impl_->selectableListPtr_);

		Literal sqlLiteral(literalVariant, alias);
		impl_->selectableListPtr_->push_back(std::make_shared<Literal>(sqlLiteral));

		return *this;
	}
}
