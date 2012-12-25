# Copyright (c) Glyn Matthews 2011, 2012.
# Copyright 2011 Dean Michael Berris (dberris@google.com)
# Copyright 2012 A. Joel Lamotte (mjklaim@gmail.com)
# Copyright 2011 Google, Inc.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)


include_directories(${CPP-NETLIB_SOURCE_DIR}/include)
include_directories(${CPP-NETLIB_SOURCE_DIR})
if (OPENSSL_FOUND)
include_directories(${OPENSSL_INCLUDE_DIR})
endif()

if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
  if (HAVE_STD11)
    set(CPP-NETLIB_CXXFLAGS "-Wall -std=c++11")
  elseif (HAVE_STD0X)
    set(CPP-NETLIB_CXXFLAGS "-Wall -std=c++0x")
  endif()
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
  CHECK_CXX_COMPILER_FLAG(-std=c++11 HAVE_STD11)
  set(CPP-NETLIB_CXXFLAGS "-Wall -std=c++11 -stdlib=libc++")
  set(CPP-NETLIB_CXXFLAGS "-Wall -std=c++11 -stdlib=libc++")
endif()

if( CPP-NETLIB_ALWAYS_LOGGING )
  add_definitions( /D NETWORK_ENABLE_LOGGING )
endif()

if( NOT CPP-NETLIB_DISABLE_LOGGING )
  set( CPP-NETLIB_LOGGING_SRCS 
    logging/logging.cpp 
  )
  add_library(cppnetlib-logging ${CPP-NETLIB_LOGGING_SRCS})
  foreach (src_file ${CPP-NETLIB_LOGGING_SRCS})
  if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${src_file}
      PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
  endif()
  endforeach(src_file)
  
  # this library name is defined only if we created the target
  # if not then it will be empty
  set( CPP-NETLIB_LOGGING_LIB cppnetlib-logging )
  
endif()

set(CPP-NETLIB_URI_SRCS uri/uri.cpp uri/schemes.cpp uri/normalize.cpp)
add_library(cppnetlib-uri ${CPP-NETLIB_URI_SRCS})
foreach (src_file ${CPP-NETLIB_URI_SRCS})
if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
endif()
endforeach(src_file)

set(CPP-NETLIB_MESSAGE_SRCS message/message.cpp)
add_library(cppnetlib-message ${CPP-NETLIB_MESSAGE_SRCS})
add_dependencies(cppnetlib-message cppnetlib-uri)
target_link_libraries(cppnetlib-message cppnetlib-uri)
foreach (src_file ${CPP-NETLIB_MESSAGE_SRCS})
if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
endif()
endforeach(src_file)

set(CPP-NETLIB_MESSAGE_DIRECTIVES_SRCS message/directives.cpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/directives/header.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/directives/remove_header.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/directives/header.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/directives/remove_header.hpp)
add_library(cppnetlib-message-directives ${CPP-NETLIB_MESSAGE_DIRECTIVES_SRCS})
foreach (src_file ${CPP-NETLIB_MESSAGE_DIRECTIVES_SRCS})
if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
endif()
endforeach(src_file)

set(CPP-NETLIB_MESSAGE_WRAPPERS_SRCS message/wrappers.cpp)
add_library(cppnetlib-message-wrappers ${CPP-NETLIB_MESSAGE_WRAPPERS_SRCS})
foreach (src_file ${CPP-NETLIB_MESSAGE_WRAPPERS_SRCS})
if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
endif()
endforeach(src_file)

set(CPP-NETLIB_HTTP_MESSAGE_SRCS http/request.cpp http/response.cpp)
add_library(cppnetlib-http-message ${CPP-NETLIB_HTTP_MESSAGE_SRCS})
add_dependencies(cppnetlib-http-message
#   ${Boost_LIBRARIES}
  cppnetlib-message)
target_link_libraries(cppnetlib-http-message
  ${Boost_LIBRARIES}
  cppnetlib-message)
foreach (src_file ${CPP-NETLIB_HTTP_MESSAGE_SRCS})
if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
endif()
endforeach(src_file)

set(CPP-NETLIB_HTTP_MESSAGE_WRAPPERS_SRCS http/message/wrappers.cpp)

add_library(cppnetlib-http-message-wrappers ${CPP-NETLIB_HTTP_MESSAGE_WRAPPERS_SRCS})
foreach (src_file ${CPP-NETLIB_HTTP_MESSAGE_WRAPPERS_SRCS})
if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
endif()
endforeach(src_file)

set(CPP-NETLIB_HTTP_SERVER_PARSERS_SRCS server_request_parsers_impl.cpp)
add_library(cppnetlib-http-server-parsers ${CPP-NETLIB_HTTP_SERVER_PARSERS_SRCS})
foreach (src_file ${CPP-NETLIB_HTTP_SERVER_PARSERS_SRCS})
if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
endif()
endforeach(src_file)

set(CPP-NETLIB_HTTP_SERVER_SRCS
    http/server_async_impl.cpp
    http/server_options.cpp
    http/server_socket_options_setter.cpp
    http/server_sync_impl.cpp)
add_library(cppnetlib-http-server ${CPP-NETLIB_HTTP_SERVER_SRCS})
add_dependencies(cppnetlib-http-server
  ${CPP-NETLIB_LOGGING_LIB}
  cppnetlib-constants
  cppnetlib-uri
  cppnetlib-message
  cppnetlib-message-wrappers
  cppnetlib-message-directives
  cppnetlib-http-message
  cppnetlib-http-message-wrappers
  cppnetlib-http-server-parsers
  cppnetlib-utils-thread_pool
  )
target_link_libraries(cppnetlib-http-server
  ${Boost_LIBRARIES}
  ${CPP-NETLIB_LOGGING_LIB}
  cppnetlib-constants
  cppnetlib-uri
  cppnetlib-message
  cppnetlib-message-wrappers
  cppnetlib-message-directives
  cppnetlib-http-message
  cppnetlib-http-message-wrappers
  cppnetlib-http-server-parsers
  cppnetlib-utils-thread_pool
  )
foreach (src_file ${CPP-NETLIB_HTTP_SERVER_SRCS})
if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
endif()
endforeach(src_file)

set(CPP-NETLIB_HTTP_CLIENT_CONNECTIONS_SRCS
    http/client_connections.cpp
    http/simple_connection_manager.cpp
    http/simple_connection_factory.cpp
    http/connection_delegate_factory.cpp
    http/client_resolver_delegate.cpp
    http/client_resolver_delegate_factory.cpp
    http/client_connection_delegates.cpp
    http/client_connection_factory.cpp
    http/client_async_resolver.cpp
    http/client_connection_normal.cpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/constants.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/constants.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/detail/debug.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/detail/directive_base.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/detail/wrapper_base.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/http/client.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/http/errors.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/http/request.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/http/response.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/include/http/client.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/include/http/server.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/include/message.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/logging/logging.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/basic_message.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/basic_message.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/directives.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/directives/detail/string_directive.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/directives/detail/string_value.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/directives/header.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/directives/header.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/directives/remove_header.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/directives/remove_header.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/message.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/message.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/message_base.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/message_base.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/message_concept.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/modifiers.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/modifiers/add_header.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/modifiers/body.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/modifiers/clear_headers.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/modifiers/destination.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/modifiers/remove_header.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/modifiers/source.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/transformers.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/transformers/selectors.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/transformers/to_lower.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/transformers/to_upper.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/wrappers.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/wrappers/body.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/wrappers/body.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/wrappers/destination.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/wrappers/destination.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/wrappers/headers.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/wrappers/headers.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/wrappers/source.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message/wrappers/source.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/message_fwd.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/algorithms/linearize.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/base.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/base.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/client_connection.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/client_connection.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/async_normal.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/async_normal.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/async_protocol_handler.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/async_resolver.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/async_resolver.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/connection_delegate.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/connection_delegate_factory.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/connection_delegate_factory.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/connection_factory.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/connection_factory.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/normal_delegate.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/normal_delegate.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/resolver_delegate.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/resolver_delegate.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/resolver_delegate_factory.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/resolver_delegate_factory.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/simple_connection_factory.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/simple_connection_factory.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/ssl_delegate.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/ssl_delegate.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/sync_base.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/sync_normal.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection/sync_ssl.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection_manager.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/connection_manager.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/facade.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/facade.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/macros.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/options.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/options.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/parameters.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/pimpl.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/simple_connection_manager.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/simple_connection_manager.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client/sync_impl.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/client_fwd.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/errors.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/impl/access.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/impl/access.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/impl/message.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/impl/parser.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/impl/request.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/impl/request_parser.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/impl/response.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/async_message.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/directives.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/directives/major_version.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/directives/method.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/directives/minor_version.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/directives/status.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/directives/status_message.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/directives/uri.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/directives/version.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/header.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/header/name.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/header/value.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/header_concept.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/modifiers.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/modifiers/major_version.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/modifiers/method.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/modifiers/minor_version.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/modifiers/status.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/modifiers/status_message.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/modifiers/uri.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/modifiers/version.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/anchor.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/anchor.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/helper.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/host.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/host.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/major_version.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/method.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/minor_version.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/path.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/path.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/port.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/port.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/protocol.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/query.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/query.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/ready.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/status.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/status.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/status_message.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/status_message.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/uri.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/uri.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/version.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/message/wrappers/version.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/parser.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/parser/incremental.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/policies/async_connection.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/policies/async_connection.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/request.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/request/request.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/request/request.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/request/request_base.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/request/request_base.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/request/request_concept.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/request_parser.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/response.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/response/response.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/response/response.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/response/response_base.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/response/response_base.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/response/response_concept.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/server.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/server/async_impl.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/server/async_impl.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/server/async_server.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/server/connection/async.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/server/connection/sync.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/server/impl/parsers.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/server/impl/socket_options_setter.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/server/impl/socket_options_setter.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/server/options.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/server/options.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/server/parameters.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/server/request.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/server/request_parser.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/server/server.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/server/socket_options_base.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/server/storage_base.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/server/sync_impl.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/server/sync_impl.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/server/sync_server.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/support/client_or_server.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/support/is_client.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/support/is_http.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/support/is_keepalive.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/support/is_server.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/support/is_simple.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/protocol/http/support/sync_only.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/uri.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/uri/accessors.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/uri/builder.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/uri/config.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/uri/decode.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/uri/detail/uri_parts.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/uri/directives.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/uri/directives/authority.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/uri/directives/fragment.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/uri/directives/host.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/uri/directives/path.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/uri/directives/port.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/uri/directives/query.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/uri/directives/scheme.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/uri/directives/user_info.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/uri/encode.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/uri/normalize.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/uri/schemes.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/uri/uri.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/uri/uri.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/uri/uri_io.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/utils/thread_pool.hpp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/utils/thread_pool.ipp
    ${CPP-NETLIB_SOURCE_DIR}/include/network/version.hpp
    )
add_library(cppnetlib-http-client-connections ${CPP-NETLIB_HTTP_CLIENT_CONNECTIONS_SRCS})
foreach (src_file ${CPP-NETLIB_HTTP_CLIENT_CONNECTIONS_SRCS})
if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
endif()
endforeach(src_file)

set(CPP-NETLIB_HTTP_CLIENT_SRCS
    http/client.cpp)
add_library(cppnetlib-http-client ${CPP-NETLIB_HTTP_CLIENT_SRCS})
add_dependencies(cppnetlib-http-client
  ${CPP-NETLIB_LOGGING_LIB}
  cppnetlib-constants
  cppnetlib-uri
  cppnetlib-message
  cppnetlib-message-wrappers
  cppnetlib-message-directives
  cppnetlib-http-message
  cppnetlib-http-message-wrappers
  cppnetlib-http-client-connections
  )
target_link_libraries(cppnetlib-http-client
  ${Boost_LIBRARIES}
  ${CPP-NETLIB_LOGGING_LIB}
  cppnetlib-constants
  cppnetlib-uri
  cppnetlib-message
  cppnetlib-message-wrappers
  cppnetlib-message-directives
  cppnetlib-http-message
  cppnetlib-http-message-wrappers
  cppnetlib-http-client-connections
  )
foreach (src_file ${CPP-NETLIB_HTTP_CLIENT_SRCS})
if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
endif()
endforeach(src_file)

set(CPP-NETLIB_UTILS_THREAD_POOL_SRCS utils/thread_pool.cpp)
add_library(cppnetlib-utils-thread_pool ${CPP-NETLIB_UTILS_THREAD_POOL_SRCS})
foreach (src_file ${CPP-NETLIB_UTILS_THREAD_POOL_SRCS})
if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
endif()
endforeach(src_file)

set(CPP-NETLIB_CONSTANTS_SRCS constants.cpp)
add_library(cppnetlib-constants ${CPP-NETLIB_CONSTANTS_SRCS})
foreach (src_file ${CPP-NETLIB_CONSTANTS_SRCS})
if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set_source_files_properties(${src_file}
        PROPERTIES COMPILE_FLAGS ${CPP-NETLIB_CXXFLAGS})
endif()
endforeach(src_file)
