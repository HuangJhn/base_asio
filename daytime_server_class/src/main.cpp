
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include <vector>
#include <iostream>
#include <string>
#include <ctime>

#include <stdint.h>

// 等待socket套接字被填上
class Connection
{
public:
    // 最好是使用智能指针
    static std::shared_ptr<Connection> Instance(boost::asio::io_context & io)
    {
        // static Connection * conn = new Connection(io);
        // return conn;
        return std::shared_ptr<Connection>(new Connection(io));
    }
    Connection(boost::asio::io_context & io):_socket(io)
    {

    }
    boost::asio::ip::tcp::socket & socket()
    {
        return this->_socket;
    }
    void start()
    {
        std::string time = ctime();
        _socket.send(boost::asio::buffer(time));
    }
    void close()
    {
        // close connection
        _socket.close();
    }
private:
    std::string ctime()
    {
        time_t tm = time(NULL);
        return ::ctime(&tm);
    }
private:
    boost::asio::ip::tcp::socket _socket;
};

// 第一步:创建监听套接字 并 监听13端口
// 第二步:开始监听并等待客户端的接入
// 第三步:由创建好的连接来回复时间（后续可以再加一个获取时间并转换为字符串的函数）
class daytime_server
{
public:
    daytime_server(boost::asio::io_context & io):_io_context(io),_acceptor(io, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),13))
    {   
        init();
    }
    ~daytime_server()
    {
        _acceptor.close();
    }
    void init()
    {
        _acceptor.listen();
        start_accept();
    }
    void start_accept()
    {
        std::shared_ptr<Connection> con = Connection::Instance(_io_context);
        _acceptor.async_accept(con->socket(),boost::bind(&daytime_server::handler_func,this,con,boost::asio::placeholders::error));
    }
    void handler_func(std::shared_ptr<Connection> con,const boost::system::error_code & ec)
    {
        if(!ec)
        {
            con->start();
            con->close();
        }
        start_accept();
    }
private:
    boost::asio::io_context & _io_context;
    boost::asio::ip::tcp::acceptor _acceptor;
};

int main(int argc,char * argv[])
{

    boost::asio::io_context io;
    daytime_server server(io);

    io.run();
    return EXIT_SUCCESS;
}
