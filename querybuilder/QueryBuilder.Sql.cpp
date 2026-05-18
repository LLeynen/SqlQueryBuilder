// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import :BuilderTypes;
import :Concepts;
import :ComponentWrappers;
import :IBuilder;
import :Impl;

namespace DataAccessLayer::SqlQueryBuilder
{
	// QueryBuilder::sql
	String QueryBuilder::sql()
	{
		if (impl_->componentMapPtr_ && !impl_->componentMapPtr_->empty())
		{
			clear();
		}

		impl_->populateComponents();

		String sqlStatement = impl_->builderPtr_->buildQuery(impl_->queryType_, *impl_->componentMapPtr_);

		return sqlStatement;
	}

	// QueryBuilder::clear
	void QueryBuilder::clear()
	{
		impl_->componentMapPtr_->clear();
	}
}
