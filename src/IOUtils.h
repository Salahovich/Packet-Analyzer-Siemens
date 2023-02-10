#ifndef IOUtils_H
#define IOUtils_H
#include <vector>
#include <string>
#include <fstream>

class IOUtils
{
    public:
        IOUtils(std::string, std::string);
        void writePacket(std::string);
        std::vector<std::string>* read();
        ~IOUtils();
    private:
        std::string readFile, writeFile;
        std::ofstream writer;
        std::ifstream reader;
};

#endif