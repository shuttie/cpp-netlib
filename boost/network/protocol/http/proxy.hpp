// This file is part of the Boost Network library
// Based on the Pion Network Library (r421)
// Copyright Atomic Labs, Inc. 2007-2008
// See http://cpp-netlib.sourceforge.net for library home page.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_NETWORK_PROTOCOL_HTTP_PROXY_HPP
#define BOOST_NETWORK_PROTOCOL_HTTP_PROXY_HPP

#include <string>

namespace boost { namespace network { namespace http {

class proxy_type {
public:
    proxy_type()
        :port_(0) {}
    proxy_type(std::string const &host, unsigned short port)
        :host_(host), port_(port) {}
    proxy_type(const proxy_type &other) {
        host_ = other.host();
        port_ = other.port();
    }

    ~proxy_type() {}

    unsigned short port() const {
        return port_;
    }

    std::string host() const {
        return host_;
    }

private:
    std::string host_;
    unsigned short port_;
};

} // namespace http

} // namespace network

} // namespace boost

#endif
