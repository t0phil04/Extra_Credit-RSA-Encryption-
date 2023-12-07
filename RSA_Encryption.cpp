#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <ctime>


#include "functions.h"

using std::cout; using std::cin; using std::vector; using std::endl; using std::string;

// Functions inside functions header file
/*
vector <int> trialsDivision(int n);
int EU_Algorithm(int e_publicKey_, int phi_n_);
bool checkPrime(vector <int> check);
int mult_Inverse( int e_publicKey, int n_KeyLength, int GCD);
vector <unsigned long long> message_Encrypt(vector <int> asciiValues, int e, int n);
*/

int mod_power(int x, int y, int p)
{
	//Source https://www.geeksforgeeks.org/modular-exponentiation-power-in-modular-arithmetic/#
	int res = 1;

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

vector<unsigned long long> fake_decrypt(const vector<unsigned long long>& cipher, int d, int n)
{
	vector<unsigned long long> decrypted;
	int m;

	for (const size_t c : cipher)
	{
		m = mod_power(c, d, n);
		decrypted.push_back(m);
	}

	return decrypted;
}

int main() {
	srand(time(0));

	vector<int> primeFactorsP; // will hold the prime factors to p
	vector<int> primeFactorsQ; // will hold the prime factors to q
	//int p = rand() % 50;
	int p = 7;
	cout << "1. Trials Division" << endl;

	cout << "Positive integer first being tested for primality (p): " << p << endl;

	// Starts method for trials division using p
	primeFactorsP = trialsDivision(p);

	// Checks if p was a prime number
	bool isPrime_P = checkPrime(primeFactorsP);

	if (isPrime_P == true)
	{
		cout << "Final number p to be tested for Primality: " << p << endl;
		cout << "Prime Factors to p: " << primeFactorsP.at(0) << " " << endl;
	}
	while (isPrime_P == false)
	{
		p++;
		primeFactorsP = trialsDivision(p); // ran again if p was not prime
		isPrime_P = checkPrime(primeFactorsP);
		if (isPrime_P == true)
		{
			cout << "Final number p to be tested for Primality: " << p << endl;
			cout << "Prime Factors to p: " << primeFactorsP.at(0) << " " << endl;

		}
	}


	//int q = rand() + 50;
	int q = 13;

	cout << "Positive integer first being tested for primality (q): " << q << endl;

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
			cout << "Final number q to be tested for Primality: " << q << endl;
			cout << "Prime factors to q: " << primeFactorsQ.at(0) << " " << endl;
		}
	}
	cout << "GCD(p,q): " << p_and_q_GCD << endl;

	cout << "\n2. Euclidean Algorithm" << endl;

	int n_KeyLength = p * q;
	cout << "Key Length (n = p*q): " << n_KeyLength << endl;

	int phi_n = (p - 1) * (q - 1);
	
	//int e_publicKey = rand() % phi_n + 2;
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

	cout << "Public Key: " << e_publicKey << endl;
	cout << "GCD(" << e_publicKey << ',' << phi_n << ')' << endl;

	
	cout << "GCD calculated is: " << GCD_final << endl;

	// Calculates the decryption key
	//int d_inverse = mult_Inverse(e_publicKey, n_KeyLength, GCD_final);
	int d_inverse = mult_Inverse(phi_n, e_publicKey);
	cout << "Decryption Key: " << d_inverse << endl;

	// Recieves the message for Encryption
	string plainText;
	cout << "\nEnter a Phrase to Encrypt: "; 
	getline(cin, plainText);
	
	// Starts the conversion to ascii
	vector<int> asciiValues;
	for (char c: plainText)
	{
		// how to cast a character to int for vectors
		// if using array: asciiValues[i] = (int) plainText[i];
		asciiValues.push_back(int(c));
	}
	cout << "\nEncoded Text: ";
	//  (range_declaration : range_expression)
	for (int ascii : asciiValues) { // new syntax for the loop using the vectors length
		cout << ascii << " ";
	}

	
	// Start the Encryption procces
	vector<unsigned long long> cipher = message_Encrypt(asciiValues, e_publicKey , n_KeyLength);
	cout << "\nCipher: ";
	for (int i = 0; i < cipher.size(); i++) { cout << cipher.at(i) << " "; }
	
	// Start the Decryption Procces
	// Decrypt the cipher

	//vector<unsigned long long> decrypted_ascii = message_Decrypt(cipher, d_inverse, n_KeyLength);

	// Convert decrypted ascii values back to characters
	// Print out the decrypted ASCII values
	/*
	string decrypted_message = " ";
	for (int i = 0; i < decrypted_ascii.size(); i++) {
		decrypted_message += static_cast<char>(decrypted_ascii[i] % 256);
	}
	*/
	vector<unsigned long long> decrypted_ascii = fake_decrypt(cipher, d_inverse, n_KeyLength);
	
	
	cout << "\ndecryption: ";
	for (size_t i = 0; i < decrypted_ascii.size(); i++)
	{
		cout << decrypted_ascii.at(i) << " ";
	}	 


	//cout << "\nDecrypted Message: " << decrypted_message;

	return 0;
}