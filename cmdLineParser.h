#ifndef __CMDLINEPARSER_H__
#define __CMDLINEPARSER_H__

#include <iostream>
#include "logger.h"
using namespace std;

class TCmdLineParser {

    //loggin
    shared_ptr<TLogger> logger;

    string romFileName; 
    int logLevel;

    void printHelpMessage();
    void setRomFileName(string new_name);
    void setLogLevel(int logLevel);
public:
    TCmdLineParser();
    void parseCmdLine(int argc, char** arv);

    bool isRomeFileNameSet(); //checks if rom file name was provided
    string getRomFileName();  //returns the rom file name
    bool isLogLevelSet();   //checks if the log level was set
    int getLogLevel(); //returns the log level
};

#endif