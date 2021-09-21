
// boost asio
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
// cpp thread
#include <thread>
#include <iostream>

class Timer
{
public:
    Timer(boost::asio::io_context & io):_timer(io,boost::asio::chrono::seconds(1))
    {
        _timer.async_wait(boost::bind(&Timer::print,this,boost::asio::placeholders::error));
    }
    ~Timer()
    {
        printf("~timer.\n");
    }
    void print(const boost::system::error_code & ec)
    {   
        if(_count < 5)
        {
            printf("_count = %d.\n",_count++);
            std::cout << "this thread id = " << std::this_thread::get_id() << std::endl;
            _timer.expires_at(_timer.expiry() + boost::asio::chrono::seconds(1));
            _timer.async_wait(boost::bind(&Timer::print,this,boost::asio::placeholders::error));
        }
    }
private:
    boost::asio::steady_timer _timer;
    int _count;
};


class DoubleTimer
{
public:
    DoubleTimer(boost::asio::io_context & io):_timer1(io,boost::asio::chrono::seconds(1)),_timer2(io,boost::asio::chrono::seconds(1))
    {
        _timer1.async_wait(boost::bind(&DoubleTimer::print1,this));
        _timer2.async_wait(boost::bind(&DoubleTimer::print2,this));
    }  
    void print1()
    {
        if(_count1 < 10)
        {
            std::cout << "timer 1 thread id = " << std::this_thread::get_id() << std::endl;
            _timer1.expires_at(_timer1.expiry() + boost::asio::chrono::seconds(1));
            _timer1.async_wait(boost::bind(&DoubleTimer::print1,this));
            // std::this_thread::sleep_for(std::chrono::seconds(4));
            _count1++;
        }
    }
    void print2()
    {
        if(_count2 < 10)
        {
            std::cout << "timer 2 thread id = " << std::this_thread::get_id() << std::endl;
            _timer2.expires_at(_timer2.expiry() + boost::asio::chrono::seconds(1));
            _timer2.async_wait(boost::bind(&DoubleTimer::print2,this));

            _count2++;
        }
    }
private:
    boost::asio::steady_timer _timer1;
    boost::asio::steady_timer _timer2;

    int _count1{0};
    int _count2{0};
};

int
main(int argc,char * argv[])
{
    // now thread id is same
    std::cout << "main thread id = " << std::this_thread::get_id() << std::endl;
    boost::asio::io_context io;
    // Timer timer(io);
    DoubleTimer timer(io);

    printf("waiting.\n");
    io.run();
    return EXIT_SUCCESS;
}

