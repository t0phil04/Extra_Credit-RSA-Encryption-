#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <random>
#include <bitset>
#include "RSA_helper.hh"
#include "public_private_keys.hh"



int main()
{
    std::cout << "What message would you like to decrypt? ";
    std::string message;
    std::getline(cin, message);

    std::vector<unsigned long long> encoded_message = encode_message<unsigned long long>(message);

    print_vector(encoded_message);

    unsigned int p = 7;
    unsigned int q = 13;
    unsigned long long n = p * q;
    unsigned long long phi = (p - 1) * (q - 1);

    cout << "n: " << n << endl;
    cout << "phi: " << phi << endl;


    unsigned long long e = compute_public<unsigned long long>(phi, 3);
    cout << "Public: " << e << endl;
    unsigned long long d = compute_private<unsigned long long>(phi, e);
    cout << "Private: " << d << endl;

    vector<unsigned long long> cipher = encrypt_message<unsigned long long>(encoded_message, e, n);

    vector<unsigned long long> decrypted = decrypt_message<unsigned long long>(cipher, d, n);

    print_vector(decrypted);

    string ret = decode_message(decrypted);

    cout << ret;

    return 0;
}