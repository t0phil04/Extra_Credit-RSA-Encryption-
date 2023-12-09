#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <ctime>
#include <cmath>

#define STRIDE 2

using namespace std;

vector <int> trialsDivision(int n) {
	vector <int> primeFactors_;
	int currentDivisor = 2;

	while (n > 1)
	{
		if (n % currentDivisor == 0)
		{
			// Adds the current divisor where n is divisible by currentDivisor to the vector
			primeFactors_.push_back(currentDivisor);
			n = n / currentDivisor;
		}
		else
		{
			currentDivisor++; // Increments the divisor by 1
		}
	}
	return primeFactors_;
}

int EU_Algorithm(int e_publicKey_, int phi_n_) {
	int tmp_a, tmp_b, remainder;

	if (e_publicKey_ > phi_n_){
		tmp_a = e_publicKey_;
		tmp_b = phi_n_;
	} else {
		tmp_a = phi_n_;
		tmp_b = e_publicKey_;
	}
	while (tmp_b > 0) {
		remainder = tmp_a % tmp_b;
		tmp_a = tmp_b;
		tmp_b = remainder;
	}

	return tmp_a;
}

bool checkPrime(vector <int> check) {
	if (check.size() > 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}


int mult_Inverse(int phi, int e) {

	unsigned long prod;
	for (size_t d = 1; d < phi; d++)
	{
		prod = e * d;
		if ((prod % phi) == (1 % phi))
		{
			return d;
		}
	}
	return 0;
	//return d_decrypt;
}

template <class T>
T mod_power(T x, T y, T p)
{
	//Source https://www.geeksforgeeks.org/modular-exponentiation-power-in-modular-arithmetic/#
	T res = 1;

	x = x % p; // Update x if it is more than or
	// equal to p

	if (x == 0) return 0; // In case x is divisible by p;

	while (y > 0)
	{
		// If y is odd, multiply x with result
		if (y & 1)
			res = (res * x) % p;

		// y must be even now
		y = y >> 1; // y = y/2
		x = (x * x) % p;
	}

	return res;
}



template <class T>
std::vector<T> encode_message(std::string message)
{
	// This function will convert the message to bits, split it according to STRIDE macro,
	// and then place the decimal values for each of the splits into a vector. 
	std::string binary_message;
	std::vector<T> encoded_message;
	int decimal;

	// Convert each character in a string to bits, and add to a new string
	for (size_t i = 0; i < message.size(); ++i)
	{
		binary_message += std::bitset<8>(message.c_str()[i]).to_string();
	}

	// Take bit splits of size STRIDE, convert to decimal value, and add to a vector
	for (size_t i = 0; i < binary_message.size(); i = i + STRIDE)
	{
		decimal = std::bitset<STRIDE>(binary_message.substr(i, STRIDE)).to_ulong();
		encoded_message.push_back(decimal);
	}

	return encoded_message;
}

template <class T>
std::string decode_message(std::vector<T> decrypted_message) {
	// Essentially the reverse of encode message, takes a vector of decimal values,
	// converts them to bits and creates a new bit string, and takes bytes from the string
	// to convert to ASCII characters
	std::string message, binary_message;
	char character;

	// Convert decimal values back to bits and add to binary string
	for (T dec : decrypted_message) {
		binary_message += std::bitset<STRIDE>(dec).to_string();
	}
	// Take bytes from the binary string and convert them to ASCII character equivalent
	for (size_t i = 0; i < binary_message.size(); i = i + 8) {
		character = (char)std::bitset<8>(binary_message.substr(i, 8)).to_ulong();
		message += character;
	}

	return message;
}

template <typename type>
vector<type> encrypt_message(vector<type> encoded, type e, type n)
{
	vector<type> cipher;
	type c;

	for (const type m : encoded)
	{
		c = mod_power<type>(m, e, n);
		cipher.push_back(c);
	}

	return cipher;
}

template <typename type>
vector<type> decrypt_message(const vector<type>& cipher, type d, type n)
{
	vector<type> decrypted;
	type m;

	for (const type c : cipher)
	{
		m = mod_power<type>(c, d, n);
		decrypted.push_back(m);
	}

	return decrypted;
}

#endif // FUNCTIONS_H

