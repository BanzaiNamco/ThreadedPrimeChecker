#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <iomanip>
#include <mutex>
#include <atomic>
#include <string>
#include <stdlib.h>
#include "primeChecker.h"
#include "linearSearch.h"

using namespace std;

void linearSearch::runImmediatePrint(unsigned int numOfThreads, unsigned int maxNum) {
    atomic <unsigned int> currentNumber(2);
    vector<thread> threads;

    for (unsigned int i = 0; i < numOfThreads; i++) {
        threads.emplace_back([&currentNumber, maxNum, i] {
            while (currentNumber <= maxNum) {
                unsigned int number = currentNumber.fetch_add(1); // this returns the number before 1 is added
                PrimeChecker::immediatePrimePrint(number, number, i);
            }
        });
    }

    for (auto &t : threads) {
        t.join();
    }
}

void linearSearch::runPrintAtEnd(unsigned int numOfThreads, unsigned int maxNum) {
    atomic <unsigned int> currentNumber(2);
    vector<thread> threads;
    vector<tuple<string, unsigned int, unsigned int>> primes;

    for (unsigned int i = 0; i < numOfThreads; i++) {
        threads.emplace_back([&currentNumber, maxNum, i, &primes] {
            while (currentNumber <= maxNum) {
                unsigned int number = currentNumber.fetch_add(1);
                PrimeChecker::storePrimes(number, number, i, ref(primes));
            }
        });
    }

    for (auto &t : threads) {
        t.join();
    }

    for (auto &p : primes) {
        cout << "Main Thread (found at thread #" << get<2>(p) << "): " << get<1>(p) << " at " << get<0>(p) << endl;
    }
    cout << endl;

}
