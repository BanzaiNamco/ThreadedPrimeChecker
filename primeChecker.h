#pragma once
#include <vector>
#include <utility> 
#include <ctime> 
#include <string>

namespace PrimeChecker {
    bool isPrime(unsigned int n);
    void immediatePrimePrint(unsigned int start, unsigned int end, unsigned int threadId);
    void storePrimes(unsigned int start, unsigned int end, unsigned int threadNo, std::vector<std::tuple<std::string, unsigned int, unsigned int>> &primes);
    std::string getCurrentTime();
}
