// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:StringStd;

#ifndef QT

import std;

namespace DataAccessLayer::SqlQueryBuilder
{
	// Alias for standard string
	export using String = std::string;

	// toString template function
	export template <typename T>
		requires
	std::is_integral_v<T> ||
		std::is_floating_point_v<T>
		String toString(T value)
	{
		return std::to_string(value);
	}

	// npos replacement for std::npos
	export constexpr size_t npos = -1;
}

#endif
