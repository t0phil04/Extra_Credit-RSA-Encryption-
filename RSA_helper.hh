/*
#ifndef RSA_HELPER_HH
#define RSA_HELPER_HH

#include <vector>
#include <string>
#include <bitset>
#include <cstddef>

// The size of the units we will split the bits of the message into. NEEDS TO BE MULTIPLE OF 2 (otherwise we have to pad)
#define STRIDE 2 // For a 32 bit string, will split it up into 16, 2-bit units. 

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



#endif // !"RSA_HELPER_HH"

*/
