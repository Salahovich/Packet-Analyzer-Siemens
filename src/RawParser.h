#ifndef RawParser_H
#define RawParser_H
#include "EthernetPacket.h"

class RawParser{
    public:
        std::string packet;
       
        RawParser(std::string);
        static std::string getSubstring(std::string, int, int);
        static std::string getType(std::string);
        virtual EthernetPacket* parse();
      
    private:
        // std::string getPreamble();
        std::string getDestination();
        std::string getSource();
        std::string getFCS();


};
#endif