/*
 * jtcp.cpp
 *
 *  Created on: Mar 8, 2015
 *  Author: John Peter Greninger
 *  Copyright 2015
 */
#include "../include/jtcp.h"

// constructor for normal TCP
jtcp::jtcp(unsigned int& mtu,
		   uint16_t& source,
		   uint16_t& destination) : jprotocol(mtu)
{
    init(source, destination);
}

// constructor for normal TCP with file input
jtcp::jtcp(unsigned int& mtu,
		   uint16_t& source,
		   uint16_t& destination,
		   std::string& file) : jprotocol(mtu, file)
{
    init(source, destination);
}

void jtcp::init(uint16_t& source, uint16_t& destination) {
    // initialization routine
    m_tcphdr = jarray<uint8_t>(20);
    m_tcphdr[0] = ((source >> 8) & 0xFF);
    m_tcphdr[1] = (source & 0xFF);
    m_tcphdr[2] = ((destination >> 8) & 0xFF);
    m_tcphdr[3] = (destination & 0xFF);
    m_tcphdr[13] = 0x02;
}

void jtcp::encap_packet(std::shared_ptr<jarray<uint8_t>>& output) {
	// get the data from the file, size the packet
	jarray<uint8_t> input(get_data());
	jarray<uint8_t> packet(m_tcphdr.get_size() + input.get_size());
    jarray<uint8_t> result;

	// update the ACK number so the header is correct
	update_acknum(input.get_size());

	// construct the packet
	packet.insert(0, m_tcphdr);
	packet.insert(m_tcphdr.get_size(), input);
    result = checksum(TCP, ENCAP, packet);
	packet.insert(16, result);

	// update the SEQ number for next packet
	update_seqnum(input.get_size());

	// pass the packet to the caller
	output->insert(0, packet);
}

void jtcp::decap_packet(std::shared_ptr<jarray<uint8_t>>& input) {

    // verify the packet didn't change
    jarray<uint8_t> chk = checksum(TCP, DECAP, *input);

    // if the checksum is good...
    if ((chk[0] == 0) && (chk[1] == 0)) {

        // extract the payload based on "offset" field
        jarray<uint8_t> payload = input->extract((((*input)[12] & 0xF0) >> 4), (input->get_size() - (((*input)[12] & 0xF0) >> 4)));

        // extract the ACK and SEQ numbers
        update_acknum(((*input)[8] << 24) | ((*input)[9] << 16) | ((*input)[10] << 8) | (*input)[11]);

        // check the window size, readjust if necessary
        update_mtu(((*input)[14] << 8) | (*input)[15]);

        // check the flags
        if ((*input)[12] & 0x0E) {
            std::cout << "Reserved bits in the header where set" << std::endl;
        }
        if (!((*input)[13] & 0x20)) {
            std::cout << "ACK bit not set" << std::endl;
        }
        if ((*input)[13] & 0x08) {
            std::cout << "PUSH buffered data to receiving application" << std::endl;
        }
        if ((*input)[13] & 0x04) {
            std::cout << "RESET of connection requested" << std::endl;
        }
        if ((*input)[13] & 0x02) {
            std::cout << "SYN bit set" << std::endl;
        }
        if ((*input)[13] & 0x01) {
            std::cout << "FINISH detected" << std::endl;
        }

        // write payload to file
        put_data(payload);
    }
    else {
        std::cerr << "In jtcp::decap_packet() with file, invalid checksum " << std::endl
                  << "expect : 0x" << chk.to_string() << std::endl
                  << "recved : 0x" << (input->extract(16,2)).to_string();
    }
}

void jtcp::encap_packet(std::shared_ptr<jarray<uint8_t>>& input, std::shared_ptr<jarray<uint8_t>>& output) {
	jarray<uint8_t> packet(m_tcphdr.get_size() + input->get_size());

	packet.update(0, m_tcphdr);
	packet.update(m_tcphdr.get_size(), *input);
    jarray<uint8_t> chksum = checksum(TCP, ENCAP, packet);
	packet.update(16, chksum);

	// update the SEQ number for next packet
	update_seqnum(input->get_size());

    // pass the packet to the caller
	output->update(0, packet);
}

void jtcp::decap_packet(std::shared_ptr<jarray<uint8_t>>& input, std::shared_ptr<jarray<uint8_t>>& output) {

    // verify the packet didn't change
    jarray<uint8_t> chk = checksum(TCP, DECAP, *input);

    // if the checksum is good...
    if ((chk[0] == 0) && (chk[1] == 0)) {
        jarray<uint8_t> payload = input->extract((((*input)[12] & 0xF0) >> 4), (input->get_size() - (((*input)[12] & 0xF0) >> 4)));

        // need to ACK with the next seqnum expected
        update_acknum(((*input)[8] << 24) | ((*input)[9] << 16) | ((*input)[10] << 8) | (*input)[11]);

        // check the window size, readjust if necessary
        update_mtu(((*input)[14] << 8) | (*input)[15]);

        // check flags
        if ((*input)[12] & 0x0E) {
            std::cout << "Reserved bits in the header where set" << std::endl;
        }
        if (!((*input)[13] & 0x20)) {
            std::cout << "ACK bit not set" << std::endl;
        }
        if ((*input)[13] & 0x08) {
            std::cout << "PUSH buffered data to receiving application" << std::endl;
        }
        if ((*input)[13] & 0x04) {
            std::cout << "RESET of connection requested" << std::endl;
        }
        if ((*input)[13] & 0x02) {
            std::cout << "SYN bit set" << std::endl;
        }
        if ((*input)[13] & 0x01) {
            std::cout << "FINISH detected" << std::endl;
        }

        output->update(0, payload);
    }
    else {
        std::cerr << "In jtcp::decap_packet() with file, invalid checksum " << std::endl
        << "expect : 0x" << chk.to_string() << std::endl
        << "recved : 0x" << (input->extract(16,2)).to_string();
    }
}

void jtcp::update_source(uint16_t& source) {
    m_tcphdr[0] = ((source >> 8) & 0xFF);
    m_tcphdr[1] = (source & 0xFF);
}

void jtcp::update_dest(uint16_t& destination) {
	m_tcphdr[2] = ((destination >> 8) & 0xFF);
	m_tcphdr[3] = (destination & 0xFF);
}

void jtcp::update_tcphdr(jarray<uint8_t>& tcphdr) {
	m_tcphdr = tcphdr;
}

void jtcp::update_seqnum(unsigned int& seqnum) {
	unsigned int curr = ((m_tcphdr[4] << 24) | (m_tcphdr[5] << 16) | (m_tcphdr[6] << 8) | m_tcphdr[7]);
	curr += (seqnum-curr);
	m_tcphdr[4] = ((curr >> 24) & 0xFF);
	m_tcphdr[5] = ((curr >> 16) & 0xFF);
	m_tcphdr[6] = ((curr >> 8 ) & 0xFF);
	m_tcphdr[7] = (curr & 0xFF);
}

void jtcp::update_acknum(unsigned int& acknum) {
	unsigned int curr = ((m_tcphdr[8] << 24) | (m_tcphdr[9] << 16) | (m_tcphdr[10] << 8) | m_tcphdr[11]);
	curr += ((acknum-curr) + 1);
	m_tcphdr[8] = ((curr >> 24) & 0xFF);
	m_tcphdr[9] = ((curr >> 16) & 0xFF);
	m_tcphdr[10] = ((curr >> 8 ) & 0xFF);
	m_tcphdr[11] = (curr & 0xFF);
}

void jtcp::update_window(uint16_t& size) {
	m_tcphdr[14] = ((size >> 8) & 0xFF);
	m_tcphdr[15] = (size & 0xFF);
}

void jtcp::update_flags(uint32_t& flags) {
    m_tcphdr[12] |= ((flags >> 8) & 0x01);
	m_tcphdr[13] |= (flags & 0xFF);
}

uint16_t jtcp::get_source() {
	uint16_t src = ((m_tcphdr[0] << 8) | m_tcphdr[1]);
	return src;
}

uint16_t jtcp::get_dest() {
	uint16_t dst = ((m_tcphdr[2] << 8) | m_tcphdr[3]);
	return dst;
}

jarray<uint8_t> jtcp::get_tcphdr() {
	return m_tcphdr;
}

uint32_t jtcp::get_seqnum() {
	uint32_t num = ((m_tcphdr[4] << 24) | (m_tcphdr[5] << 16) | (m_tcphdr[6] << 8) | m_tcphdr[7]);
	return num;
}

uint32_t jtcp::get_acknum() {
	uint32_t ack = ((m_tcphdr[8] << 24) | (m_tcphdr[9] << 16) | (m_tcphdr[10] << 8) | m_tcphdr[11]);
	return ack;
}

unsigned int jtcp::get_window() {
	unsigned int win = ((m_tcphdr[14] << 8) | m_tcphdr[15]);
	return win;
}

uint16_t jtcp::get_flags() {
	uint16_t flags = (((m_tcphdr[12] & 0x01) << 8) | m_tcphdr[13]);
	return flags;
}

unsigned int jt