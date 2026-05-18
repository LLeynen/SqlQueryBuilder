// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :Literal;

import std;

import :BuilderTypes;
import :Selectable;
import :Variant;

namespace DataAccessLayer::SqlQueryBuilder
{
	class LiteralImpl
	{
	public:
		LiteralImpl() = default;

		LiteralImpl(const Variant& value)
			: value_{ value }
		{}

		LiteralImpl(const LiteralImpl& other) = default;

		LiteralImpl(LiteralImpl&& other) noexcept
			: value_{ std::move(other.value_) }
		{}

		LiteralImpl& operator=(const LiteralImpl& other)
		{
			if (this != &other)
			{
				value_ = other.value_;
			}
			return *this;
		}

		LiteralImpl& operator=(LiteralImpl&& other) noexcept
		{
			if (this != &other)
			{
				value_ = std::move(other.value_);
			}
			return *this;
		}

		Variant value_{};
	};


	Literal::Literal() noexcept
		: Selectable{ ComponentId::Literal }
		, impl_{ std::make_unique<LiteralImpl>() }
	{}


	Literal::Literal(const Variant& value, std::optional<Alias> alias)
		: Selectable{ ComponentId::Literal }
		, impl_{ std::make_unique<LiteralImpl>(value) }
	{
		Selectable::setAlias(std::move(alias));
	}


	Literal::~Literal() = default;


	Literal::Literal(const Literal& other)
		: Selectable(other)
		, impl_{ std::make_unique<LiteralImpl>(*other.impl_) }
	{}


	Literal& Literal::operator=(const Literal& other)
	{
		if (this != &other)
		{
			Selectable::operator=(other);
			impl_ = std::make_unique<LiteralImpl>(*other.impl_);
		}

		return *this;
	}


	Literal::Literal(Literal&& other) noexcept
		: Selectable(std::move(other))
		, impl_{ std::move(other.impl_) }
	{}


	Literal& Literal::operator=(Literal&& other) noexcept
	{
		if (this != &other)
		{
			Selectable::operator=(std::move(other));
			impl_ = std::move(other.impl_);
		}
		return *this;
	}


	SelectablePtr Literal::clone() const
	{
		return std::make_shared<Literal>(*this);
	}


	const Variant& Literal::value() const noexcept
	{
		return impl_->value_;
	}


	void Literal::setValue(const Variant& value) const
	{
		impl_->value_ = value;
	}


	String Literal::toSql(const IBuilder* builderPtr) const
	{
		return Component::sqlImpl(builderPtr, *this);
	}
}
