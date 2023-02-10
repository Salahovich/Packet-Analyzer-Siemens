#include "eCEPRIParser.h"
#include "eCEPRIProperties.h"
#include "eCEPRI.h"

eCEPRIParser::eCEPRIParser(std::string packet) : RawParser{packet} {}

EthernetPacket* eCEPRIParser::parse()
{
    eCEPRIProperties *frame = new eCEPRIProperties();
    frame->setProtocolVersion(parseProtocolVersion());
    frame->setConcatIndicator(parseConcatenationIndicator());
    frame->setMessageType(parseMessageType());
    frame->setPayloadSize(parsePayloadSize());
    frame->setRtcId(parseRTCId());
    frame->setSequenceId(parseSequenceId());

    FrameProperties *parentFrame = RawParser::parse()->getFrame();
    EthernetPacket *packet = new eCEPRI(parentFrame, frame);
    return packet;
}
std::string eCEPRIParser::parseProtocolVersion()
{
    return getSubstring(packet, 44, 1);
}
std::string eCEPRIParser::parseConcatenationIndicator()
{
    return getSubstring(packet, 45, 1);
}
std::string eCEPRIParser::parseMessageType()
{
    return getSubstring(packet, 46, 1 * byteSize);
}
std::string eCEPRIParser::parsePayloadSize()
{
    return getSubstring(packet, 48, 2 * byteSize);
}
std::string eCEPRIParser::parseRTCId()
{
    return getSubstring(packet, 52, 2 * byteSize);
}
std::string eCEPRIParser::parseSequenceId()
{
    return getSubstring(packet, 56, 2 * byteSize);
}