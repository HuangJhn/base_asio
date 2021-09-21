// boost
#include <boost/asio.hpp>
#include <boost/array.hpp>

// cpp std
#include <exception>
#include <iostream>
#include <string>
int
main(int argc,char * argv[])
{
    // need check argc
    boost::asio::io_context io;
    boost::asio::ip::tcp::resolver resolver(io);

    // boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(argv[1],"daytime");

    boost::asio::ip::tcp::endpoint endpoints;
    endpoints.address(boost::asio::ip::address().from_string(argv[1]));
    endpoints.port(boost::asio::ip::port_type(13));

    boost::asio::ip::tcp::socket socket(io);
    // boost::asio::connect(socket, endpoints);
    socket.connect(endpoints);
    for (;;)
    {
	    // boost::array<char, 128> buf;   // ok
        // std::string buf;               // no work
        std::vector<char> buf(120);         // no work
        // char buf[128];					  // ok 
        // bzero(buf,sizeof(buf));
		boost::system::error_code error;

        size_t len = socket.read_some(boost::asio::buffer(buf), error);

        if (error == boost::asio::error::eof)
            break; // Connection closed cleanly by peer.
        else if (error)
            throw boost::system::system_error(error); // Some other error.
		
		// std::cout << "get time = " << buf << std::endl;
	}
    return EXIT_SUCCESS;
}
