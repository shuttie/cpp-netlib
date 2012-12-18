#            Copyright (c) Dean Michael Berris 2010.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 2.8)
project(CPP-NETLIB)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTI_THREADED ON)
find_package( Boost 1.45.0 REQUIRED unit_test_framework system regex date_time thread filesystem program_options )
find_package( OpenSSL )
find_package( Threads )
set(CMAKE_VERBOSE_MAKEFILE true)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DBOOST_NETWORK_DEBUG)
endif()

if (OPENSSL_FOUND)
    add_definitions(-DBOOST_NETWORK_ENABLE_HTTPS)
endif()

if (Boost_FOUND)
    if (MSVC)
      add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    endif(MSVC)
    if (WIN32)
      add_definitions(-D_WIN32_WINNT=0x0501)
    endif(WIN32)
    include_directories(${Boost_INCLUDE_DIRS})
    enable_testing()
    add_subdirectory(libs/network/src)
    if(CPP-NETLIB_BUILD_TESTS)
      add_subdirectory(libs/network/test)
    endif(CPP-NETLIB_BUILD_TESTS)
    if (NOT MSVC)
      if(CPP-NETLIB_BUILD_TESTS)
        add_subdirectory(libs/mime/test)
      endif(CPP-NETLIB_BUILD_TESTS)
    endif(NOT MSVC)
    if(CPP-NETLIB_BUILD_EXAMPLES)
      add_subdirectory(libs/network/example)
    endif(CPP-NETLIB_BUILD_EXAMPLES)
endif(Boost_FOUND)

if(CPP-NETLIB_BUILD_TESTS)
  enable_testing()
endif()

message(STATUS "CPP-NETLIB Options selected:")
message(STATUS "  CPP-NETLIB_BUILD_SHARED_LIBS: ${CPP-NETLIB_BUILD_SHARED_LIBS}\t(Build cpp-netlib as shared libraries: OFF, ON)")
message(STATUS "  CPP-NETLIB_BUILD_TESTS:       ${CPP-NETLIB_BUILD_TESTS}\t(Build the unit tests: ON, OFF)")
message(STATUS "  CPP-NETLIB_BUILD_EXAMPLES:    ${CPP-NETLIB_BUILD_EXAMPLES}\t(Build the examples using cpp-netlib: ON, OFF)")
message(STATUS "  CPP-NETLIB_ALWAYS_LOGGING:    ${CPP-NETLIB_ALWAYS_LOGGING}\t(Allow cpp-netlib to log debug messages even in non-debug mode: ON, OFF)")
message(STATUS "  CPP-NETLIB_DISABLE_LOGGING:   ${CPP-NETLIB_DISABLE_LOGGING}\t(Disable logging definitely, no logging code will be generated or compiled: ON, OFF)")

set(CPP-NETLIB_HEADERS include/network.hpp)

