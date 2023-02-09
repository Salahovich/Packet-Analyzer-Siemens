#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class IOUtils{
    public:
        IOUtils(string readFile, string writeFile){
            this->readFile = readFile;
            this->writeFile = writeFile;
            this->writer.open(writeFile, ios::out);
            this->reader.open(readFile, ios::in);
        }

        void writePacket(string packet){
            if(!this->writer.is_open())
                throw "The write file is not open";
            this->writer << packet;
            this->writer << "******************************************************************************\n";
        }

        vector<string>* read(){
            if(!this->reader.is_open())
                throw "The read file is not open";
            vector<string>* packets = new vector<string>();

            string line;
            while(getline(this->reader, line)){
                packets->push_back(line);    
            }
            this->reader.close();
            return packets;
        }

        ~IOUtils(){
            // close the streams
            this->writer.close();
        }

    private:
        string readFile, writeFile;
        ofstream writer;
        ifstream reader;

};

class FrameProperties{
    public:
        FrameProperties(){}

        void setDestination(string destination){
            this->destination = destination;
        }
        void setSource(string source){
            this->source = source;
        }
        void setType(string type){
            this->type = type;
        }
        void setFCS(string fcs){
            this->fcs = fcs;
        }
        void setFullPacket(string fullPacket){
            this->fullPacket = fullPacket;
        }

        string format(int id){
            string data="";
            data += "Packet #" + to_string(id) + ": \n";
            data += this->fullPacket + '\n';
            data += "Source Address: " + this->source + '\n';
            data += "Destination Address: " + this->destination + '\n';
            data += "Type: " + this->type + '\n';
            data += "CRC: " + this->fcs + '\n';
            return data;
        }

    private:
        string destination, source, type, fcs, fullPacket;
};

class eCEPRIProperties{
    public:
        eCEPRIProperties(){}

        
        void setConcatIndicator(string concatIndicator){
            this->concatIndicator = concatIndicator;
        }
        void setMessageType(string messageType){
            this->messageType = messageType;
        }
        void setPayloadSize(string payloadSize){
            this->payloadSize = payloadSize;
        }
        void setProtocolVersion(string protocolVersion){
            this->protocolVersion = protocolVersion;
        }
        void setRtcId(string rtcId){
            this->rtcId = rtcId;
        }
        void setSequenceId(string sequenceId){
            this->sequenceId = sequenceId;
        }

        string format(){
            string data;
            data += "Protocol Version: " + this->protocolVersion + '\n';
            data += "Concatenation Indicator: " + this->concatIndicator + '\n';
            data += "Message Type: " + this->messageType + '\n';
            data += "Payload Size: " + this->payloadSize + '\n';
            data += "RTC ID: " + this->rtcId + '\n';
            data += "Sequence ID: " + this->sequenceId + '\n';
            return data;
        }
    private: 
        string concatIndicator, messageType, payloadSize, protocolVersion, rtcId, sequenceId;
};

class EthernetPacket{
    public: 
        EthernetPacket(FrameProperties* properties){
            this->commonProperties = properties;
        }

        virtual string format(int id){
            return this->commonProperties->format(id);
        }

        FrameProperties* getFrame(){
            return this->commonProperties;
        }
        ~EthernetPacket(){
            delete commonProperties;
        }
    private:  
       FrameProperties* commonProperties;
};

class eCEPRI : public EthernetPacket{
    public: 
        eCEPRI(FrameProperties* properties, eCEPRIProperties* special):EthernetPacket{properties}{
            this->specialProperties = special;
        }
       
        string format(int id){
            string data = EthernetPacket::format(id);
            data += this->specialProperties->format();
            return data;
        }

        ~eCEPRI(){
            delete specialProperties;
        }
    private: 
         eCEPRIProperties* specialProperties;
};

class RawParser{
    public:
        static const int byteSize = 2;
        string packet;
        RawParser(string packet){
            this->packet = packet;
        }

        static string getSubstring(string packet, int index, int size){
            string data;
            for(int i=index; i<index+size; i++){
                data+=packet[i];
            }
            return data;
        }

        static string getType(string packet){
            return getSubstring(packet, 40, 2*byteSize);
        }

        virtual EthernetPacket* parse(){
            FrameProperties* frame = new FrameProperties();
            frame->setDestination(getDestination());
            frame->setSource(getSource());
            frame->setType(getType(packet));
            frame->setFCS(getFCS());
            frame->setFullPacket(packet);
            EthernetPacket* RawPacket = new EthernetPacket(frame);
            
            return RawPacket;
        }
      
    private:

        // string getPreamble(){
        //     return getSubstring(packet, 0, 8*byteSize);
        // }

        string getDestination(){
            return getSubstring(packet, 16, 6*byteSize);
        }

        string getSource(){
            return getSubstring(packet, 28, 6*byteSize);
        }

        string getFCS(){
            int index = packet.size()-4*byteSize;     // last four bytes of a packet
            return getSubstring(packet, index, 4*byteSize);
        }

        
};

class eCEPRIParser : public RawParser{
    public:
        eCEPRIParser(string packet) : RawParser{packet}{}

        EthernetPacket* parse(){
            eCEPRIProperties* frame = new eCEPRIProperties();
            frame->setProtocolVersion(parseProtocolVersion());
            frame->setConcatIndicator(parseConcatenationIndicator());
            frame->setMessageType(parseMessageType());
            frame->setPayloadSize(parsePayloadSize());
            frame->setRtcId(parseRTCId());
            frame->setSequenceId(parseSequenceId());
            
            FrameProperties* parentFrame = RawParser::parse()->getFrame(); 
            EthernetPacket* packet = new eCEPRI(parentFrame, frame);
            return packet;
        }
    private:
        string parseProtocolVersion(){
            return getSubstring(packet, 44, 1);
        }
        string parseConcatenationIndicator(){
            return getSubstring(packet, 45, 1);
        }
        string parseMessageType(){
            return getSubstring(packet, 46, 1*byteSize);
        }
        string parsePayloadSize(){
            return getSubstring(packet, 48, 2*byteSize);
        } 
        string parseRTCId(){
            return getSubstring(packet, 52, 2*byteSize);
        }
        string parseSequenceId(){
            return getSubstring(packet, 56, 2*byteSize);
        }
};

class PacketAnalyzer{
    public: 
        PacketAnalyzer(string in, string out){
            this->io = new IOUtils(in, out);
        }

        void read(){
            this->packetString = this->io->read();
        }
        void write(){
            int packetId=0;
            for(EthernetPacket* packet : packets){
                this->io->writePacket(packet->format(packetId));
                packetId++;
            }
        }
        void execute(){
            read();
            RawParser* parser;
            for(string& thePacket : *packetString){
                string type = RawParser::getType(thePacket);
                if(type == "AEFE")
                    parser = new eCEPRIParser(thePacket);
                else
                    parser = new RawParser(thePacket);
                packets.push_back(parser->parse());
                delete parser;
            }
            write();
        }

        ~PacketAnalyzer(){
            delete io;
            delete packetString;
            for(EthernetPacket* packet : packets)
                delete packet;
        }
    private:
        IOUtils* io;
        vector<string>* packetString;
        vector<EthernetPacket*> packets;
        
};

int main(){
    PacketAnalyzer analyzer("input_packets", "output");
    analyzer.execute();

    return 0;
}