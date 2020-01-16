#include <iostream>
#include <unistd.h>

#include "sock.hpp"
#include "packet_printer.hpp"

struct CliConfig {
    std::string interface;
};

void printUsage() {
    std::cout << "Usage: -i interface" << std::endl;
}

CliConfig getCliConfig(int argc, char** argv) {
    CliConfig cliConfig;
    int opt {};
    while ((opt = getopt(argc, argv, "i:")) != EOF) {
        switch (opt) {
            case 'i': {
                cliConfig.interface = optarg; 
                break;
            }
            default: {
                printUsage();
                break;
            }
        }
    }

    return cliConfig;
}

int main(int argc, char** argv) {
    const auto cliConfig = getCliConfig(argc, argv);
    if (cliConfig.interface.empty()) {
        return 1;
    }

    Sock sock;
    if (not sock.open()) {
        std::cout << "Failed to open socket" << std::endl;
        return 1;
    }

    if (not sock.bindToInterface(cliConfig.interface)) {
        std::cout << "Failed to bind to interface " << cliConfig.interface << std::endl;
        return 1;
    }

    std::cout << "Listening on interface " << cliConfig.interface << std::endl;

    PacketPrinter printer;
    while (true) {
        const auto packet = sock.read();
        if (packet) {
            printer.print(*packet);
        }
    }

    return 0;
}
