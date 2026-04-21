AC_INIT([ramiga], m4_esyscmd_s([awk '/^Version:/ {print $2}' DESCRIPTION]))

# 1. Determine R_HOME and compiler settings
: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  AC_MSG_ERROR([Could not determine R_HOME. Is R installed?])
fi

CC=`"${R_HOME}/bin/R" CMD config CC`
CFLAGS=`"${R_HOME}/bin/R" CMD config CFLAGS`
CPPFLAGS=`"${R_HOME}/bin/R" CMD config CPPFLAGS`

# 2. macOS-specific type fixes (your original logic)
if test `uname` = "Darwin"; then
  AC_MSG_NOTICE([Applying macOS-specific type fixes to src/cpp11.cpp...])
  sed -i '' 's/R_useDynamicSymbols(dll, FALSE)/R_useDynamicSymbols(dll, (Rboolean)0)/g' src/cpp11.cpp
  sed -i '' 's/R_forceSymbols(dll, TRUE)/R_forceSymbols(dll, (Rboolean)1)/g' src/cpp11.cpp
fi

# 3. Handle zlib dependency
PKG_PROG_PKG_CONFIG
PKG_LIBS_EXTRA=""

if test -n "$PKG_CONFIG"; then
  AC_MSG_CHECKING([for zlib via pkg-config])
  if $PKG_CONFIG --exists zlib; then
    AC_MSG_RESULT([yes])
    PKG_CPPFLAGS=`$PKG_CONFIG --cflags zlib`
    PKG_LIBS_EXTRA=`$PKG_CONFIG --libs zlib`
  else
    AC_MSG_RESULT([no])
  fi
fi

# Fallback check if pkg-config fails
if test -z "$PKG_LIBS_EXTRA"; then
  AC_CHECK_LIB([z], [deflate], [PKG_LIBS_EXTRA="-lz"], [
    AC_MSG_ERROR([zlib library not found. Please install zlib1g-dev (Ubuntu) or zlib (macOS).])
  ])
fi

# 4. Find source files and include paths (your original logic)
# Note: We use shell commands within the script to populate variables
RAMIGA_INCLUDES=$(find src -mindepth 1 -type d | grep -v "utlib/include/utl" | grep -v "utlib/src" | sed 's|^src/|-I./|' | tr '\n' ' ' | tr -s ' ')
RAMIGA_CFILES=$(cd src && find . -type f -name "*.c" | sed 's|^src/||' | tr '\n' ' ')
RAMIGA_CPPFILES=$(cd src && find . -type f -name "*.cpp" | sed 's|^src/||' | tr '\n' ' ')

# 5. Export variables to Makevars.in
AC_SUBST(RAMIGA_CFILES)
AC_SUBST(RAMIGA_CPPFILES)
RAMIGA_FLAGS="" # Defined in your original script
AC_SUBST(RAMIGA_FLAGS)
AC_SUBST(RAMIGA_INCLUDES)
AC_SUBST(PKG_LIBS_EXTRA)
AC_SUBST(PKG_CPPFLAGS)

AC_CONFIG_FILES([src/Makevars])
AC_OUTPUT
