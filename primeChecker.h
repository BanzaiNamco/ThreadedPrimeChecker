#pragma once
#include <vector>
#include <utility> 
#include <ctime> 

namespace PrimeChecker {
    bool isPrime(int n);
    void immediatePrimePrint(int start, int end, int threadId);
    void storePrimes(int start, int end, std::vector<std::pair<time_t, int>> &primes);
    time_t getCurrentTime();
}
