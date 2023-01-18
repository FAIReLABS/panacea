#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([panacea], [0.0.0.9000], [https://github.com/FAIReLABS/panacea/issues])
AC_CONFIG_SRCDIR([src/panacea.cpp])
AC_CONFIG_HEADERS([src/config.hpp])

# Checks for programs (compiler and c++11 new standard).
AC_PROG_CXX

# Check for installation tools
AC_PROG_INSTALL

# Checks for libraries.
AC_CHECK_LIB([boost_unit_test_framework], [main])

# Define C macro (initatilze with false).
# AC_DEFINE_UNQUOTED([HAVE_NLOHMANN_JSON_HPP], [0], [Define to 1 if you have `nlohmann/json.hpp'.])

# Checks for header files.
if pkg-config --exists nlohmann_json; then
	# Get include path.
	JSON_CXXFLAGS=$(pkg-config nlohmann_json --cflags)
	# Define C macro.
	AC_DEFINE_UNQUOTED([HAVE_NLOHMANN_JSON_HPP], [1], [Define to 1 if you have `nlohmann/json.hpp'.])
else
	AC_MSG_WARN([
  ------------------------------------------------------------------------
  A full build of nlohmann json is required.

  If you believe nlohmann/json.hpp is present on your system but this script is
  simply unable to find it, you can specify the include manually:
  ./configure CXXFLAGS="-I/path/to/nlohmann/json.hpp"
  ------------------------------------------------------------------------])
fi

# This extra step is needed for the space in between the original and new flags.
CXXFLAGS="${CXXFLAGS} ${JSON_CXXFLAGS}" 

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_STRTOD
AC_CHECK_FUNCS([floor localeconv memmove memset strtoull])

AC_CONFIG_FILES([Doxyfile Makefile src/Makefile test/Makefile])
AC_OUTPUT
