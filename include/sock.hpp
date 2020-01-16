#ifndef PKT_SNIFFER_SOCK_HH_
#define PKT_SNIFFER_SOCK_HH_

#include <array>
#include <string>
#include <optional>

#include "packet.hpp"

class Sock {
public:
    Sock() = default;
    Sock(const Sock&) = delete;
    Sock(Sock&&) = default;

    ~Sock();

    bool open();
    bool bindToInterface(const std::string& interface);
    std::optional<Packet> read();

private:
    const std::string _interfaceName;

    int _sock { 0 };
    std::array<uint8_t, Packet::MAX_PACKET_SIZE> _data;
};

#endif /* PKT_SNIFFER_SOCK_HH_ */