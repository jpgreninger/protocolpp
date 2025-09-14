/*
 * judp.h
 *
 *  Created on: Feb 28, 2015
 *  Author: John Peter Greninger
 *  Copyright 2015
 */

#ifndef JUDP_H_
#define JUDP_H_

#include "jprotocol.h"

class judp : public jprotocol {
public:

	// constructor for normal UDP
	judp(unsigned int& mtu,
		 uint16_t& source,
		 uint16_t& destination);

	// constructor for normal UDP with file input
	judp(unsigned int& mtu,
		 uint16_t& source,
		 uint16_t& destination,
		 std::string& file);

	virtual ~judp() {}

	// This function is for use with the constructors that accept
	// a file. Encap will produce a packet each time it's called from
	// the data found in the file. When all data is exhausted, it will
	// return true. This function will throw if the private member
	// m_input is NULL
	void encap_packet(std::shared_ptr<jarray<uint8_t>>& output);

    // This function is for use with the constructors that accept
    // a file. Decap will extract the data and write it to the
    // file specificed in the constuctor. Will throw if m_file
    // does not exist
    void decap_packet(std::shared_ptr<jarray<uint8_t>>& input);

	// These two functions are for use with the constructors without
	// a file handle. Encap will produce a packet with the payload passed
	// in while Decap will produce a payload from the packet passed in.
	// Encap will throw if m_input is not NULL when it is called
	void encap_packet(std::shared_ptr<jarray<uint8_t>>& input,
			          std::shared_ptr<jarray<uint8_t>>& output);

	void decap_packet(std::shared_ptr<jarray<uint8_t>>& input,
			          std::shared_ptr<jarray<uint8_t>>& output);

	// Functions to update fields specific to UDP. Will throw if function
	// is called for a field that doesn't exist in the version of UDP this
	// UDP is configured for
	void update_source(uint16_t& source);
	void update_dest(uint16_t& destination);
	void update_udphdr(jarray<uint8_t>& udphdr);

	uint16_t get_source();
	uint16_t get_dest();
	jarray<uint8_t> get_udphdr();

private:

	// don't use these
	judp();
	judp(const judp& judp);

	void init(uint16_t& source, uint16_t& destination);

	// array for UDP header
	jarray<uint8_t> m_udphdr;
};

#endif /* JUDP_H_ */
