project(opengl-tutorial)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Easy way to detect 32/64bit build target
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(OGLTUTOR_TARGET_ARCH "x86-64")
else ()
  set(OGLTUTOR_TARGET_ARCH "x86-32")
endif()

# Global options

option(OGLTUTOR_STATIC "Build opengl-tutorial statically (on Unix, it will still be dynamically linked to glibc and window manager libs)" OFF)

if (OGLTUTOR_STATIC)

  if (UNIX OR MINGW)
    list(APPEND CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
  elseif (MSVC)
    # Use /MT (static runtime) instead of /MD project-wide
    foreach (flag
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_MINSIZEREL
        CMAKE_C_FLAGS_RELWITHDEBINFO
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL
        CMAKE_CXX_FLAGS_RELWITHDEBINFO
        )

      if (${flag} MATCHES "/MD")
        string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
      endif()
      if (${flag} MATCHES "/MDd")
        string(REGEX REPLACE "/MDd" "/MTd" ${flag} "${${flag}}")
      endif()

    endforeach()
  endif()
  
endif(OGLTUTOR_STATIC)

# Find and/or build dependencies

include(dependencies)

# Main sources

add_subdirectory(src)

# Packaging with CPack
include(package)
