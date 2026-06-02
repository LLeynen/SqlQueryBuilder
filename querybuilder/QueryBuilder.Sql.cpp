// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import std;

import :BuilderTypes;
import :Concepts;
import :ComponentWrappers;
import :IBuilder;
import :ParameterRegistry;
import :Impl;

namespace DataAccessLayer::SqlQueryBuilder
{
	namespace
	{
		String formatter(String sql)
		{
			for (const std::string& keyword : {" FROM ", " INNER JOIN ", " WHERE ", " ORDER BY ", " (SELECT "})
			{
				size_t pos = 0;
				while ((pos = sql.find(keyword, pos)) != std::string::npos)
				{
					sql.replace(pos, 1, "\n");
					pos += 1;
				}
			}
			return sql;
		}
	}


	String QueryBuilder::sql() const
	{
		ParameterRegistry::incrementContext();

		try
		{
			if (impl_->componentMapPtr_ && !impl_->componentMapPtr_->empty())
			{
				clear();
			}

			impl_->populateComponents();

			String sqlStatement = impl_->builderPtr_->buildQuery(impl_->queryType_, *impl_->componentMapPtr_);

			ParameterRegistry::decrementContext();

			return formatter(sqlStatement);
		}
		catch (...)
		{
			ParameterRegistry::decrementContext();
			throw;
		}
	}


	void QueryBuilder::clear() const
	{
		impl_->componentMapPtr_->clear();
	}
}
