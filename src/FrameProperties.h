#ifndef FrameProperties_H
#define FrameProperties_H
#include <string>

class FrameProperties{
    public:
        FrameProperties();
        void setSource(std::string);
        void setDestination(std::string);
        void setType(std::string);
        void setFCS(std::string);
        void setFullPacket(std::string);
        std::string format(int id);
    private:
        std::string destination, source, type, fcs, fullPacket;
};

#endif