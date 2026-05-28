// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module QueryBuilder;

import :Component;

import std;

import :BuilderTypes;
import :IBuilder;

namespace DataAccessLayer::SqlQueryBuilder
{
	class ComponentImpl
	{
		public:
			ComponentImpl() = default;
			ComponentImpl(const ComponentId componentId)
				: componentId_{ componentId }
			{}
			ComponentImpl(const ComponentImpl& other) = default;

			ComponentId componentId_{};
	};


	Component::Component() noexcept
		: impl_{ std::make_unique<ComponentImpl>() }
	{}


	Component::Component(ComponentId componentId) noexcept
		: impl_{ std::make_unique<ComponentImpl>(componentId) }
	{}

	Component::~Component() = default;


	Component::Component(const Component& other)
		: impl_{ std::make_unique<ComponentImpl>(*other.impl_) }
	{}


	Component& Component::operator=(const Component& other)
	{
		if (this != &other)
		{
			impl_ = std::make_unique<ComponentImpl>(*other.impl_);
		}

		return *this;
	}

	Component::Component(Component&&) noexcept = default;

	Component& Component::operator=(Component&&) noexcept = default;


	ComponentId Component::componentId() const noexcept
	{
		return impl_->componentId_;
	}
}
