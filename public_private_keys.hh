#ifndef PUBLIC_PRIVATE_KEYS_HH
#define PUBLIC_PRIVATE_KEYS_HH
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <random>
#include <bitset>
#include "RSA_helper.hh"
#include "public_private_keys.hh"

bool trial_division(int val)
{
    int N = val;
    int numFactors = 0;
    int currentDivisor = 2;

    while (N > 1)
    {
        if (N % currentDivisor == 0)
        {
            numFactors += 1;
            if (numFactors >= 2)
            {
                return false;
            }

            N /= currentDivisor;
        }

        else
        {
            currentDivisor += 1;
        }
    }

    return true;
}

template <typename type>
type gcd(type m, type n)
{
    type m_, n_, r, temp;

    if (m > n)
    {
        m_ = m;
        n_ = n;
    }
    else
    {
        n_ = m;
        m_ = n;
    }

    while (n_ > 0)
    {
        r = m_ % n_;
        if (r == 0)
        {
            return n_;
        }
        m_ = n_;
        n_ = r;
    }

    return 1;
}

template <typename type>
type compute_public(type phi, int start)
{
    type e = start;

    while (gcd<type>(e, phi) > 1)
    {
        e += 1;
    }

    return e;
}

template <typename type>
type compute_private(type phi, type e)
{
    unsigned long prod;
    for (type d = 1; d < phi; d++)
    {
        prod = e * d;

        if ((prod % phi) == (1 % phi))
        {
            return d;
        }
    }

    return 0;
}

#endif // !PUBLIC_PRIVATE_KEYS_HH
