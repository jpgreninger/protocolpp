/*
 * judp.cpp
 *
 *  Created on: Feb 28, 2015
 *  Author: John Peter Greninger
 *  Copyright 2015
 */
#include "../include/judp.h"

judp::judp(unsigned int& mtu,
		   uint16_t& source,
		   uint16_t& destination) : jprotocol(mtu)
{
	init(source, destination);
}


judp::judp(unsigned int& mtu,
		   uint16_t& source,
		   uint16_t& destination,
		   std::string& file) : jprotocol(mtu, file)
{
	init(source, destination);
}

void judp::init(uint16_t& source, uint16_t& destination) {
	m_udphdr = jarray<uint8_t>(static_cast<unsigned int>(4));
	m_udphdr[0] = ((source >> 8) & 0xFF);
	m_udphdr[1] = (source & 0xFF);
	m_udphdr[2] = ((destination >> 8) & 0xFF);
	m_udphdr[3] = (destination & 0xFF);
}

void judp::update_source(uint16_t& source) {
    m_udphdr[0] = ((source >> 8) & 0xFF);
	m_udphdr[1] = (source & 0xFF);

	return;
}

void judp::update_dest(uint16_t& destination) {
	m_udphdr[2] = ((destination >> 8) & 0xFF);
	m_udphdr[3] = (destination & 0xFF);

	return;
}

void judp::update_udphdr(jarray<uint8_t>& udphdr) {
    if (udphdr.get_size() != 8) {
        std::cerr << "In judp::update_udphdr(), new UDP header is incorrect size of : " << udphdr.get_size();
    }
    else {
        m_udphdr = udphdr;
    }

	return;
}

uint16_t judp::get_source() {
	uint32_t result = ((m_udphdr[0] << 8) | m_udphdr[1]);

	return result;
}

uint16_t judp::get_dest() {
	uint32_t result = ((m_udphdr[2] << 8) | m_udphdr[3]);

	return result;
}

jarray<uint8_t> judp::get_udphdr() {
	return m_udphdr;
}

void judp::encap_packet(std::shared_ptr<jarray<uint8_t>>& output) {
    // create the packet with header and data
    jarray<uint8_t> temp(m_udphdr);
    temp.append(get_data());

    // copy the packet to the output pointer
    for (unsigned int i=0; i<temp.get_size(); i++) {
        output->push_back(temp[i]);
    }
}

void judp::decap_packet(std::shared_ptr<jarray<uint8_t>>& input) {
    // check the packet for changes
    jarray<uint8_t> check = checksum(UDP, DECAP, *input);

    // if the checksum is correct write the data to the file, otherwise signal an error
    if ((check[0] == 0) && (check[1] == 0)) {
        put_data(input->extract(8, (input->get_size()-8)));
    }
    else {
        std::cerr << "CHECKSUM FOR UDP PACKET FAILED, VALUE : " << std::hex << check.to_string() << std::endl;
    }
}

void judp::encap_packet(std::shared_ptr<jarray<uint8_t>>& input,
		                std::shared_ptr<jarray<uint8_t>>& output)
{
    // create the packet from the header and input
	jarray<uint8_t> out = m_udphdr;
	out.append(*input);

	uint32_t len = out.get_size();
	out.insert(4, jarray<uint8_t>(len).extract(2,2));
	out.insert(6, checksum(UDP, ENCAP, out));

    // copy the packet to the output pointer
    for (unsigned int i=0; i<out.get_size(); i++) {
        output->push_back(out[i]);
    }
}

void judp::decap_packet(std::shared_ptr<jarray<uint8_t>>& input,
		                std::shared_ptr<jarray<uint8_t>>& output)
{
    // check the packet for changes
	jarray<uint8_t> check = checksum(UDP, DECAP, *input);

    // if the checksum is correct copy the payload to output, otherwise signal an error
	if ((check[0] == 0) && (check[1] == 0)) {
	    output->append(input->extract(8, (input->get_size()-8)));
	}
	else {
		std::cerr << "CHECKSUM FOR UDP PACKET FAILED, VALUE : " << std::hex << check.to_string() << std::endl;
	}
}
