/*
 * jprotocol.cpp
 *
 *  Created on: Mar 8, 2015
 *  Author: John Peter Greninger
 *  Copyright 2015
 */
#include "../include/jprotocol.h"

// constructors
jprotocol::jprotocol(unsigned int& mtu,
                     unsigned int seed) : m_mtu(mtu),
                                          m_file(),
                                          m_rand(seed)
{}

jprotocol::jprotocol(unsigned int& mtu,
		             std::string& file,
                     unsigned int seed) : m_mtu(mtu),
										  m_file(file.c_str(), std::fstream::in),
                                          m_rand(seed)
{}

//jprotocol::jprotocol(unsigned int& mtu,
//		             replay_t& replay) : m_mtu(mtu),
//		                                 m_replay(replay)
//{}

//jprotocol::jprotocol(unsigned int& mtu,
//		             std::string& file,
//					 replay_t& replay) : m_mtu(mtu),
//									     m_file(file.c_str(), std::fstream::in),
//									     m_replay(replay)
//{}


jarray<uint8_t> jprotocol::checksum(protocol_t prot, direction_t dir, jarray<uint8_t>& data) {
    jarray<uint8_t> temp(data);
    jarray<uint8_t> chksum(2);
    uint32_t result = 0;
    uint8_t pad = 0;

    // based on protocol, zero out the correct field if ENCAP
    if (dir == ENCAP) {
        switch (prot) {
            case UDP :
                temp[6] = 0;
                temp[7] = 0;
                break;
            case TCP :
                temp[16] = 0;
                temp[17] = 0;
                break;
            case IPv4 :
                temp[10] = 0;
                temp[11] = 0;
                break;
            default :
                std::cerr << "In jprotocol::checksum(), unknown protocol requested : " << prot;
        }
    }

	// checksum is performed on 16-bits, pad with zeros
	if ((temp.get_size() % 2) != 0) {
		temp.push_back(pad);
	}

	// calculate the checksum 16-bits at a time
	for (unsigned int i=0; i<temp.get_size(); i=i+2) {
		result += ((temp[i] << 8) | temp[i+1]);
		result += (result >> 16);
	}

	// complement the result
	result = ~result;

	// if result is zero, set it to all F's
	if (result == 0) {
		result = 0xFFFF;
	}

    // convert result to uint8_t array
    chksum[0] = ((result >> 8) & 0xFF);
    chksum[1] = (result & 0xFF);

    // return the result as an array
    return chksum;
}

jarray<uint8_t> jprotocol::pad(pad_t padtype, unsigned int& length) {
	jarray<uint8_t> padding(length);

	// generate the correct type of padding
	if (padtype == RANDOM) {
		padding = m_rand.getbytes(length);
	}
	else if (padtype == INCREMENT) {
		padding = jarray<uint8_t>(length);
		for(unsigned int i=0; i<length; i++) {
			padding[i] = static_cast<uint8_t>(i+1);
		}
	}
	else if (padtype == ZERO) {
        uint8_t value = 0;
		padding = jarray<uint8_t>(length, value);
	}
	else {
		std::cerr << "In jprotocol::pad(), unknown padding type requested : " << padtype;
		padding = jarray<uint8_t>(0);
	}

	return padding;
}

unsigned int jprotocol::get_mtu() {
	return m_mtu;
}

jarray<uint8_t> jprotocol::get_data() {
    char* buffer = new char [m_mtu];
    m_file.read(buffer, m_mtu);

    // return the array populated with the file data
    return jarray<uint8_t>(std::string(buffer));
}

void jprotocol::put_data(jarray<uint8_t>& wdata) {
    m_file << wdata.to_string();
}

void jprotocol::update_mtu(unsigned int& mtu) {
	m_mtu = mtu;
}

//uint32_t jprotocol::get_extseqnum() {
	//return m_replay.extseqnum;
//}
