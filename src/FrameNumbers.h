#ifndef FrameNumbers_H
#define FrameNumbers_H
#include <string>


class FrameNumbers{
    public:
        FrameNumbers();
        static const std::string AEFE_TYPE;
        static const int BYTE_SIZE;
        static const int PREAMBLE[];
        static const int SOURCE[];
        static const int DESTINATION[];
        static const int TYPE[];
        static const int FCS[];
        static const int PROTOCOL_VER[];
        static const int CONCAT_INDICATOR[];
        static const int MESSAGE_TYPE[];
        static const int PAYLOAD_SIZE[];
        static const int RTC_ID[];
        static const int SEQUENCE_ID[];
};

#endif