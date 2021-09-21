
// boost library
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <boost/thread/thread.hpp>

// cpp std
#include <iostream>
#include <string>
#include <memory>
#include <time.h>

// linux
#include <unistd.h>
#include <sys/socket.h>

// gettimeofday
std::string GetTimeOfDay()
{
    time_t time = std::time(0);

    return std::ctime(&time);
}

int
main(int argc,char * argv[])
{
    using namespace boost::asio::ip;

    boost::asio::io_context io;
    // boost::asio::ip::tcp::endpoint endpoint =  boost::asio::ip::tcp::endpoint(tcp::v4(),13);
    boost::asio::ip::tcp::acceptor acceptor(io,tcp::endpoint(tcp::v4(),13));
    for(;;)
    {
        try
        {
            tcp::socket socket(io);
            acceptor.accept(socket);

            boost::system::error_code error;
            // socket.send(getTimeOfDay(),error);
            std::string tm = GetTimeOfDay();

            // boost::asio::write(socket,boost::asio::buffer(tm),error);
            std::cout << tm << std::endl;
            socket.send(boost::asio::buffer(tm));

            socket.close();
        }
        catch(std::exception & ec)
        {
            std::cout << ec.what() << std::endl;
        }
    }

    return EXIT_SUCCESS;
}