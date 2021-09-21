
// boost 
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread/thread.hpp>

// cpp std
#include <iostream>
#include <thread>

class Printer
{
public:
    Printer(boost::asio::io_context & io):_strand(boost::asio::make_strand(io)),
        _timer1(io,boost::asio::chrono::seconds(1)),
        _timer2(io,boost::asio::chrono::seconds(1)),
        _timer3(io,boost::asio::chrono::seconds(1))
    {
        _timer1.async_wait(boost::asio::bind_executor(_strand,boost::bind(&Printer::print1,this)));
        _timer2.async_wait(boost::asio::bind_executor(_strand,boost::bind(&Printer::print2,this)));
        _timer3.async_wait(boost::asio::bind_executor(_strand,boost::bind(&Printer::print3,this)));
    }
    void print1()
    {
        if(_count < 10)
        {
            _count++;
            // print thread id
            std::cout << "print-1 thread id = " << boost::this_thread::get_id() << std::endl;
            _timer1.expires_at(_timer1.expiry() + boost::asio::chrono::seconds(1));
            _timer1.async_wait(boost::asio::bind_executor(_strand,boost::bind(&Printer::print1,this)));
        }
    }
    void print2()
    {
        if(_count < 10)
        {
            _count++;
            std::cout << "print-2 thread id = " << boost::this_thread::get_id() << std::endl;
            _timer2.expires_at(_timer2.expiry() + boost::asio::chrono::seconds(1));
            _timer2.async_wait(boost::asio::bind_executor(_strand,boost::bind(&Printer::print2,this)));
        }
    }
    void print3()
    {
        if(_count < 10)
        {
            _count++;
            std::cout << "print-3 thread id = " << boost::this_thread::get_id() << std::endl;
            _timer3.expires_at(_timer3.expiry() + boost::asio::chrono::seconds(1));
            _timer3.async_wait(boost::asio::bind_executor(_strand,boost::bind(&Printer::print3,this)));
        }
    }
    ~Printer()
    {
        std::cout << "destory function" << std::endl;
    }
private:
    boost::asio::strand<boost::asio::io_context::executor_type> _strand;    // 执行器 主要的管理者还是io_context
    boost::asio::steady_timer _timer1;
    boost::asio::steady_timer _timer2;
    // extra add timer
    boost::asio::steady_timer _timer3;
    int _count{0};
};

int
main(int argc,char * argv[])
{
    std::cout << "main thread id = " << boost::this_thread::get_id() << std::endl;
    boost::asio::io_context io;
    Printer p(io);
    // 多线程运行io对象的run函数，导致绑定在io对象的异步调用函数会随机分配在两个线程上面
    boost::thread t(boost::bind(&boost::asio::io_context::run, &io));
    io.run();
    t.join();

    return EXIT_SUCCESS;
}