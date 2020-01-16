#ifndef PKT_SNIFFER_PACKET_HH_
#define PKT_SNIFFER_PACKET_HH_

#include <limits>
#include <array>
#include <vector>
#include <exception>
#include <utility>

class PacketInvalidDataException : public std::exception {
public:
    explicit PacketInvalidDataException(const std::string& info) : _info(info) {
    } 

    const char* what() const throw() {
        return _info.c_str();
    }

private:
    const std::string _info;
};

class Packet {
public:
    static constexpr auto MAX_PACKET_SIZE = std::numeric_limits<uint16_t>::max();

    Packet(const std::array<uint8_t, Packet::MAX_PACKET_SIZE>& data, const ssize_t dataLen) {
        if ((dataLen < 0) or (static_cast<std::size_t>(dataLen) > data.size())) {
            const std::string info = "Invalid data len " + std::to_string(dataLen);
            throw PacketInvalidDataException(info);
        }

        std::vector<uint8_t> tmpData { data.begin(), data.begin() + dataLen };
        _data = std::move(tmpData);
    }

    const std::vector<uint8_t>& getRawData() const {
        return _data;
    }

private:
    std::vector<uint8_t> _data;
};

#endif /* PKT_SNIFFER_PACKET_HH_ */