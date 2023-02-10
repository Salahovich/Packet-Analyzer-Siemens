#include <iostream>
#include "src/PacketAnalyzer.h"

using namespace std;


int main(){
    try{   
        PacketAnalyzer analyzer("io\\input_packets", "io\\output");
        analyzer.execute();
    }catch(const char* msg){
        cout << msg;
    }

    return 0;
}