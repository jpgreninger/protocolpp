/*
 * jbuilder.cpp
 *
 *  Created on: Feb 28, 2015
 *  Author: John Peter Greninger
 *  Copyright 2015
 */
#include <memory>
#include "../include/jarray.h"
#include "../include/jrand.h"
#include "../include/jprotocol.h"
#include "../include/jtcp.h"
#include "../include/judp.h"


int main() {

	unsigned int seed = 10;
	unsigned int mtu = 50;

	jrand myrand(seed);

	uint16_t src = myrand.get_u16();
	uint16_t dst = myrand.get_u16();

	judp udp(mtu, src, dst);

	std::shared_ptr<jarray<uint8_t>> input = std::shared_ptr<jarray<uint8_t>>(new jarray<uint8_t>(myrand.getbytes(mtu)));
	std::shared_ptr<jarray<uint8_t>> output = std::shared_ptr<jarray<uint8_t>>(new jarray<uint8_t>(mtu));

	udp.encap_packet(input, output);

	std::cout << "OUTPUT PACKET : " << output->to_string() << std::endl;
	// test GIT
}
