//            Copyright (c) Glyn Matthews 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


//[ hello_world_client_main
/*`
  This is a part of the 'Hello World' example.  We create a client
  object and make a single HTTP request.  If we use make this request
  to the `hello_world_server`, then the output is simply "Hello,
  World!".
 */
#include <boost/network/protocol/http/client.hpp>
#include <boost/network/protocol/http/proxy.hpp>
#include <iostream>


namespace http = boost::network::http;
typedef http::basic_client<http::tags::http_async_8bit_tcp_resolve, 1, 1> http_client;
int
main(int argc, char *argv[]) {
    
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " proxy port url" << std::endl;
        return 1;
    }

    try {
        int port = boost::lexical_cast<int>(argv[2]);
        /*<< Creates the client. >>*/
        http_client client(http::_follow_redirects=true/*, http::_proxy=http::proxy_type(argv[1], port)*/);
        /*<< Creates a request using a URI supplied on the command
             line. >>*/
        http_client::request request(argv[3]);
        /*<< Gets a response from the HTTP server. >>*/
        http_client::response response = client.get(request);
        /*<< Prints the response body to the console. >>*/
        std::cout << body(response) << std::endl;
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
//]
