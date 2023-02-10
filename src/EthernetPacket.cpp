#include "EthernetPacket.h"

EthernetPacket::EthernetPacket(FrameProperties *properties)
{
    this->commonProperties = properties;
}

std::string EthernetPacket::format(int id)
{
    return this->commonProperties->format(id);
}

FrameProperties *EthernetPacket::getFrame()
{
    return this->commonProperties;
}
EthernetPacket::~EthernetPacket()
{
    delete commonProperties;
}