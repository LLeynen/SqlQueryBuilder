// SqlQueryBuilder Class Library
// Copyright (c) 2025-present, Luc Leynen.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

module;

export module QueryBuilder:String;

#ifdef QT
export import :StringQt;
#else
export import :StringStd;
#endif
