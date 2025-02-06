#pragma once
#include <vector>
#include <utility> 
#include <ctime> 
#include <string>

namespace PrimeChecker {
    bool isPrime(int n);
    void immediatePrimePrint(int start, int end, int threadId);
    void storePrimes(int start, int end, std::vector<std::pair<std::string, int>> &primes);
    std::string getCurrentTime();
}
