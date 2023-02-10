#ifndef PacketAnalyzer_H
#define PacketAnalyzer_H

#include "IOUtils.h"
#include "EthernetPacket.h"
#include <string>
#include <vector>

class PacketAnalyzer{
    public:
        PacketAnalyzer(std::string, std::string);
        void read();
        void write();
        void execute();
        ~PacketAnalyzer();
        
    private:
        IOUtils* io;
        std::vector<std::string>* packetString;
        std::vector<EthernetPacket*> packets;

};
#endif