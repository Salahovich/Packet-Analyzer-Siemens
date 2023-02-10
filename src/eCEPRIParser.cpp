#include "eCEPRIParser.h"
#include "eCEPRIProperties.h"
#include "eCEPRI.h"
#include "FrameNumbers.h"

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
    return getSubstring(packet, FrameNumbers::PROTOCOL_VER[0], FrameNumbers::PROTOCOL_VER[1]);
}
std::string eCEPRIParser::parseConcatenationIndicator()
{
    return getSubstring(packet, FrameNumbers::CONCAT_INDICATOR[0], FrameNumbers::CONCAT_INDICATOR[1]);
}
std::string eCEPRIParser::parseMessageType()
{
    return getSubstring(packet, FrameNumbers::MESSAGE_TYPE[0], FrameNumbers::MESSAGE_TYPE[1]);
}
std::string eCEPRIParser::parsePayloadSize()
{
    return getSubstring(packet, FrameNumbers::PAYLOAD_SIZE[0], FrameNumbers::PAYLOAD_SIZE[1]);
}
std::string eCEPRIParser::parseRTCId()
{
    return getSubstring(packet, FrameNumbers::RTC_ID[0], FrameNumbers::RTC_ID[1]);
}
std::string eCEPRIParser::parseSequenceId()
{
    return getSubstring(packet, FrameNumbers::SEQUENCE_ID[0], FrameNumbers::SEQUENCE_ID[1]);
}