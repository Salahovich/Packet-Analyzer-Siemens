#include "RawParser.h"
#include "FrameNumbers.h"

RawParser::RawParser(std::string packet)
{
    this->packet = packet;
}

// string getPreamble(){
//     return getSubstring(packet, 0, 8*byteSize);
// }

std::string RawParser::getDestination()
{
    return getSubstring(packet, FrameNumbers::DESTINATION[0], FrameNumbers::DESTINATION[1]);
}

std::string RawParser::getSource()
{
    return getSubstring(packet, FrameNumbers::SOURCE[0], FrameNumbers::SOURCE[1]);
}

std::string RawParser::getFCS()
{
    int index = packet.size() - 4 * FrameNumbers::BYTE_SIZE; // last four bytes of a packet
    return getSubstring(packet, index, FrameNumbers::FCS[1]);
}

std::string RawParser::getSubstring(std::string packet, int index, int size)
{
    std::string data;
    for (int i = index; i < index + size; i++)
    {
        data += packet[i];
    }
    return data;
}

std::string RawParser::getType(std::string packet)
{
    return getSubstring(packet, FrameNumbers::TYPE[0], FrameNumbers::TYPE[1]);
}

EthernetPacket* RawParser::parse()
{
    FrameProperties *frame = new FrameProperties();
    frame->setDestination(getDestination());
    frame->setSource(getSource());
    frame->setType(getType(packet));
    frame->setFCS(getFCS());
    frame->setFullPacket(packet);
    EthernetPacket *RawPacket = new EthernetPacket(frame);

    return RawPacket;
}

