#ifndef eCEPRIProperties_H
#define eCEPRIProperties_H
#include <string>

class eCEPRIProperties{
    public:
        eCEPRIProperties();
        void setConcatIndicator(std::string);
        void setMessageType(std::string);
        void setPayloadSize(std::string);
        void setProtocolVersion(std::string);
        void setRtcId(std::string);
        void setSequenceId(std::string);

        std::string format();
    private:
        std::string concatIndicator, messageType, payloadSize, protocolVersion, rtcId, sequenceId;
};
#endif