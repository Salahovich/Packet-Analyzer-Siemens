#include "eCEPRI.h"

eCEPRI::eCEPRI(FrameProperties *properties, eCEPRIProperties *special) : EthernetPacket{properties}
{
    this->specialProperties = special;
}

std::string eCEPRI::format(int id)
{
    std::string data = EthernetPacket::format(id);
    data += this->specialProperties->format();
    return data;
}

eCEPRI::~eCEPRI()
{
    delete specialProperties;
}