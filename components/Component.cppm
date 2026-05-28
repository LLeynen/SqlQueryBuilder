// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:Component;

import std;

import :BuilderTypes;
import :IBuilder;
import :BuilderFactory;

namespace DataAccessLayer::SqlQueryBuilder
{
	class ComponentImpl;

	export class Component
	{
	public:
		Component() noexcept;
		Component(ComponentId componentId) noexcept;
		virtual ~Component();

		Component(const Component&);
		Component& operator=(const Component&);
		Component(Component&&) noexcept ;
		Component& operator=(Component&&) noexcept ;

		[[nodiscard]] ComponentId componentId() const noexcept;

		String sql(const IBuilder* builderPtr = nullptr) const
		{
			return toSql(builderPtr);
		}

	protected:
		virtual String toSql(const IBuilder* builderPtr) const = 0;

		template<typename T>
		static String sqlImpl(const IBuilder* builderPtr, const T& componentRef)
		{
			auto builder = builderPtr ? builderPtr : defaultBuilder().get();

			if (!builder)
			{
				throw std::runtime_error("Component::sqlImpl() - No builder available");
			}
			
			return builder->buildComponent(componentRef);
		}

	private:
		std::unique_ptr<ComponentImpl> impl_;
	};
}
