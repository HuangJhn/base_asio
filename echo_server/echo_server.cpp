/**
 * @file echo_server.cpp
 * @author huangj (1435054809@qq.com)
 * @brief 
 * @version 0.1your name
 * @date 2021-09-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */
// boost
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

//cpp std
#include <iostream>
#include <string>
#include <array>

#define BUFFER_SIZE 1460

/**
 * @brief 监听端口和IPV4地址
 * 
 */
void listen(int port);

int
main(int argc,char * argv[])
{
	// 需要输入一个端口
    if (argc != 2)
    {
        std::cout << "Usage : " << argv[0] << " <PORT>" << std::endl;
        return EXIT_FAILURE;
    }
	// 这个转换是可能出错的
    int port = atoi(argv[1]);
	if (port == 0)
	{
		printf("输入的端口 转换错误或者不能输入为0的端口.\n");
		return EXIT_FAILURE;
	}
    listen(port);
    return EXIT_SUCCESS;
}

void listen(int port)
{
    boost::asio::io_context io_context;
    // 创建一个端点
    boost::asio::ip::tcp::endpoint end(boost::asio::ip::tcp::v4(), port);

    // 创建一个监听者
    boost::asio::ip::tcp::acceptor acceptor(io_context, end);
    // buffer
    // std::array<char, BUFFER_SIZE> array;
    std::string message;
	std::size_t len = 0;
    (void)len;

    // iterator server
accept:
    // std::array<char,1460> buffer;        // ok work
    // std::vector<char>   buffer(1024);    // ok work
    std::string         buffer;         // ok work
    buffer.resize(1024);
    boost::system::error_code ec;
    boost::asio::ip::tcp::socket socket(io_context);
    acceptor.accept(socket);
    for(;;)
    {
        len = socket.read_some(boost::asio::buffer(buffer),ec);
        if(ec)
        {
            if(ec == boost::asio::error::eof)
            {
                // peer is close
                goto accept;
            }
            std::cout << "error info : " << ec.message() << std::endl;
        }
        socket.send(boost::asio::buffer(buffer,len));
    }
    return ;
}
