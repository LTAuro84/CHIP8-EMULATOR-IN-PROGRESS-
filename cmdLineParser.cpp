#include <cctype>
#include <cmdLineParser.h>
using namespace std;

void TCmdLineParser::printHelpMessage() {
    cout << "Usage: lcc [options] file..." << endl;
    cout << "Options: " << endl;
    cout << "   -h, --help              Display this help information" << endl;
    cout << "   -r, --romFileName       Set the rom file path to be used" << endl;
    cout << "   -l, --logLevel          Set the desired log level [NONE = 0, ERROR = 1, WARN = 2, INFO = 3, DEBUG = 4]" << endl; 
}