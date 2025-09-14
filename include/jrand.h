/*
 * jrand.h
 *
 *  Created on: Feb 8, 2015
 *  Author: John Peter Greninger
 *  Copyright 2015
 */

#ifndef JRAND_H_
#define JRAND_H_

#include "jarray.h"
#include "mtrand.h"

class jrand {

	public:

		jrand();

		jrand(unsigned int& myseed);

		jrand(const unsigned long *newseed, int& size);

		virtual ~jrand() { }

		jarray<uint8_t> getbytes(unsigned int& amount);

		jarray<uint32_t> getwords(unsigned int& amount);

        uint8_t  get_u8();

	    uint16_t get_u16();

		uint32_t get_u32();

        uint64_t get_u64();

		void seed(unsigned long& myseed);

		void seed(const unsigned long *newseed, int& size);

	private:

		// don't use these
		jrand(const jrand &jrand);

		MTRand_int32 m_rand;
};

//
/// Standard constructor
jrand::jrand() : m_rand() { }

//
/// Constructor with uint32_t
jrand::jrand(unsigned int& myseed) : m_rand(myseed) { }

//
/// Constructor with array of uint32_t
jrand::jrand(const unsigned long *newseed, int& size) : m_rand(newseed, size) { }

//
/// Request a vector of random data as bytes
jarray<uint8_t> jrand::getbytes(unsigned int& amount) {
	jarray<uint8_t> result(amount);
	unsigned long temp = 0;

	for (unsigned int i = 0; i < amount; i = i + 4) {
		temp = m_rand();

		if (i < result.get_size()) {
			result[i] = ((temp >> 24) & 0xFF);
		}
		if ((i + 1) < result.get_size()) {
			result[(i + 1u)] = ((temp >> 16) & 0xFF);
		}
		if ((i + 2) < result.get_size()) {
			result[(i + 2u)] = ((temp >> 8) & 0xFF);
		}
		if ((i + 3) < result.get_size()) {
			result[(i + 3u)] = (temp & 0xFF);
		}
	}

	return result;
}

//
/// Request a vector of random data as uint32_t
jarray<uint32_t> jrand::getwords(unsigned int& amount) {
	jarray<uint32_t> result(amount);

	for (int i = 0; i < amount; i++) {
		result[i] = m_rand();
	}

	return result;
}

//
/// Request a single uint8_t
uint8_t jrand::get_u8() {
    return (m_rand() & 0xFF);
}

//
/// Request a single uint16_t
uint16_t jrand::get_u16() {
    return (m_rand() & 0xFFFF);
}

//
/// Request a single uint32_t
uint32_t jrand::get_u32() {
    return m_rand();
}

//
/// Request a single uint64_t
uint64_t jrand::get_u64() {
    uint64_t result = m_rand();
    result = ((result << 32) | m_rand());
	return result;
}

//
/// Reseed using a uint32_t
void jrand::seed(unsigned long& myseed) {
	m_rand.seed(myseed);
}

//
/// Reseed using an array of uint32_t
void jrand::seed(const unsigned long *newseed, int& size) {
	m_rand.seed(newseed, size);
}

#endif /* JRAND_H_ */
