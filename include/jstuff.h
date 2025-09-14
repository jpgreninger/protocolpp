/*
 * jstuff.h
 *
 *  Created on: Mar 1, 2015
 *  Author: John Peter Greninger
 *  Copyright 2015
 */

#ifndef JSTUFF_H_
#define JSTUFF_H_

#include <vector>
#include <memory>
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include <string>
#include <iomanip>
#include "jarray.h"
#include "jrand.h"

namespace jstuff {
    template <typename T> class jarray;
    class jrand;
}

struct seca_t {
    jstuff::jarray<uint8_t> cipherkey;
    jstuff::jarray<uint8_t> authkey;
    jstuff::jarray<uint8_t> iv;
    jstuff::jarray<uint8_t> arwindow;
    uint32_t window;
    uint32_t icvlen;
    uint64_t seqnum;
    std::string cipher;
    std::string auth;
};

#include "jtcp.h"
#include "judp.h"

#endif /* JSTUFF_H_ */
