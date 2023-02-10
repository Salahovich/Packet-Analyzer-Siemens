#include "PacketAnalyzer.h"
#include "IOUtils.h"
#include "RawParser.h"
#include "eCEPRIParser.h"
#include "FrameNumbers.h"

PacketAnalyzer::PacketAnalyzer(std::string in, std::string out)
{
    this->io = new IOUtils(in, out);
}

void PacketAnalyzer::read()
{
    this->packetString = this->io->read();
}
void PacketAnalyzer::write()
{
    int packetId = 0;
    for (EthernetPacket *packet : packets)
    {
        this->io->writePacket(packet->format(packetId));
        packetId++;
    }
}
void PacketAnalyzer::execute()
{
    read();
    RawParser *parser;
    for (std::string &thePacket : *packetString)
    {
        std::string type = RawParser::getType(thePacket);
        if (type == FrameNumbers::AEFE_TYPE)
            parser = new eCEPRIParser(thePacket);
        else
            parser = new RawParser(thePacket);
        packets.push_back(parser->parse());
        delete parser;
    }
    write();
}

PacketAnalyzer::~PacketAnalyzer()
{
    delete io;
    delete packetString;
    for (EthernetPacket *packet : packets)
        delete packet;
}