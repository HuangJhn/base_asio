
// boost
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
// cpp std
#include <iostream>
#include <thread>

void timer();
void timer_clock();

// test_case 2 helper function
// must is const
void print(const boost::system::error_code & /*error_code*/)
{
    // thread is same
    std::cout << std::this_thread::get_id() << std::endl;
    printf("we care content.\n");
}

// test_case 3 helper function
void print_test_case_3(const boost::system::error_code & ec,boost::asio::steady_timer * timer,int * count)
{
    if(*count <= 5)
    {
        std::cout << "timer count = " << *count << std::endl;
        std::cout << "expiry time min = " << timer->expiry().min << std::endl;
        std::cout << "expiry time max = " << timer->expiry().max << std::endl;

        (*count)++;
        // 以expiry()为基点向后延迟
        timer->expires_at(timer->expiry() + boost::asio::chrono::seconds(2));

        timer->async_wait(boost::bind(print_test_case_3,boost::asio::placeholders::error,timer,count));
    }
}

// function declare
void timer_expiry_count();

int
main(int argc,char * argv[])
{
    // timer();
    // thread is same
    // std::cout << std::this_thread::get_id() << std::endl;
    // timer_clock();

    // test case 3
    timer_expiry_count();
    return EXIT_SUCCESS;    
}
// test_case 1
void timer()
{
    boost::asio::io_context io;
    boost::asio::steady_timer timer(io,boost::asio::chrono::seconds(4));

    timer.wait();
    printf("wait for 4 second for print this line.\n");
}
// test_case 2
// clock 
void
timer_clock()
{
    boost::asio::io_context io;
    boost::asio::steady_timer timer(io,boost::asio::chrono::seconds(3));

    // skil this line and continue execute 
    timer.async_wait(&print);

    std::cout << "test function" << std::endl;

    // block in there because has task is wait  
    io.run();
}

void
timer_expiry_count()
{
    int count = 0;
    boost::asio::io_context io;
    boost::asio::steady_timer timer(io,boost::asio::chrono::seconds(3));

    timer.async_wait(boost::bind(print_test_case_3,boost::asio::placeholders::error,&timer,&count));

    io.run();
}