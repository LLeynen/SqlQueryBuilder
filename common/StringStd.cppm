// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:StringStd;

#ifndef QT

import std;

namespace DataAccessLayer::SqlQueryBuilder
{
	export using String = std::string;

	export template <typename T>
		requires
	std::is_integral_v<T> ||
		std::is_floating_point_v<T>
		String toString(T value)
	{
		return std::to_string(value);
	}

	export constexpr size_t npos = -1;
}

#endif
