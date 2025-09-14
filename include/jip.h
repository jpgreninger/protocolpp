/*
 * jip.h
 *
 *  Created on: July 19, 2015
 *  Author: John Peter Greninger
 *  Copyright 2015
 */

#ifndef JIP_H_
#define JIP_H_

#include <string>
#include "jprotocol.h"

// padding types
enum ext_t {
	JUMBOGRAM,
	TRAFFIC
};

class jip : public jprotocol {
public:

	// constructor for normal IPv4
	jip(unsigned int& mtu,
	    uint32_t& source,
	    uint32_t& destination,
	    uint8_t& nh);

	// constructor for normal IPv6
	jip(unsigned int& mtu,
	    uint64_t& source,
	    uint64_t& destination,
	    uint8_t& nh);

	// constructor for normal IPv4 with file input
	jip(unsigned int& mtu,
	    uint32_t& source,
	    uint32_t& destination,
	    uint8_t& nh,
	    std::string& file);

	// constructor for normal IPv6 with file input
	jip(unsigned int& mtu,
	    uint64_t& source,
	    uint64_t& destination,
	    uint8_t& nh,
	    std::string& file);

	virtual ~jip() {}

	// This function is for use with the constructors that accept
	// a file. Encap will produce a packet each time it's called from
	// the data found in the file. When all data is exhausted, it will
	// return true. This function will throw if the private member
	// m_input is NULL
	void encap_packet(std::shared_ptr<jarray<uint8_t>>& output);

	// This function is for use with the constructors that accept
	// a file. Decap will extract the payload from the packet and
	// write it to the file. This function will throw if m_file
	// file variable is NULL
	void decap_packet(std::shared_ptr<jarray<uint8_t>>& input);

	// These two functions are for use with the constructors without
	// a file handle. Encap will produce a packet with the payload passed
	// in while Decap will produce a payload from the packet passed in.
	// Encap will throw if m_input is not NULL when it is called
	void encap_packet(std::shared_ptr<jarray<uint8_t>>& input, std::shared_ptr<jarray<uint8_t>>& output);
	void decap_packet(std::shared_ptr<jarray<uint8_t>>& input, std::shared_ptr<jarray<uint8_t>>& output);

	// Functions to update fields specific to IP. Will throw if function
	// is called for a field that doesn't exist in the version of IP this
	// IP is configured for
	template <typename T>
	void update_source(T& source) {
		if (m_ver == IPv4) {
			m_iphdr[12] = ((source >> 24) & 0xFF);
			m_iphdr[13] = ((source >> 16) & 0xFF);
			m_iphdr[14] = ((source >> 8) & 0xFF);
			m_iphdr[15] = (source & 0xFF);
		}
		else if (m_ver == IPv6){
			m_iphdr[24] = ((source >> 56) & 0xFF);
			m_iphdr[25] = ((source >> 48) & 0xFF);
			m_iphdr[26] = ((source >> 40) & 0xFF);
			m_iphdr[27] = ((source >> 32) & 0xFF);
			m_iphdr[28] = ((source >> 24) & 0xFF);
			m_iphdr[29] = ((source >> 16) & 0xFF);
			m_iphdr[30] = ((source >> 8) & 0xFF);
			m_iphdr[31] = (source & 0xFF);
		}
		else {
			std::cerr << "In jip::update_source(), Unknown IP version requested : " << m_ver;
		}
	}

	template <typename T>
	void update_dest(T& destination) {
		if (m_ver == IPv4) {
			m_iphdr[16] = ((destination >> 24) & 0xFF);
			m_iphdr[17] = ((destination >> 16) & 0xFF);
			m_iphdr[18] = ((destination >> 8) & 0xFF);
			m_iphdr[19] = (destination & 0xFF);
		}
		else if (m_ver == IPv6) {
			m_iphdr[32] = ((destination >> 56) & 0xFF);
			m_iphdr[33] = ((destination >> 48) & 0xFF);
			m_iphdr[34] = ((destination >> 40) & 0xFF);
			m_iphdr[35] = ((destination >> 32) & 0xFF);
			m_iphdr[36] = ((destination >> 24) & 0xFF);
			m_iphdr[37] = ((destination >> 16) & 0xFF);
			m_iphdr[38] = ((destination >> 8) & 0xFF);
			m_iphdr[39] = (destination & 0xFF);
		}
		else {
			std::cerr << "In jip::update_destination(), Unknown IP version requested : " << m_ver;
		}
	}

    // update functions for packet processing
    void update_iphdr(jarray<uint8_t>& iphdr);
    void update_version(protocol_t& version);
    void update_dscp_ecn(uint8_t& dscp_ecn);
    void update_flow_label(uint32_t& label);
    void update_nh(uint8_t& nh);
    void update_ttl_hoplimit(uint8_t& ttl_hop);
    void update_flags(uint8_t& flags);
    void update_pktlen(unsigned int& length);
	void add_extension(ext_t& extension, unsigned int& length=0);

	// Functions to retrieve the current values for packet building
	template <typename T>
	T get_source() {
        if (m_ver == IPv4) {
            uint32_t ipv4src = ((m_iphdr[12] << 24) | (m_iphdr[13] << 16) | (m_iphdr[14] << 8) | m_iphdr[15]);
			return ipv4src;
        }
        else if (m_ver == IPv6){
            uint64_t ipv6src = ((m_iphdr[24] << 24) | (m_iphdr[25] << 16) | (m_iphdr[26] << 8) | m_iphdr[27]);
			ipv6src <<= 32;
			ipv6src |= ((m_iphdr[28] << 24) | (m_iphdr[29] << 16) | (m_iphdr[30] << 8) | m_iphdr[31]);
			return ipv6src;
        }
        else {
            std::cerr << "In jip::get_source(), Unknown IP version requested : " << m_ver;
        }
        return 0;
    }

	template <typename T>
	T get_destination() {
        if (m_ver == IPv4) {
            uint32_t ipv4dest = ((m_iphdr[12] << 24) | (m_iphdr[13] << 16) | (m_iphdr[14] << 8) | m_iphdr[15]);
			return ipv4dest;
        }
        else if (m_ver == IPv6){
            uint64_t ipv6dest = ((m_iphdr[24] << 24) | (m_iphdr[25] << 16) | (m_iphdr[26] << 8) | m_iphdr[27]);
			ipv6dest <<= 32;
			ipv6dest |= ((m_iphdr[28] << 24) | (m_iphdr[29] << 16) | (m_iphdr[30] << 8) | m_iphdr[31]);
			return ipv6dest;
        }
        else {
            std::cerr << "In jip::get_destination(), Unknown IP version requested : " << m_ver;
        }
        return 0;
    }

    // get values for packet construction
	jarray<uint8_t> get_iphdr();
	protocol_t get_version();
	uint8_t get_dscp_ecn();
	uint32_t get_label();
	uint8_t get_nh();
	uint8_t get_ttl_hoplimit();
	uint8_t get_flags();

private:

	// don't use these
	jip();
	jip(const jip& jip);

	// initialization routine
	template <typename T>
	void ipinit(T& src, T& dst, uint8_t& nxthdr) {

		// create arrays out of the src and dst
		jarray<uint8_t> mysrc = jarray<uint8_t>(src);
		jarray<uint8_t> mydst = jarray<uint8_t>(dst);

        if (m_ver == IPv4) {
            m_iphdr = jarray<uint8_t>(20);
            m_iphdr[0] = 0x45;
            m_iphdr[9] = nxthdr;
            m_iphdr[10] = 0;
            m_iphdr[11] = 0;
            m_iphdr.update(12, mysrc);
            m_iphdr.update(16, mydst);
        }
        else if (m_ver == IPv6) {
			m_iphdr = jarray<uint8_t>(40);
            m_iphdr[0] = 0x60;
            m_iphdr[6] = nxthdr;
            m_iphdr.update(24, mysrc);
            m_iphdr.update(32, mydst);
        }
        else {
            std::cerr << "In jip::get_destination(), Unknown IP version requested : " << m_ver;
        }
    }

	uint8_t m_nh;
	protocol_t m_ver;
	jarray<uint8_t> m_iphdr;

};

#endif /* JIP_H_ */
