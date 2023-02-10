#ifndef eCEPRIParser_H
#define eCEPRIParser_H
#include "RawParser.h"

class eCEPRIParser: public RawParser{
    public:
        eCEPRIParser(std::string);

        EthernetPacket* parse();
    private:
        std::string parseProtocolVersion();
        std::string parseConcatenationIndicator();
        std::string parseMessageType();
        std::string parsePayloadSize();
        std::string parseRTCId();
        std::string parseSequenceId();
};

#endif