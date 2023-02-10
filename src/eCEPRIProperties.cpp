#include "eCEPRIProperties.h"

eCEPRIProperties::eCEPRIProperties() {}

void eCEPRIProperties::setConcatIndicator(std::string concatIndicator)
{
    this->concatIndicator = concatIndicator;
}
void eCEPRIProperties::setMessageType(std::string messageType)
{
    this->messageType = messageType;
}
void eCEPRIProperties::setPayloadSize(std::string payloadSize)
{
    this->payloadSize = payloadSize;
}
void eCEPRIProperties::setProtocolVersion(std::string protocolVersion)
{
    this->protocolVersion = protocolVersion;
}
void eCEPRIProperties::setRtcId(std::string rtcId)
{
    this->rtcId = rtcId;
}
void eCEPRIProperties::setSequenceId(std::string sequenceId)
{
    this->sequenceId = sequenceId;
}

std::string eCEPRIProperties::format()
{
    std::string data;
    data += "Protocol Version: " + this->protocolVersion + '\n';
    data += "Concatenation Indicator: " + this->concatIndicator + '\n';
    data += "Message Type: " + this->messageType + '\n';
    data += "Payload Size: " + this->payloadSize + '\n';
    data += "RTC ID: " + this->rtcId + '\n';
    data += "Sequence ID: " + this->sequenceId + '\n';
    return data;
}