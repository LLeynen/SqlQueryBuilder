// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:EnumMap;

import std;

import :String;

namespace DataAccessLayer::SqlQueryBuilder
{
	// EnumType concept
	template <typename TEnum>
	concept EnumType = std::is_enum_v<TEnum>;

	export template <EnumType TEnum, class TValue = String>
		class EnumMap : public std::unordered_map<TEnum, TValue>
	{
	public:
		EnumMap(std::initializer_list<std::pair<const TEnum, TValue>> list);

		TValue operator()(TEnum key) const;
		TEnum operator()(const TValue& value) const;
	};

	// EnumMap::EnumMap
	export template<EnumType TEnum, class TValue>
		EnumMap<TEnum, TValue>::EnumMap(std::initializer_list<std::pair<const TEnum, TValue>> list)
		: std::unordered_map<TEnum, TValue>(list)
	{
	}

	// EnumMap::operator() enum to value
	export template<EnumType TEnum, class TValue>
		inline TValue EnumMap<TEnum, TValue>::operator()(TEnum key) const
	{
		auto iter = this->find(key);
		if (iter != this->end())
		{
			return iter->second;
		}

		throw std::out_of_range("EnumMap: Key not found in EnumMap");
	}

	// EnumMap::operator() value to enum
	export template<EnumType TEnum, class TValue>
		inline TEnum EnumMap<TEnum, TValue>::operator()(const TValue& value) const
	{
		for (const auto& [mapkey, mapvalue] : *this)
		{
			if (mapvalue == value)
			{
				return mapkey;
			}
		}

		throw std::out_of_range("EnumMap: Value not found in EnumMap");
	}
}
