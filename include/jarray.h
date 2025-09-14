/*
 * jarray.h
 *
 *  Created on: Feb 14, 2015
 *  Author: John Peter Greninger
 *  Copyright 2015
 */

#ifndef JARRAY_H_
#define JARRAY_H_

#include <vector>
#include <memory>
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include <string>
#include <iomanip>

template <typename T> class jarray {

public:

    jarray();

	jarray(unsigned int size);

//	jarray(T value);

	jarray(unsigned int size, T& value);

	jarray(const jarray<T>& jarray);

	jarray(const std::string& rhs);

	jarray(const std::vector<T>& rhs);

	virtual ~jarray() {}

	unsigned int get_size();

	bool empty();

	jarray<T> split(unsigned int elements);

	jarray<T> extract(unsigned int start, unsigned int elements);

	void push_back(T& rhs);

	T pop_back();

	void append(jarray<T>& rhs);

	void insert(unsigned int index, jarray<T>& rhs);

	void update(unsigned int index, jarray<T>& rhs);

	jarray<T> serial_and(jarray<T>& rhs);

	jarray<T> serial_add(jarray<T>& rhs);

	jarray<T> serial_addc(jarray<T>& rhs);

	jarray<T> serial_or(jarray<T>& rhs);

	jarray<T> serial_xor(jarray<T>& rhs);

	std::string to_string(bool printable=false);

	bool operator==(jarray<T>& rhs);

	T& operator[](unsigned int index);

	const T& operator[](unsigned int index) const;

private:

	std::vector<T> m_data;
};

//
/// Standard constructor
template <typename T>
jarray<T>::jarray() : m_data(0)
{}

//
/// Constructor for given size
template <typename T>
jarray<T>::jarray(unsigned int size) : m_data(size)
{}

//
/// Constructor with constant
template <typename T>
jarray<T>::jarray(T value) : m_data(0)
{
	m_data.resize(sizeof(T));

	for (unsigned int i=0; i<sizeof(T); i++) {
		m_data[m_data.size()-i-1] = ((value >> (8*i)) & 0xFF);
	}
}

//
/// Constructor to initialize with given value and size
template <typename T>
jarray<T>::jarray(unsigned int size, T& value) : m_data(size)
{
	for (unsigned int i=0; i<size; i++) {
		m_data[i] = value;
	}
}

//
/// Copy Constructor
template <typename T>
jarray<T>::jarray(const jarray<T>& rhs) : m_data(0) {
	jarray<T> tmp(rhs);
	m_data.resize(tmp.get_size());

	for (unsigned int i=0; i<m_data.size(); i++) {
		m_data[i] = tmp[i];
	}
}

//
/// Constructor to initialize from string
template <typename T>
jarray<T>::jarray(const std::string& rhs) : m_data(0)
{
	std::istringstream myhex(rhs);
	T myvar;

	// while there's still data in the string, convert to an array
	while (myhex.good()) {
		myhex >> std::setw(sizeof(T)) >> std::setfill('0') >> std::hex >> myvar;
		m_data.push_back(myvar);
	}
}

//
/// Constructor to initialize from vector
template <typename T>
jarray<T>::jarray(const std::vector<T>& rhs) : m_data(rhs)
{}

//
/// returns the size of the array
template <typename T>
unsigned int jarray<T>::get_size() {
	return m_data.size();
}

//
/// returns true if size of array is zero
template <typename T>
bool jarray<T>::empty() {
	return m_data.empty();
}

//
/// splits number of elements from front of this array and returns them
/// modifies the original array to the new size
template <typename T>
jarray<T> jarray<T>::split(unsigned int elements) {
	jarray<T> result(elements);

	// boundary check the split
	if (elements > m_data.size()) {
		std::cerr << "Number of elements requested in ::split() exceeds array length" << std::endl;
		return result;
	}

	for (unsigned int i=0; i<elements; i++) {
		result[i] = m_data[i];
	}

	m_data.erase(m_data.begin(), m_data.begin()+elements);

	return result;
}

//
/// extracts elements at index and returns them
template <typename T>
jarray<T> jarray<T>::extract(unsigned int index, unsigned int elements) {
	jarray<T> result(elements);

	// boundary check the extraction
	if ((index+elements) > m_data.size()) {
		std::cerr << "Number of elements in ::extract() : " << (index+elements) << " goes beyond the end of the array : " << m_data.size() << std::endl;
		return result;
	}

	for (unsigned int i=index; i<index+elements; i++) {
		result[i] = m_data[i];
	}

	return result;
}

//
/// adds the element to the end of the array
template <typename T>
void jarray<T>::push_back(T& rhs) {
	m_data.push_back(rhs);
}

//
/// returns the element from the end of the array
template <typename T>
T jarray<T>::pop_back() {
	return m_data.pop_back();
}

//
/// appends rhs onto this array
template <typename T>
void jarray<T>::append(jarray<T>& rhs) {
	unsigned int curr = m_data.size();

	m_data.resize(m_data.size()+rhs.get_size());

	for (unsigned int i=curr; i<m_data.size(); i++) {
		m_data[i] = rhs[i-curr];
	}
}

//
/// inserts rhs into this array, resizes if necessary
template <typename T>
void jarray<T>::insert(unsigned int index, jarray<T>& rhs) {
	// create a new vector with the correct size
	std::vector<T> temp(rhs.get_size() + m_data.size());

	// insert the new elements into the middle of the old ones
	for (unsigned int i=0; i<temp.size(); i++) {
		if (i < index) {
			temp[i] = m_data[i];
		}
		else if ((i-index) < (index + rhs.get_size())) {
			temp[i] = rhs(i-index);
		}
		else {
			temp[i] = m_data[(i-rhs.get_size())];
		}
	}

	// assign the internal element with the new vector
	m_data = temp;
}

//
/// updates the array starting at index with the
/// data found in rhs, resizes if necessary
template <typename T>
void jarray<T>::update(unsigned int index, jarray<T>& rhs) {
    // if the new array will fall off the end, resize
	if ((index + rhs.get_size()) > m_data.size()) {
		m_data.resize(m_data.size() + ((index + rhs.get_size()) - m_data.size()));
	}

    // update the current contexts with the new ones
	for (unsigned int i=index; i<m_data.size(); i++) {
		m_data[i] = rhs[i-index];
	}
}

//
/// performs serial AND of this array and rhs and returns result
template <typename T>
jarray<T> jarray<T>::serial_and(jarray<T>& rhs) {
	jarray<T> result(rhs.get_size());

	// check that arrays are the same size
	if (m_data.size() != rhs.get_size()) {
		std::cout << "In ::serial_and, arrays must be the same size" << std::endl;
		return result;
	}

	for (unsigned int i=0; i<rhs.get_size(); i++) {
		result[i] = m_data[i] & rhs[i];
	}

	return result;
}

//
/// performs serial ADD between this array and rhs then returns result
template <typename T>
jarray<T> jarray<T>::serial_add(jarray<T>& rhs) {
	jarray<T> result(rhs.get_size());

	// check that arrays are the same size
	if (m_data.size() != rhs.get_size()) {
		std::cout << "In ::serial_add, arrays must be the same size" << std::endl;
		return result;
	}

	for (unsigned int i=0; i<rhs.get_size(); i++) {
		result[i] = m_data[i] + rhs[i];
	}

	return result;
}

//
/// performs serial ADDC between this array and rhs then returns result
template <typename T>
jarray<T> jarray<T>::serial_addc(jarray<T>& rhs) {
	jarray<T> result(rhs.get_size());
	unsigned int carry = 0;

	// check that arrays are the same size
	if (m_data.size() != rhs.get_size()) {
		std::cout << "In ::serial_addc, arrays must be the same size" << std::endl;
		return result;
	}

	for (unsigned int i=rhs.get_size(); i>=0; --i) {

		if (carry) {
		    result[i] = ((m_data[i] + rhs[i] + carry) & 0xFF);
		}
		else {
		    result[i] = ((m_data[i] + rhs[i]) & 0xFF);
		}
		carry = m_data[i] + rhs[i] + ((carry) ? carry : 0);
		carry >>= 8;
	}

	return result;
}

//
/// performs serial OR between this array and rhs, returns result
template <typename T>
jarray<T> jarray<T>::serial_or(jarray<T>& rhs) {
	jarray<T> result(rhs.get_size());

	// check that arrays are the same size
	if (m_data.size() != rhs.get_size()) {
		std::cout << "In ::serial_or, arrays must be the same size" << std::endl;
		return result;
	}

	for (unsigned int i=0; i<rhs.get_size(); i++) {
		result[i] = m_data[i] | rhs[i];
	}

	return result;
}

//
/// performs serial XOR between this array and rhs, returns result
template <typename T>
jarray<T> jarray<T>::serial_xor(jarray<T>& rhs) {
	jarray<T> result(rhs.get_size());

	// check that arrays are the same size
	if (m_data.size() != rhs.get_size()) {
		std::cout << "In ::serial_xor, arrays must be the same size" << std::endl;
		return result;
	}

	for (unsigned int i=0; i<rhs.get_size(); i++) {
		result[i] = m_data[i] ^ rhs[i];
	}

	return result;
}

//
/// converts this array to string and returns result
template <typename T>
std::string jarray<T>::to_string(bool printable) {
	std::ostringstream myhex;

	for(unsigned int i=0; i<m_data.size(); i++) {
		myhex << ((sizeof(m_data[i]) == 4) ? std::setw(4) : std::setw(2)) << std::setfill('0') << std::hex << +m_data[i];

		// if we're priting the array, make it pretty
		if (printable) {
		    // if we're not on the last element, insert items
		    if ((i+1) != m_data.size()) {
				if (sizeof(m_data[i]) == 1) {
					if (((i + 1) % 16) == 0) {
						myhex << "\n ";
					}
					else if (((i + 1) % 4) == 0) {
						myhex << "_";
					}
				}
				else if (sizeof(m_data[i]) == 4) {
					if (((i + 1) % 4) == 0) {
						myhex << "\n ";
					}
					else if (((i + 1) % 1) == 0) {
						myhex << "_";
					}
				}
			}
		}
	}

	std::string result(myhex.str());

	// if we're printing the array, make it pretty
	if (printable) {
	    result.insert(0, "[");
	    result.append("]\n");
	}

	return result;
}

//
/// compares this array to rhs to determine if they are equal
template <typename T>
bool jarray<T>::operator==(jarray<T>& rhs) {
	if (m_data.size() != rhs.get_size()) {
		return false;
	}

	for(unsigned int i=0; i<rhs.get_size(); i++) {
		if (m_data[i] != rhs[i]) {
			return false;
		}
	}

	return true;
}

//
/// returns value at index in this array
template <typename T>
T& jarray<T>::operator[](unsigned int index) {
	return m_data[index];
}

//
/// returns value at index in this array
template <typename T>
const T& jarray<T>::operator[](unsigned int index) const {
	return m_data[index];
}

#endif /* JARRAY_H_ */
