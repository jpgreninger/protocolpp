/*
 * jtcp.h
 *
 *  Created on: Feb 28, 2015
 *  Author: John Peter Greninger
 *  Copyright 2015
 */

#ifndef JTCP_H_
#define JTCP_H_

#include <fstream>
#include <memory>
#include "jprotocol.h"

class jtcp : public jprotocol {
public:

	// constructor for normal TCP
	jtcp(unsigned int& mtu,
		 uint16_t& source,
		 uint16_t& destination);

	// constructor for normal TCP with file input
	jtcp(unsigned int& mtu,
		 uint16_t& source,
		 uint16_t& destination,
		 std::string& file);

	virtual ~jtcp() {}

	// This function is for use with the constructors that accept
	// a file. Encap will produce a packet each time it's called from
	// the data found in the file. When all data is exhausted, it will
	// return true. This function will throw if the private member
	// m_input is NULL
	void encap_packet(std::shared_ptr<jarray<uint8_t>>& output);

    // This function is for use with the constructors that accept
    // a file. Decap will extract the payload from the packet
    // check flags and write the output the object m_file. This
    // function will throw if there's no file object to write to
    void decap_packet(std::shared_ptr<jarray<uint8_t>>& input);

	// These two functions are for use with the constructors without
	// a file handle. Encap will produce a packet with the payload passed
	// in while Decap will produce a payload from the packet passed in.
	// Encap will throw if m_input is not NULL when it is called
	void encap_packet(std::shared_ptr<jarray<uint8_t>>& input, std::shared_ptr<jarray<uint8_t>>& output);
	void decap_packet(std::shared_ptr<jarray<uint8_t>>& input, std::shared_ptr<jarray<uint8_t>>& output);

	// Functions to update fields specific to TCP. Will throw if function
	// is called for a field that doesn't exist in the version of TCP this
	// TCP is configured for
	void update_source(uint16_t& source);
	void update_dest(uint16_t& destination);
	void update_tcphdr(jarray<uint8_t>& tcphdr);
	void update_window(uint16_t& size);
	void update_flags(uint16_t& flags);
	void update_seqnum(unsigned int amount);
	void update_acknum(unsigned int amount);

	// Functions to retrieve fields specific to TCP. Will throw if function
	// is called for a field that doesn't exist in the version of TCP this
	// TCP is configured for
	uint16_t get_source();
    uint16_t get_dest();
    jarray<uint8_t> get_tcphdr();
	uint32_t get_seqnum();
	uint32_t get_acknum();
	uint16_t get_flags();
	unsigned int get_window();

private:

	// don't use these
	jtcp();
	jtcp(const jtcp& jtcp);

	void init(uint16_t& source, uint16_t& destination);

	// array for TCP header
	jarray<uint8_t> m_tcphdr;
};

#endif /* JTCP_H_ */
