#ifndef eCEPRI_H
#define eCEPRI_H
#include "FrameProperties.h"
#include "eCEPRIProperties.h"
#include "EthernetPacket.h"

class eCEPRI : public EthernetPacket{
    public:
        eCEPRI(FrameProperties*, eCEPRIProperties*);
        std::string format(int);
        ~eCEPRI();

    private:
       eCEPRIProperties* specialProperties;
};

#endif