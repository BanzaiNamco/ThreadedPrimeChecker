#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <iomanip>
#include <mutex>
#include <cmath>
#include <atomic>
#include <string>
#include <tuple>
#include <stdlib.h>
#include "primeChecker.h"
#include "linearSearch.h"

using namespace std;

void linearSearch::immediatePrint(int numOfThreads, int maxNum) {
    atomic<int> currentNumber = 2;
    vector<thread> threads;
    atomic<int> currentDivisor = 2;
    atomic<bool> isPrime = true;
    atomic<int> threadId = 0;

    while (currentNumber <= maxNum) {
        threadDispatch(currentNumber, currentDivisor, isPrime, threadId, numOfThreads, threads);
        if (currentDivisor * currentDivisor > currentNumber) {
            if (isPrime) {
                string currentTime = PrimeChecker::getCurrentTime();
                cout << "Thread " << threadId << ": " << currentNumber << " at " << currentTime << endl;
            }
            updateToNextNumber(currentNumber, currentDivisor, isPrime);
        }
    }
}

void linearSearch::delayPrint(int numOfThreads, int maxNum) {
    atomic<int> currentNumber = 2;
    vector<thread> threads;
    atomic<int> currentDivisor = 2;
    atomic<bool> isPrime = true;
    atomic<int> threadId = 0;
    vector<tuple<string, int, int>> primes;

    while (currentNumber <= maxNum) {
        threadDispatch(currentNumber, currentDivisor, isPrime, threadId, numOfThreads, threads);
        if (currentDivisor * currentDivisor > currentNumber) {
            if (isPrime) {
                string currentTime = PrimeChecker::getCurrentTime();
                int threadId2 = threadId.load();
                int currentNumber2 = currentNumber.load();
                primes.push_back(make_tuple(currentTime, currentNumber2, threadId2));
            }
            updateToNextNumber(currentNumber, currentDivisor, isPrime);
        }
    }
    for (auto &p : primes) {
        cout << "Main Thread (found at thread #" << get<2>(p) << "): " << get<1>(p) << " at " << get<0>(p) << endl;
    }
}

void linearSearch::threadDispatch(atomic <int> &currentNumber, atomic <int> &currentDivisor, atomic <bool> &isPrime, atomic <int> &threadId, int numOfThreads, vector<thread> &threads) {
    int num = currentNumber.load();
    int maxN = static_cast<int>(sqrt(num));

    for (int i = 0; i < numOfThreads && i < maxN; i++) {
        int divisor = currentDivisor.load();
        threads.emplace_back(PrimeChecker::divisibilityChecker, num, divisor, ref(isPrime), ref(threadId), i);
        currentDivisor.fetch_add(1);
    }
    for (auto &t : threads) {
        t.join();
    }
    threads.clear();
}

void linearSearch::updateToNextNumber(atomic<int> &currentNumber, atomic<int> &currentDivisor, atomic<bool> &isPrime) {
    currentNumber++;
    currentDivisor = 2;
    isPrime.store(true);
}