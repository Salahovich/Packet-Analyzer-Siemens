#include "FrameProperties.h"

FrameProperties::FrameProperties() {}

void FrameProperties::setDestination(std::string destination)
{
    this->destination = destination;
}
void FrameProperties::setSource(std::string source)
{
    this->source = source;
}
void FrameProperties::setType(std::string type)
{
    this->type = type;
}
void FrameProperties::setFCS(std::string fcs)
{
    this->fcs = fcs;
}
void FrameProperties::setFullPacket(std::string fullPacket)
{
    this->fullPacket = fullPacket;
}

std::string FrameProperties::format(int id)
{
    std::string data = "";
    data += "Packet #" + std::to_string(id) + ": \n";
    data += this->fullPacket + '\n';
    data += "Source Address: " + this->source + '\n';
    data += "Destination Address: " + this->destination + '\n';
    data += "Type: " + this->type + '\n';
    data += "CRC: " + this->fcs + '\n';
    return data;
}