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
	String QueryBuilder::sql() const
	{
		if (impl_->componentMapPtr_ && !impl_->componentMapPtr_->empty())
		{
			clear();
		}

		impl_->populateComponents();

		String sqlStatement = impl_->builderPtr_->buildQuery(impl_->queryType_, *impl_->componentMapPtr_);

		return sqlStatement;
	}


	void QueryBuilder::clear() const
	{
		impl_->componentMapPtr_->clear();
	}
}
