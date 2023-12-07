#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <ctime>
#include <cmath>


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
	/*int d_decrypt = 1;
	int tmp1 = 2;
	int tmp2 = 2;
	
	

	// Check if a multiplicative inverse exists
	if (GCD != 1) {
		cout << "Error: no multiplicative inverse exists" << endl;
		return -1;
	}

	// Find the multiplicative inverse using a loop
	while (tmp1 != 1) {
		tmp1 = (e_publicKey * tmp2) % n;
		d_decrypt = tmp2;
		if (d_decrypt == 1) {
			break;
		}
		else {
			tmp2++;
		}
	}
	*/

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

// Exponentation algorithmn
// Comment Block below used for Learning Opportunity
/* 
The original code used the pow() function from the C++ standard library
	to calculate the exponentiation of asciiValues.at(i) to the power of e.
	However, pow() returns a floating-point value, which can lead to precision
	errors when dealing with large numbers.

In contrast, the modPow() function is a custom implementation of the
	exponentiation algorithm that works with integers. This function
	calculates the result of raising the base to the power of exp modulo mod.

The algorithm works by repeatedly squaring the base and reducing the
	result modulo mod. This allows the calculation to be performed efficiently
	and without the need for floating-point arithmetic.

By using modPow() instead of pow(), the precision errors are avoided,
	and the encryption is performed correctly. This results in the correct
	values being added to the cipher_ vector, as expected.
*/

unsigned long long modPow(unsigned long long base, unsigned long long exp, unsigned long long mod) {
	unsigned long long result = 1;
	while (exp > 0) {
		if (exp % 2 == 1) {
			result = (result * base) % mod;
		}
		base = (base * base) % mod;
		exp /= 2;
	}
	return result;
}

vector <unsigned long long> message_Encrypt(vector <int> asciiValues , int e, int n) {
	// Had to switch to this data type because the outputs were all negative
	vector <unsigned long long> cipher_;
	for (int i = 0; i < asciiValues.size(); i++) {
							// used to read: pow(asciiValues.at(i), e);
							//				 encryptedValue %= n;
							// This caused the cipher_ values to all be the same
		unsigned long long encryptedValue = modPow(asciiValues.at(i), e, n);
		cipher_.push_back(encryptedValue);
	}

	return cipher_;
}

vector<unsigned long long> message_Decrypt(vector<unsigned long long> cipher, int d, int n) {
	vector<unsigned long long> decrypted_ascii; // Holds the new vector of ascii values
	cout << "\nascii to message: ";

	for (int i = 0; i < cipher.size(); i++) {
		// Use your modPow function for decryption
		unsigned long long ascii = modPow(cipher.at(i), d, n);

		decrypted_ascii.push_back(ascii);
		cout << "ascii: " << ascii << " ";
	}

	string decrypted_message = "";
	for (int i = 0; i < decrypted_ascii.size(); i++) {
		decrypted_message += static_cast<char>(decrypted_ascii.at(i));
	}

	return decrypted_ascii;
}


/*
vector<unsigned long long> message_Decrypt(vector<unsigned long long> cipher, int d, int n) {
	vector<unsigned long long> decrypted_ascii; // Holds the new vector of ascii values
	cout << "\nascii to message: ";

	for (int i = 0; i < cipher.size(); i++) {

		// current index ascii value produced using modular exponentiation
		unsigned long long ascii = pow(cipher.at(i), d);
		ascii = ascii % n;

		decrypted_ascii.push_back(ascii);
		cout << "ascii: " << ascii << " ";
	}
	string decrypted_message = "";
	for (int i = 0; i < decrypted_ascii.size(); i++) {
		decrypted_message += static_cast<char>(decrypted_ascii.at(i));
	}

	return decrypted_ascii;

}
*/

/*
vector<unsigned long long> message_Decrypt(vector<unsigned long long> cipher, int d, int n) {
	vector<unsigned long long> decrypted_ascii; // Holds the new vector of ascii values
	cout << "\nascii to message: ";

	for (int i = 0; i < cipher.size(); i++) {

		// current index ascii value produced using modular exponentiation
		unsigned long long ascii = modPow(cipher.at(i), d, n);
		decrypted_ascii.push_back(ascii);
		cout << decrypted_ascii.at(i) << " ";

	}
	string decrypted_message = "";
	for (int i = 0; i < decrypted_ascii.size(); i++) {
		decrypted_message += static_cast<char>(decrypted_ascii.at(i));
	}

	return decrypted_ascii;

}
*/


#endif // FUNCTIONS_H

