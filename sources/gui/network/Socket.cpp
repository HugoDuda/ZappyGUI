#include "network/Socket.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <cerrno>
#include <sys/poll.h>
#include <stdint.h>
#include <sys/socket.h>
#include <vector>

SocketClass::SocketClass(const std::string& ip, int port)
{
    this->_machine = ip;
    struct sockaddr_in address = { 
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr = {0},
        .sin_zero = {0},
    };

    if (this->_machine.empty() || this->_machine == "localhost") {
        this->_machine = "0.0.0.0";
    }
    if (inet_aton(this->_machine.c_str(), &address.sin_addr) == 0) {
        throw SocketException("Could not connect to "
            + this->_machine + ":" + std::to_string(port) + ": Invalid IP");
    }
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fd == -1) {
        throw SocketException(std::string("Could not create TCP socket: ") + strerror(errno));
    }
    if (connect(fd, (const sockaddr *) &address, sizeof address) < 0) {
       throw SocketException("Could not connect to " + ip + ":" + std::to_string(port) + ": " + strerror(errno));
    }
    this->_fd = {
        .fd = fd,
        .events = POLLIN,
        .revents = 0
    };
}

int SocketClass::socketPoll()
{
    return poll(&this->_fd, 1, 0); 
}

int SocketClass::socketPoll(int s)
{
    return poll(&this->_fd, 1, s); 
}

void SocketClass::socketSend()
{
    if (!(this->_fd.revents & POLLOUT)) {
        this->_fd.events |= POLLOUT;
        return;
    }

    size_t sended = send(this->_fd.fd, (void *)OBuffer.c_str(), OBuffer.size(), MSG_NOSIGNAL);

    std::cout << sended << " sended , buff size = " << OBuffer.size() << std::endl;
    OBuffer.erase(0, sended);
    std::cout << "buff size = " << OBuffer.size() << std::endl;
    if (this->OBuffer.empty()) {
        this->_fd.events &= ~POLLOUT;
    }
}

bool SocketClass::socketRecv()
{
    std::vector<char> buf(512);

    ssize_t nb_recv = recv(this->_fd.fd, buf.data(), 512, MSG_NOSIGNAL);
    if (nb_recv != 0) {
        IBuffer += std::string(buf.data(), nb_recv);
        return true;
    }
    return false;
}

void SocketClass::pushOutputBuffer(std::string msg)
{
    OBuffer += msg;
}

void SocketClass::monitorSockets(int timer)
{
    if (this->socketPoll(timer)) {
        if (this->_fd.events & POLLOUT && this->_fd.revents & POLLOUT) {
            this->socketSend();
        }

        if (!(this->_fd.revents & POLLIN) && !(this->_fd.revents & POLLOUT)) {
            return;
        }
        if (this->socketRecv() == false) {
            throw SocketException("Socket Disconnected");
        }
    }
}
