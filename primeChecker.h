#pragma once
#include <vector>
#include <utility> 
#include <ctime> 
#include <string>
#include <thread>
#include <atomic>

namespace PrimeChecker {
    bool isPrime(int n);
    void immediatePrimePrint(int start, int end, int threadId);
    void storePrimes(int start, int end, int threadNo, std::vector<std::tuple<std::string, int, int>> &primes);
    std::string getCurrentTime();
    void divisibilityChecker(int n, int divisor, std::atomic<bool> &isPrime, std::atomic<int> &threadId, int i);
}
