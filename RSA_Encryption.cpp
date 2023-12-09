#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <random>
#include <bitset>


#include "Functions.h"

//using std::cout; using std::cin; using std::vector; using std::endl; using std::string;

int main() {
	srand(time(0));

	std::vector<int> primeFactorsP; // will hold the prime factors to p
	std::vector<int> primeFactorsQ; // will hold the prime factors to q
	
	int p = 7;
	int q = 13;
	cout << "1. Trials Division" << std::endl;

	std::cout << "Positive integer first being tested for primality (p): " << p << std::endl;

	// Starts method for trials division using p
	primeFactorsP = trialsDivision(p);

	// Checks if p was a prime number
	bool isPrime_P = checkPrime(primeFactorsP);

	if (isPrime_P == true)
	{
		std::cout << "Final number p to be tested for Primality: " << p << std::endl;
		std::cout << "Prime Factors to p: " << primeFactorsP.at(0) << " " << std::endl;
	}
	while (isPrime_P == false)
	{
		p++;
		primeFactorsP = trialsDivision(p); // ran again if p was not prime
		isPrime_P = checkPrime(primeFactorsP);
		if (isPrime_P == true)
		{
			std::cout << "Final number p to be tested for Primality: " << p << std::endl;
			std::cout << "Prime Factors to p: " << primeFactorsP.at(0) << " " << std::endl;

		}
	}

	std::cout << "Positive integer first being tested for primality (q): " << q << std::endl;

	// Starts method for trials division using q
	primeFactorsQ = trialsDivision(q);

	bool isPrime_Q = checkPrime(primeFactorsQ);
	int p_and_q_GCD = EU_Algorithm(p, q);

	while (isPrime_Q == false && p_and_q_GCD != 1)
	{
		q++;
		primeFactorsQ = trialsDivision(q);
		isPrime_Q = checkPrime(primeFactorsQ);
		p_and_q_GCD = EU_Algorithm(p, q);

		if (isPrime_Q == true && p_and_q_GCD == 1)
		{
			std::cout << "Final number q to be tested for Primality: " << q << std::endl;
			std::cout << "Prime factors to q: " << primeFactorsQ.at(0) << " " << std::endl;
		}
	}
	std::cout << "GCD(p,q): " << p_and_q_GCD << std::endl;

	std::cout << "\n2. Euclidean Algorithm" << std::endl;

	int n_KeyLength = p * q;
	std::cout << "Key Length (n = p*q): " << n_KeyLength << std::endl;

	int phi_n = (p - 1) * (q - 1);
	
	int e_publicKey = 5;
	if (e_publicKey == 2 || e_publicKey >= phi_n)
	{
		while ((e_publicKey != 2) && (e_publicKey >= phi_n))
		{
			e_publicKey = rand() % phi_n + 2;
		}
	}
	
	int GCD_final = EU_Algorithm(e_publicKey, phi_n);
	while (GCD_final != 1)
	{
		int e_publicKey = rand() % phi_n + 2;
		if (e_publicKey == 2 || e_publicKey >= phi_n)
		{
			while ((e_publicKey != 2) && (e_publicKey >= phi_n))
			{
				e_publicKey = rand() % phi_n + 2;
			}
		}
		GCD_final = EU_Algorithm(e_publicKey, phi_n);
	}

	std::cout << "Public Key: " << e_publicKey << std::endl;
	std::cout << "GCD(" << e_publicKey << ',' << phi_n << ')' << std::endl;

	
	std::cout << "GCD calculated is: " << GCD_final << std::endl;

	// Calculates the decryption key
	//int d_inverse = mult_Inverse(e_publicKey, n_KeyLength, GCD_final);
	int d_inverse = mult_Inverse(phi_n, e_publicKey);
	std::cout << "Decryption Key: " << d_inverse << std::endl;

	// Recieves the message for Encryption
	std::string plainText;
	std::cout << "\nEnter a Phrase to Encrypt: ";
	getline(cin, plainText);
	
	
// Start the Encryption procces
	std::vector<unsigned long long> encoded_message = encode_message<unsigned long long>(plainText);
	std::vector<unsigned long long> cipher = encrypt_message<unsigned long long>(encoded_message, e_publicKey, n_KeyLength);

	std::cout << "\nEncoded_message: ";
	for (int i = 0; i < encoded_message.size(); i++) { std::cout << encoded_message.at(i) << " "; }

	std::cout << "\nCipher: ";
	for (int i = 0; i < cipher.size(); i++) { std::cout <<cipher.at(i) << " "; }
	

	
// Start the Decryption Procces
	std::vector<unsigned long long> decrypted = decrypt_message<unsigned long long>(cipher, d_inverse, n_KeyLength);
/*
	cout << "\nDecrypted Message: ";
	for (int i = 0; i < decrypted.size(); i++) { std::cout << decrypted.at(i) << " "; }
*/
	std::string ret_message = decode_message(decrypted);
	std::cout << "\nOriginal Message: " << ret_message;


	return 0;
}