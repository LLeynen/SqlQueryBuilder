// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:ParameterRegistry;

import std;

import :BuilderTypes;
import :Variant;

namespace DataAccessLayer::SqlQueryBuilder
{
	export class ParameterRegistry
	{
	public:
		ParameterRegistry() = delete;

		static void set(const String& name, Variant value) noexcept;
		[[nodiscard]] static Variant get(const String& name) noexcept;

		static void clear() noexcept;
	};
}
