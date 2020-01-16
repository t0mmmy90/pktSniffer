#ifndef PKT_SNIFFER_PACKET_PRINTER_HH_
#define PKT_SNIFFER_PACKET_PRINTER_HH_

#include <sstream>
#include <iostream>
#include <iomanip>

#include "packet.hpp"

class PacketPrinter {
public:
    void print(const Packet& packet) const {
        constexpr auto BYTE_WIDTH = 2;
        constexpr auto BYTE_FILL = '0';
        const auto packetRawData = packet.getRawData();

        std::stringstream dataStream;
        dataStream << "Packet data: " << std::endl;
        for (const auto byte : packetRawData) {
            dataStream << std::hex << std::uppercase << std::setfill(BYTE_FILL) << std::setw(BYTE_WIDTH) <<
            static_cast<int>(byte) << " ";
        }
        std::cout << dataStream.str() << std::endl;
    }
};

#endif /* PKT_SNIFFER_PACKET_PRINTER_HH_ */