/*
 * jip.cpp
 *
 *  Created on: July 19, 2015
 *  Author: John Peter Greninger
 *  Copyright 2015
 */
#include "../include/jip.h"

//
/// IPv4 constructor
jip::jip(unsigned int& mtu,
         uint32_t& source,
         uint32_t& destination,
         uint8_t& nh) : jprotocol(mtu),
                        m_ver(IPv4)
{
    ipinit(source, destination, nh);
}

//
/// IPv6 constructor
jip::jip(unsigned int& mtu,
         uint64_t& source,
         uint64_t& destination,
         uint8_t& nh) : jprotocol(mtu),
                        m_ver(IPv6)
{
    ipinit(source, destination, nh);
}

//
/// IPv4 constructor with MTU and file inputs
jip::jip(unsigned int& mtu,
         uint32_t& source,
         uint32_t& destination,
         uint8_t& nh,
         std::string& input) : jprotocol(mtu, input),
                               m_ver(IPv4)
{
    ipinit(source, destination, nh);
}

//
/// IPv6 constructor with MTU and file inputs
jip::jip(unsigned int& mtu,
         uint64_t& source,
         uint64_t& destination,
         uint8_t& nh,
         std::string& input) : jprotocol(mtu, input),
                               m_ver(IPv6)
{
    ipinit(source, destination, nh);
}

void jip::encap_packet(std::shared_ptr<jarray<uint8_t>>& output) {

    // perform the IPv4 header checksum
    if (m_ver == IPv4) {
        jarray<uint8_t> chksum = checksum(IPv4, ENCAP, m_iphdr);
        m_iphdr[10] = chksum[0];
        m_iphdr[11] = chksum[1];
    }
}

void jip::encap_packet(std::shared_ptr<jarray<uint8_t>>& input, std::shared_ptr<jarray<uint8_t>>& output) {

    unsigned int size = input->get_size();

    // perform the IPv4 header checksum
    if (m_ver == IPv4) {
        size += ((m_iphdr[0] & 0x0F) * 4);
    }
    else if (m_ver == IPv6) {
        // may contain extension headers
        size += (m_iphdr - 40);
    }

    // update the packet length in the header
    update_pktlen(size);

    // perform the IPv4 header checksum
    if (m_ver == IPv4) {
        jarray<uint8_t> chksum = checksum(IPv4, ENCAP, m_iphdr);
        m_iphdr[10] = chksum[0];
        m_iphdr[11] = chksum[1];
    }

    // add the header to the output
    output->update(0, m_iphdr);

    // add the payload
    output->update(m_iphdr.get_size(), *input);

}

void jip::decap_packet(std::shared_ptr<jarray<uint8_t>>& input, std::shared_ptr<jarray<uint8_t>>& output) {

    // perform the IPv4 header checksum
    if (m_ver == IPv4) {
        jarray<uint8_t> chk = checksum(IPv4, DECAP, *input);
        if ((chk[0] == 0) && (chk[1] == 0)) {
            output->update(0, input->extract(((input[0] & 0x0F) * 4), (input->get_size() - ((input[0] & 0x0F) * 4))));
        }
        else {
            std::cerr << "In jip::decap_packet(), checksum failed " << std::endl
                      << " checksum in packet : " << HEX(((input[10] << 8) | input[11]), 2);
        }

    }
    else if (m_ver == IPv6) {
        unsigned int size = ((input[4] << 8) | input[5]);
        unsigned int start = input->get_size() - size;
        jarray<uint8_t> extract = input->extract(start, size);
        output->update(0, extract);
    }
}

void jip::update_iphdr(jarray<uint8_t>& iphdr) {
    m_iphdr = iphdr;
}

void jip::update_version(protocol_t& version) {
    m_ver = version;
}

void jip::update_dscp_ecn(uint8_t& dscp_ecn) {
    if (m_ver == IPv4) {
        m_iphdr[1] = dscp_ecn;
    }
    else if (m_ver == IPv6) {
        m_iphdr[0] |= ((dscp_ecn >> 4) & 0x0F);
        m_iphdr[1] |= ((dscp_ecn << 4) & 0xF0);
    }
    else {
        std::cerr << "In jip::update_dscp_ecn(), expecting IPv4 or IPv6 but version is : " << m_ver);
    }
}

void jip::update_flow_label(uint32_t& label) {
    if (m_ver == IPv6) {
        m_iphdr[1] |= ((label >> 16) & 0x0F);
        m_iphdr[2]  = ((label >> 8) & 0xFF);
        m_iphdr[3]  = (label & 0xFF);
    }
    else {
        std::cerr << "In jip::update_flow_label(), only IPv6 supports a flow label but version is : " << m_ver);
    }
}

void jip::update_nh(uint8_t& nh) {
    if (m_ver == IPv4) {
        m_iphdr[9] = nh;
    }
    else if (m_ver == IPv6) {
        m_iphdr[6] = nh;
    }
    else {
        std::cerr << "In jip::update_nh(), expecting IPv4 or IPv6 but version is : " << m_ver);
    }
}

void jip::update_ttl_hoplimit(uint8_t& ttl_hop) {
    if (m_ver == IPv4) {
        m_iphdr[8] = ttl_hop;
    }
    else if (m_ver == IPv6) {
        m_iphdr[7] = ttl_hop;
    }
    else {
        std::cerr << "In jip::update_ttl_hoplimit(), expecting IPv4 or IPv6 but version is : " << m_ver);
    }
}

void jip::update_flags(uint8_t& flags) {
    if (m_ver == IPv4) {
       m_iphdr[6] |= (flags << 1);
    }
    else {
        std::cerr << "In jip::update_flags(), only IPv4 supports a flags field but version is : " << m_ver);
    }
}

void jip::update_pktlen(unsigned int& length) {
    if (m_ver == IPv4) {
        // IPv4 pktlen is length of total packet
        m_iphdr[2] = ((length >> 8) & 0xFF);
        m_iphdr[3] = (length & 0xFF);
    }
    else if (m_ver == IPv6) {
        // IPv6 pktlen is length of payload and extension headers
        if (length > 0xFFFF) {
            m_iphdr[4] = 0;
            m_iphdr[5] = 0;
            add_extension(JUMBOGRAM, length);
        }
        else {
            m_iphdr[4] = ((length >> 8) & 0xFF);
            m_iphdr[5] = (length & 0xFF);
        }
    }
    else {
        std::cerr << "In jip::update_pktlen(), expecting IPv4 or IPv6 but version is : " << m_ver);
    }
}

void jip::add_extension(ext_t& extension, unsigned int& length) {
    if (extension == JUMBOGRAM) {
        // length must be total length minus 40
        jarray<uint8_t> ext(1, 0xC2);
        jarray<uint8_t> len(length);
        ext.push_back(0x04);
        ext.append(len);
        m_iphdr.append(ext);
    }
    else {
        std::cerr << "In jip::add_options(), not yet implemented";
    }
}

jarray<uint8_t> jip::get_iphdr() {
    return m_iphdr;
}

protocol_t jip::get_version() {
    return m_ver;
}

uint8_t jip::get_dscp_ecn() {
    uint8_t version = 0;

    if (m_ver == IPv4) {
        version = m_iphdr[1];
    }
    else if (m_ver == IPv4) {
        version = (((m_iphdr[0] & 0x0F) << 4) | ((m_iphdr[0] & 0xF0) >> 4));
    }
    else {
        std::cerr << "In jip::get_dscp_ecn(), expecting IPv4 or IPv6 but version is : " << m_ver);
    }
    return version;
}

uint32_t jip::get_label() {
    uint32_t label = 0;

    if (m_ver == IPv6) {
        label = (((m_iphdr[1] & 0x0F) << 16) | (m_iphdr[2] << 8) | m_iphdr[3]);
    }
    else {
       std::cerr << "In jip::get_label(), only IPv6 supports a flow label but version is : " << m_ver);
    }
    return label;
}

uint8_t jip::get_nh() {
    if (m_ver == IPv4) {
        return m_iphdr[9];
    }
    else if (m_ver == IPv6) {
        return m_iphdr[6];
    }
    else {
        std::cerr << "In jip::get_nh(), expecting IPv4 or IPv6 but version is : " << m_ver);
        return 0;
    }
}

uint8_t jip::get_ttl_hoplimit() {
    if (m_ver == IPv4) {
        return m_iphdr[8];
    }
    else if (m_ver == IPv6) {
        return m_iphdr[7];
    }
    else {
        std::cerr << "In jip::get_ttl_hoplimit(), expecting IPv4 or IPv6 but version is : " << m_ver);
        return 0;
    }
}

uint8_t jip::get_flags() {
    if (m_ver == IPv4) {
        return ((m_iphdr[6] & 0xE0) >> 5);
    }
    else {
        std::cerr << "In jip::get_nh(), only IPv4 supports a flags field but version is : " << m_ver);
        return 0;
    }
}

