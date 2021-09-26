
// boost asio
#include <boost/asio.hpp>
#include <boost/bind.hpp>

// cpp std
#include <iostream>
#include <string.h>
#include <functional>

class ClockTimer
{
public:
    ClockTimer(const int count, boost::asio::io_context &);
    void second_timer(const boost::system::error_code & ec);
private:
    int _count;
    boost::asio::steady_timer _timer;
};

ClockTimer::ClockTimer(const int count, boost::asio::io_context &io) : _count(count), _timer(io, boost::asio::chrono::seconds(1))
{
    _timer.async_wait(boost::bind(&ClockTimer::second_timer, this,boost::asio::placeholders::error));
}
void ClockTimer::second_timer(const boost::system::error_code & ec)
{
    _count--;
    if (_count == 0)
    {
        printf("time out.\n");
        return;
    }
    _timer.expires_at(_timer.expiry() + boost::asio::chrono::seconds(1));
    _timer.async_wait(boost::bind(&ClockTimer::second_timer, this,boost::asio::placeholders::error));
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("need a number.\n");
        return EXIT_FAILURE;
    }
    int number = atoi(argv[1]);
    boost::asio::io_context io;
    ClockTimer t(number,io);
    io.run();   // must;
    return EXIT_SUCCESS;
}