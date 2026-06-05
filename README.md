# SqlQueryBuilder

A modern, lightweight, and type-safe C++20/C++23 SQL query builder designed for seamless data access layer integration. 
Built from the ground up to leverage modern C++ paradigms, it eliminates raw string concatenation errors and provides a fluent, intuitive API for constructing complex queries.

## Features

* **Modern C++ Architecture:** Fully embraces C++20/C++23 standards, optimized for standard library modules (`import std;`).
* **Header-Free Design:** Engineered to minimize compile-time overhead and maintain perfectly synchronized, clean source structures across platforms.
* **Fluent API:** Construct `SELECT`, `INSERT`, `UPDATE`, and `DELETE` statements using a highly readable, chained syntax.
* **Advanced Query Support:** Seamlessly handles subqueries as selectables, explicit field criteria, filters and complex joins.
* **Cross-Platform & Toolkit Agnostic:** Designed to easily map results to local UI widgets, object-relational models, or frameworks like Qt (e.g., integrating with custom SQL models).

---

## 🚀 Getting Started

### Prerequisites

* **Compiler:** A compiler with robust C++20/C++23 support (MSVC 2022, GCC 13+, or Clang 16+).
* **Build System:** CMake 3.26+ recommended.

### Installation & Integration

Since `SqlQueryBuilder` utilizes modern C++ module workflows, you can drop the source directly into your CMake project:

### cmake
#### CMakeLists.txt snippet
add_library(SqlQueryBuilder)
target_sources(SqlQueryBuilder 
    PUBLIC 
        FILE_SET CXX_MODULES FILES 
            SqlQueryBuilder.ixx # Or your specific module interface file
)

target_compile_features(SqlQueryBuilder PUBLIC cxx_std_23)

# Usage Examples
1. Basic SELECT Query
Constructing a clean query with explicit field criteria:

'''import SqlQueryBuilder;
import std;

int main() 
{
        QueryBuilder sqlTest{ SelectQuery };

        sqlTest
            .from("Investment", as("Inv"))
            .fields({ {"InvestmentId"}, {"InvestmentName"} })
            .field ({"Symbol"})
            .sum({"Value"}, as("TheValue"))
            .where({"Symbol"}, Equals, "AMZN");

        const String sql = sqlTest.sql();

        std::cout << "sql = " << sql << std::endl;

    // Output: SELECT `InvestmentId`, `InvestmentName`, `Symbol`, SUM(`Value`) AS TheValue 
    // FROM `investment` AS Inv
    // WHERE `Symbol` = 'AMZN'
}

2. Complex Subqueries
SqlQueryBuilder allows you to treat subqueries as distinct selectable entities:

    subQuery
        .from("permissions")
        .field({"user_id"})
        .where("access_level", GreaterThan, 5);

    mainQuery
        .from("users")
        .fields({"name", "email"})
        .where("id", In, subQuery);

    // Output: SELECT name, email FROM users WHERE id IN (SELECT user_id FROM permissions WHERE access_level > 5);

# Building & Testing
To build the library locally and run the test suite:
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .


# License
This project is licensed under the MIT License - see the LICENSE file for details.
