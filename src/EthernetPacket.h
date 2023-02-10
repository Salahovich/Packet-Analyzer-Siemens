#ifndef EthernetPacket_H
#define EthernetPacket_H
#include "FrameProperties.h"

class EthernetPacket{
    public:
        EthernetPacket(FrameProperties*);
        virtual std::string format(int);
        FrameProperties* getFrame();
        ~EthernetPacket();
    private:
        FrameProperties* commonProperties;
};

#endif