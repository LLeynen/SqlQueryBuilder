// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

#ifdef QT
#include <QString>
#include <QHash>
#endif

export module QueryBuilder:StringQt;

import  <functional>;

#ifdef QT

namespace DataAccessLayer::SqlQueryBuilder
{
	// String class
	export class String : public QString
	{
	public:
		String() = default;
		String(char* str)
			: QString(str)
		{}
		String(const char* str)
			: QString(str)
		{}
		String(std::string_view str)
			: QString(str.data())
		{}
		String(QString& str)
			: QString(str)
		{}
		String(const QString& str)
			: QString(str)
		{}
		String(const int v)
			: QString()
		{
			setNum(v);
		}
		String(const long v)
			: QString()
		{
			setNum(v);
		}
		String(const double v)
			: QString()
		{
			setNum(v);
		}
		String(const bool v)
			: QString()
		{
			*this = v ? "true" : "false";
		}
		bool empty() const
		{
			return QString::isEmpty();
		}
		size_t find(const char c) const
		{
			return static_cast<size_t>(QString::indexOf(c));
		}
	};

	// toString template function
    export template <typename T>
		requires
	std::is_integral_v<T> ||
		std::is_floating_point_v<T>
		String toString(T value)
	{
		return QString::number(value);
	}

	// npos replacement for std::npos
    export constexpr size_t npos = -1;

	// Exported operator+ overloads so module consumers don't have to include QString
	export inline String operator+(const String& a, const char* b)
	{
		return String(QString(a) + QString::fromUtf8(b));
	}

	export inline String operator+(const char* a, const String& b)
	{
		return String(QString::fromUtf8(a) + QString(b));
	}

	export inline String operator+(const String& a, const String& b)
	{
		return String(QString(a) + QString(b));
	}

    // Optionally provide += for convenience (fixes overload resolution with literals)
	export inline String& operator+=(String& a, const String& b)
	{
		a = String(QString(a) + QString(b));
		return a;
	}

    // Handle appending C-strings (literals) directly to avoid ambiguous overloads
    export inline String& operator+=(String& a, const char* b)
    {
        a = a + b;
        return a;
    }

    // Handle appending single characters
    export inline String& operator+=(String& a, char c)
    {
        a = a + String(QString(c));
        return a;
    }
}

// Specialization of std::hash for String,
// allowing use of Qt String in STL unordered containers
namespace std
{
	namespace Sql = DataAccessLayer::SqlQueryBuilder;

	template<>
	struct hash<Sql::String>
	{
		std::size_t operator()(const Sql::String& s) const noexcept
		{
			const QByteArray utf8 = s.toUtf8();
			const char* str = utf8.constData();
			std::size_t hash = 5381;
			int c;
			while ((c = *str++))
			{
				hash = ((hash << 5) + hash) + c; // hash * 33 + c
			}
			return hash;
		}
	};
}

#endif
