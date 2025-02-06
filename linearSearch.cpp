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

void linearSearch::runImmediatePrint(int numOfThreads, int maxNum) {
    atomic <int> currentNumber(2);
    vector<thread> threads;

    for (int i = 0; i < numOfThreads; i++) {
        threads.emplace_back([&currentNumber, maxNum, i] {
            while (currentNumber <= maxNum) {
                int number = currentNumber.fetch_add(1); // this returns the number before 1 is added
                PrimeChecker::immediatePrimePrint(number, number, i);
            }
        });
    }

    for (auto &t : threads) {
        t.join();
    }
}

void linearSearch::runPrintAtEnd(int numOfThreads, int maxNum) {
    atomic <int> currentNumber(2);
    vector<thread> threads;
    vector<pair<string, int>> primes;

    for (int i = 0; i < numOfThreads; i++) {
        threads.emplace_back([&currentNumber, maxNum, &primes] {
            while (currentNumber <= maxNum) {
                int number = currentNumber.fetch_add(1);
                PrimeChecker::storePrimes(number, number, ref(primes));
            }
        });
    }

    for (auto &t : threads) {
        t.join();
    }

    for (auto &p : primes) {
        cout << "Main Thread: " << p.second << " at " << p.first << endl;
    }
    cout << endl;

}
