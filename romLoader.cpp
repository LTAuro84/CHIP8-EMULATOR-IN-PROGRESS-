#include "romLoader.h"
using namespace std;

TRomLoader::TRomLoader() {
    m_logger = TLogger::getInstance();
}

TRomLoader::~TRomLoader() {

}

void TRomLoader::loadRom(string& file_path, uint8_t* mem) {

    m_logger->log("Loading ROM: " + file_path, ELogLevel::INFO);

    //this opens the file in binary mode
    ifstream file(file_path, ios::binary);

    if (!file) {
        m_logger->log("Couldn't open file: " + file_path, ELogLevel::ERROR);
        exit(1);
    }

    //this determines the rom size
    file.seekg(0, ios::end);
    streamsize size = file.tellg();
    file.seekg(0, ios::beg);

    if (file.read(reinterpret_cast<char*>(mem), size))
        m_logger->log("File read successfully. Size: " + to_string(size) + " bytes.", ELogLevel::INFO);
    else {
        m_logger->log("Error during file read", ELogLevel::ERROR);
        exit(1);
    }

    file.close();
}