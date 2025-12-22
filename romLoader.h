#ifndef __ROMLOADER_H__
#define __ROMLOADER_H__

#include <cstdint>
#include <iostream>
#include "logger.h"

using namespace std;

class TRomLoader {
    shared_ptr<TLogger> m_logger;

public:
    TRomLoader();
    ~TRomLoader();

    void loadROm(string& file_path, uint8_t* mem);
};

#endif