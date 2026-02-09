#pragma once

#include <iostream>
#include <sstream>

#define PRINT(expr) \
  INFO("  ", #expr, ": ", (expr))

#define ERROR(...) \
  ERROR_impl(__FILE__, __LINE__, __VA_ARGS__)

#define ASSERT(expr, ...) \
  if (! (expr)) \
    ASSERT_impl(__FILE__, __LINE__, #expr, ##__VA_ARGS__)

template<typename... Args>
void INFO(Args&&... args) {

  std::ostringstream oss;

  (oss << ... << args);

  std::cout << "[INFO] " << oss.str() << std::endl;

}

template<typename... Args>
void ERROR_impl(const char* file, int line, Args&&... args) {

 std::ostringstream oss;

 (oss << ... << args);

 std::cerr << "[ERROR] " 
   << " (file " << file << ", line " << line << ")" << std::endl
   << oss.str() << std::endl;

 std::abort();

}

template<typename... Args>
void ASSERT_impl(const char* file, int line, const char * expr, Args&&... args) {

 std::ostringstream oss;

 if constexpr (sizeof...(args) > 0)
  (oss << ... << args);

 std::cerr << "[ASSERT failed] " 
   << expr
   << " (file " << file << ", line " << line << ")" << std::endl
   << oss.str() << std::endl;

 std::abort();

}
