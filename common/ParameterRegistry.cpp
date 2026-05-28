// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :ParameterRegistry;

import std;

import :BuilderTypes;

namespace DataAccessLayer::SqlQueryBuilder
{
	struct ParameterRegistryImpl
	{
		ParameterRegistryMap params_;
	};


	[[nodiscard]] static ParameterRegistryImpl& instance() noexcept
	{
		thread_local ParameterRegistryImpl storage;
		return storage;
	}


	void ParameterRegistry::set(const String& name, Variant value) noexcept
	{
		instance().params_[name] = std::move(value);
	}


	Variant ParameterRegistry::get(const String& name) noexcept
	{
		auto& map = instance().params_;
		if (const auto it = map.find(name); it != map.end())
		{
			return it->second;
		}
		return Variant{};
	}


	void ParameterRegistry::clear() noexcept
	{
		instance().params_.clear();
	}
}