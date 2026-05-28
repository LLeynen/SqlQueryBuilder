// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :Alias;

import std;

import :BuilderTypes;

namespace DataAccessLayer::SqlQueryBuilder
{
	class AliasImpl
	{
	public:
		AliasImpl() = default;

		AliasImpl(String aliasValue, const AliasType aliasType)
			: aliasType_{ aliasType }
			, aliasValue_{std::move( aliasValue )}
		{}

		AliasImpl(const AliasImpl& other) = default;

		AliasImpl(AliasImpl&& other) noexcept
			: aliasType_ { other.aliasType_ }
			, aliasValue_{ std::move(other.aliasValue_) }
		{}

		AliasImpl& operator=(const AliasImpl& other)
		{
			if (this != &other)
			{
				aliasValue_ = other.aliasValue_;
				aliasType_ = other.aliasType_;
			}
			return *this;
		}

		AliasImpl& operator=(AliasImpl&& other) noexcept
		{
			if (this != &other)
			{
				aliasValue_ = std::move(other.aliasValue_);
				aliasType_ = other.aliasType_;
			}
			return *this;
		}

		AliasType aliasType_{};
		String aliasValue_{};
		bool suppressed_{false};
	};


	Alias::Alias() noexcept
		: Component{ ComponentId::Alias }
		, impl_{ std::make_unique<AliasImpl>() }
	{}


	Alias::Alias(String aliasValue)
		: Component { ComponentId::Alias }
		, impl_{ std::make_unique<AliasImpl>(std::move(aliasValue), AliasType::Column) }
	{}


	Alias::~Alias() = default;


	Alias::Alias(const Alias& other)
		: Component(other)
		, impl_{ std::make_unique<AliasImpl>(*other.impl_) }
	{}


	Alias& Alias::operator=(const Alias& other)
	{
		if (this != &other)
		{
			Component::operator=(other);
			impl_ = std::make_unique<AliasImpl>(*other.impl_);
		}

		return *this;
	}


	Alias::Alias(Alias&& other) noexcept
		: Component(std::move(other))
		, impl_{ std::move(other.impl_) }
	{}


	Alias& Alias::operator=(Alias&& other) noexcept
	{
		if (this != &other)
		{
			Component::operator=(std::move(other));
			impl_ = std::move(other.impl_);
		}
		return *this;
	}


	AliasType Alias::aliasType() const noexcept
	{
		return impl_->aliasType_;
	}


	void Alias::setAliasType(const AliasType aliasType) const
	{
		impl_->aliasType_ = aliasType;
	}


	String Alias::value() const noexcept
	{
		return impl_->aliasValue_;
	}


	void Alias::setValue(String value) const
	{
		impl_->aliasValue_ = std::move(value);
	}


	void Alias::suppress(const bool suppress) const noexcept
	{
		impl_->suppressed_ = suppress;
	}


	[[nodiscard]] bool Alias::isSuppressed() const noexcept
	{
		return impl_->suppressed_;
	}


	String Alias::toSql(const IBuilder* builderPtr) const
	{
		return Component::sqlImpl(builderPtr, *this);
	}
}
