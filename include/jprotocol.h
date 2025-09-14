/*
 * jprotocol.h
 *
 *  Created on: Feb 28, 2015
 *  Author: John Peter Greninger
 *  Copyright 2015
 */

#ifndef JPROTOCOL_H_
#define JPROTOCOL_H_

#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "jarray.h"
#include "jrand.h"

#define HEX(a, b) \
    "0x" << std::setw(b) << std::setfill('0') << std::hex << static_cast<unsigned int>(a)

// padding types
enum pad_t {
    RANDOM,
    INCREMENT,
    ZERO
};

// protocol types
enum protocol_t {
    UDP,
	TCP,
	IPv4,
	IPv6,
    IPAHv4,
    IPAHv6,
    IPsecv4,
    IPsecv6,
	MACSEC,
	WIFI,
	WIMAX,
	LTE,
	SSL
};

// processing direction
enum direction_t {
    ENCAP,
    DECAP,
};

// link direction
enum link_t {
    DOWNLINK,
    UPLINK
};

// encryption ciphers
enum cipher_t {
    DES_CBC,
    TDES_CBC,
    AES_CBC,
    AES_CTR,
    AES_CCM,
    AES_GCM,
    SNOWE,
    ZUCE
};

// authentication types
enum auth_t {
    MD5,
    SHA1,
    SHA224,
    SHA256,
    SHA384,
    SHA512,
    SNOWA,
    ZUCA
};

// anti-replay structure used by children to pass information
//template <typename TK=uint32_t, typename TE=uint32_t, unsigned int WIN=0>
//struct replay_t {
//    TK seqnum;
//    TE extseqnum;
//    unsigned int window=WIN;
//    jarray<int> arwindow;
//
//    replay_t() {
//        seqnum = 1;
//        extseqnum = 0;
//        for (unsigned int i=0; i<window; i++) {
//            if (i == 0) {
//                arwindow[i] = 1;
//            }
//            else {
//                arwindow[i] = 0;
//            }
//        }
//    }
//};

class jprotocol {
public:

	// constructors
	jprotocol(unsigned int& mtu, unsigned int seed=0xF1234567);
	jprotocol(unsigned int& mtu, std::string& file, unsigned int seed=0xF1234567);
	//jprotocol(unsigned int& mtu, replay_t& replay);
	//jprotocol(unsigned int& mtu, std::string& file, replay_t& replay);

	// deconstructor
	virtual ~jprotocol() {}

	// packet processing functions for use with files
	virtual void encap_packet(std::shared_ptr<jarray<uint8_t>>& output);
    virtual void decap_packet(std::shared_ptr<jarray<uint8_t>>& input);

    // packet processing functions for use with arrays, used with all protocols
	virtual void encap_packet(std::shared_ptr<jarray<uint8_t>>& input, std::shared_ptr<jarray<uint8_t>>& output) = 0;
	virtual void decap_packet(std::shared_ptr<jarray<uint8_t>>& input, std::shared_ptr<jarray<uint8_t>>& output) = 0;

    //template <typename T>
    //void update_seqnum(T& seqnum) { m_replay.seqnum = seqnum; }

protected:

	// helper functions
	jarray<uint8_t> checksum(protocol_t prot, direction_t dir, jarray<uint8_t>& check);
	jarray<uint8_t> pad(pad_t padtype, unsigned int& len);

    // functions for MTU
    void update_mtu(unsigned int& mtu);
    unsigned int get_mtu();

    // file access functions
    jarray<uint8_t> get_data();
    void put_data(jarray<uint8_t>& wdata);

    // get the sequence number
//    template <typename T>
//    T get_seqnum() {
//        return m_replay.seqnum;
//    }

    // anti-replay function, uses an INT array to support any size
    // window instead of being limited to 32, 64, or 128
//    template <typename T>
//    bool antireplay(T& currseq) {
//        uint64_t diff = currseq - m_replay.seqnum;
//        uint64_t curr = 0;
//        uint8_t bit = 0;
//        int pos = 0;

//        if (m_replay.window == 0) {
//            std::cout << "Anti-Replay is not enabled" << std::endl;
//            return true;
//        }
//        else if (diff < 0) {
//            int chk = abs(diff);
//            if (chk > m_replay.window) {
//                std::cerr << "LATE ERROR detected, CURR : " << m_replay.seqnum << ", RECEIVED : " << currseq << ", WINDOW : " << m_replay.window << std::endl;
//                return false;
//            }
//            else {
//                if (m_replay.arwindow[chk] == 1) {
//                    std::cerr << "REPLAY ERROR detected, CURR : " << m_replay.seqnum << ", RECEIVED : " << currseq << ", BIT POS : " << chk << std::endl;
//                    return false;
//                }
//                else {
//                    m_replay.arwindow[chk] = 1;
//                    return true;
//                }
//            }
//        }
//        else if (diff == 0) {
//            std::cerr << "REPLAY ERROR detected, CURR : " << m_replay.seqnum << ", RECEIVED : " << currseq << std::endl;
//            return false;
//        }
//        else {
//            // shift the window length of diff, set bit
//            jarray<int> newwin(diff, 0);
//            newwin[0] = 1;
//            m_replay.arwindow.insert(0, newwin);
//            m_replay = m_replay.arwindow.split(0, m_replay.window);
//            m_replay.seqnum = currseq;
//            return true;
//        }
//    }

private:

    // don't use these
    jprotocol() = delete;
    jprotocol(const jprotocol& jprotocol) = delete;

	// maximum transmission unit
	unsigned int m_mtu;

    // anti-replay structure
    //replay_t m_replay;

    // input file
    std::fstream m_file;

    // random number generator for padding
    jrand m_rand;
};

#endif /* JPROTOCOL_H_ */
