/**
 * @file main.cpp
 * @author huangj (1435054809@qq.com)
 * @brief echo_client
 * @version 0.1your name
 * @date 2021-09-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// boost 
#include <boost/asio.hpp>

// cpp std
#include <iostream>
#include <array>
#include <string>
#include <memory>
#include <vector>


void connect_to_server(const char * ip,const int port);

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc,char * argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <IPaddress> <port> .\n",argv[0]);
        return EXIT_FAILURE;
    }
    const char * ip = argv[1];
    const uint16_t port = atoi(argv[2]);
    if(port <= 0)
    {
        printf("port need a integer number.\n");
        return EXIT_FAILURE;
    }
    // 连接服务器
    connect_to_server(ip,port);
    return EXIT_SUCCESS;
}

/**
 * @brief 
 * 
 * @param ip 
 * @param port 
 */
void connect_to_server(const char * ip,const int port)
{
    using namespace boost::asio::ip;
    boost::asio::io_context io;
    // 创建endpoint端点
    boost::asio::ip::tcp::endpoint  endpoint;
    tcp::endpoint edp(address(address_v4::from_string(ip)),port_type(port));
    // endpoint.address(boost::asio::ip::address(boost::asio::ip::address_v4::from_string(ip)));
    // endpoint.port(boost::asio::ip::port_type(port));

    endpoint.address(address(address_v4::from_string(ip)));
    endpoint.port(port_type(port));
    boost::asio::ip::tcp::socket socket(io);
    boost::system::error_code ec;

    // 如果连接失败会抛出异常
    try
    {
            socket.connect(endpoint);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }
    // open file
    FILE * fp = fopen("Makefile","r");
    if(fp == NULL)
    {
        goto end;
    }
    char buffer[1024];
    char recvbuffer[1024];
    for(;;)
    {
        bzero(buffer,1024);
        if (fgets(buffer,1024,fp) == NULL)
        {
            break;
        }
        std::size_t len = socket.send(boost::asio::buffer(buffer,strlen(buffer) + 1));
        printf("send msg size : %ld.\n",len);
        bzero(recvbuffer,1024);
        socket.receive(boost::asio::buffer(recvbuffer),1024);
        printf("echo content : %s \n",recvbuffer);
    }
end:
    socket.close();
}