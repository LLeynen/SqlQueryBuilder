// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:Function;

import std;

import :BuilderTypes;
import :Selectable;
import :Literal;
import :Operand;

namespace DataAccessLayer::SqlQueryBuilder
{
	class FunctionImpl;

	export class Function : public Selectable
	{
	public:

		Function() noexcept;
//		Function(ScalarFunction scalarFunction, std::initializer_list<FormulaArg> args, std::optional<Alias> alias = std::nullopt) noexcept;
		Function(ScalarFunction scalarFunction, std::vector<FormulaArg> args, std::optional<Alias> alias = std::nullopt) noexcept;
		~Function() override;

		Function(const Function& other);
		Function& operator=(const Function& other);
		Function(Function&&) noexcept;
		Function& operator=(Function&&) noexcept;

		[[nodiscard]] ScalarFunction function() const noexcept;
		[[nodiscard]] std::vector<FormulaArg>& arguments() const noexcept;
//		void setFunction(ScalarFunction scalarFunction) const noexcept;
//		[[nodiscard]] SelectableList selectableList() const noexcept;
//		void setSelectableList(SelectableList selectableList) const noexcept;

		[[nodiscard]] SelectablePtr clone() const override;

	protected:
		String toSql(const IBuilder* builderPtr) const override;

	private:
		std::unique_ptr<FunctionImpl> impl_{};
	};

	/*
	export template <typename... Args>
	[[nodiscard]] std::shared_ptr<Function> func(ScalarFunction scalarFunction, Args&&... args)
	{
		return std::make_shared<Function>(scalarFunction, std::vector<FormulaArg>{std::forward<Args>(args)...});
	}
*/
}
