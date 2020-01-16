#include "sock.hpp"

#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <sys/socket.h>
#include <net/if.h>
#include <linux/if_packet.h>

Sock::~Sock() {
    if (_sock != 0) {
        close(_sock);
    }
}

bool Sock::open() {
    _sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (_sock < 0) {
        return false;
    }

    return true;
}

bool Sock::bindToInterface(const std::string& interface) {
    sockaddr_ll addr {};
    addr.sll_family = AF_PACKET;
    addr.sll_ifindex = if_nametoindex(interface.c_str());

    if (bind(_sock, (sockaddr*) &addr, sizeof(addr)) < 0) {
        close(_sock);
        return false;
    }

    return true;
}

std::optional<Packet> Sock::read() {
    const auto readDataLen = recvfrom(_sock, _data.data(), Packet::MAX_PACKET_SIZE, 0, NULL, NULL);

    try {
        return Packet { _data, readDataLen };
    } catch (const PacketInvalidDataException& exception) {
        std::cout << "Exception caught: " << exception.what() << std::endl;
    }

    return {};
}
