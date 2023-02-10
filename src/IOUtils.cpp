#include "IOUtils.h"
using namespace std;

IOUtils::IOUtils(string readFile, string writeFile){
    this->readFile = readFile;
    this->writeFile = writeFile;
    this->writer.open(writeFile, ios::out);
    this->reader.open(readFile, ios::in);
}

void IOUtils::writePacket(string packet){
    if(!this->writer.is_open())
        throw "The write file is not open";
    this->writer << packet;
    this->writer << "******************************************************************************\n";
}

vector<string>* IOUtils::read(){
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
IOUtils::~IOUtils(){
    // close the streams
    this->writer.close();
}