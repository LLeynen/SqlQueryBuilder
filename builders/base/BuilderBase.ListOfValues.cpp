// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :BuilderBase;

import std;

import :BuilderTypes;
import :ListOfValues;

namespace DataAccessLayer::SqlQueryBuilder
{
	String BuilderBase::buildComponent(const ListOfValues& listOfValues) const
	{
		String listOfValuesString{ };

		if (const auto valueList = listOfValues.valueList(); valueList.empty() == false)
		{
			listOfValuesString = "(";

			for (size_t i = 0; i < valueList.size(); ++i)
			{
				listOfValuesString += valueList.at(i).sqlFormat();

				if (i < valueList.size() - 1)
				{
					listOfValuesString += ", ";
				}
			}

			listOfValuesString += ")";
		}

		return listOfValuesString;
	}
}
