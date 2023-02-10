#include "RawParser.h"

const int RawParser::byteSize = 2;

RawParser::RawParser(std::string packet)
{
    this->packet = packet;
}

// string getPreamble(){
//     return getSubstring(packet, 0, 8*byteSize);
// }

std::string RawParser::getDestination()
{
    return getSubstring(packet, 16, 6 * byteSize);
}

std::string RawParser::getSource()
{
    return getSubstring(packet, 28, 6 * byteSize);
}

std::string RawParser::getFCS()
{
    int index = packet.size() - 4 * byteSize; // last four bytes of a packet
    return getSubstring(packet, index, 4 * byteSize);
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
    return getSubstring(packet, 40, 2 * byteSize);
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

