/*
** EPITECH PROJECT, 2025
** zappy_graphical
** File description:
** Socket.hpp
*/

#ifndef SOCKET_HPP_
    #define SOCKET_HPP_

    #include <iostream>
    #include <arpa/inet.h>
    #include <sys/poll.h>
    #include <sys/socket.h>

class SocketClass {
public:
    SocketClass(const std::string& machine, int port);
    ~SocketClass() = default;

    class SocketException : public std::exception
        {
            public:
                explicit SocketException(const std::string &message)
                : _message("[Socket] " + message)
                {}
                ~SocketException() override = default;
                const char *what() const noexcept override
                {
                    return _message.c_str();
                }
            private:
                std::string _message;
        };

    void monitorSockets(int timer = 0);
    int socketPoll();
    int socketPoll(int s);
    void socketSend();
    bool socketRecv();
    void clearIBuffer() { this->IBuffer.clear(); };

    std::string& getInputBuffer() { return IBuffer; };
    void pushOutputBuffer(std::string msg);
private:
    std::string _machine;
    int _port;
    struct pollfd _fd;
    std::string OBuffer;
    std::string IBuffer;
};

#endif // !SOCKET_HPP_
