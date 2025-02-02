#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <iomanip>
#include <mutex>
#include "primeChecker.h"
#include "searchRange.h"

using namespace std;

void SearchRange::runImmediatePrint(int numOfThreads, int maxNum) {
    // divide the search range into numOfThreads
    // each thread will check a portion of the search range
    // print the prime numbers immediately
    vector<thread> threads;
    int range = maxNum / numOfThreads;
    int start = 2;
    for (int i = 0; i < numOfThreads; i++) {
        int end = start + range - 1;
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

void SearchRange::runPrintAtEnd(int numOfThreads, int maxNum) {
    vector<thread> threads;
    vector<pair<time_t, int>> primes;
    int range = maxNum / numOfThreads;
    int start = 2;
    for (int i = 0; i < numOfThreads; i++) {
        int end = start + range - 1;
        if (i == numOfThreads - 1) {
            end = maxNum;
        }
        threads.emplace_back(PrimeChecker::storePrimes, start, end, ref(primes));
        start = end + 1;
    }

    for (auto &t : threads) {
        t.join();
    }

    // print the prime numbers at the end
    for (auto &p : primes) {
        cout << "Main Thread: " << p.second << " at " << put_time(localtime(&p.first), "%Y-%m-%d %H:%M:%S") << endl;
    }
    cout << endl;
}
