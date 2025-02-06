#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <iomanip>
#include <mutex>
#include "primeChecker.h"
#include "searchRange.h"

using namespace std;

void SearchRange::runImmediatePrint(unsigned int numOfThreads, unsigned int maxNum) {
    // divide the search range into numOfThreads
    // each thread will check a portion of the search range
    // print the prime numbers immediately
    vector<thread> threads;
    unsigned int range = maxNum / numOfThreads;
    unsigned int start = 2;
    for (unsigned int i = 0; i < numOfThreads; i++) {
        unsigned int end = start + range - 1;
        if (i == numOfThreads - 1) {
            end = maxNum;
        }
        threads.emplace_back(PrimeChecker::immediatePrimePrint, start, end, i);
        start = end + 1;
    }

    for (auto &t : threads) {
        t.join();
    }
}

void SearchRange::runPrintAtEnd(unsigned int numOfThreads, unsigned int maxNum) {
    vector<thread> threads;
    vector<tuple<string, unsigned int, unsigned int>> primes;
    unsigned int range = maxNum / numOfThreads;
    unsigned int start = 2;
    for (unsigned int i = 0; i < numOfThreads; i++) {
        unsigned int end = start + range - 1;
        if (i == numOfThreads - 1) {
            end = maxNum;
        }
        threads.emplace_back(PrimeChecker::storePrimes, start, end, i, ref(primes));
        start = end + 1;
    }

    for (auto &t : threads) {
        t.join();
    }

    // print the prime numbers at the end
    for (auto &p : primes) {
        cout << "Main Thread (found at thread #" << get<2>(p) << "): " << get<1>(p) << " at " << get<0>(p) << endl;
    }
    cout << endl;
}
