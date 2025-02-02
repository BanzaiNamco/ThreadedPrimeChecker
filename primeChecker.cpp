#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <mutex>
#include <iomanip>

#include "primeChecker.h"

using namespace std;

mutex printMutex;

bool PrimeChecker::isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    // check only from 2 to sqrt(n)
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void PrimeChecker::immediatePrimePrint(int start, int end, int threadId) {
    for (int i = start; i <= end; i++) {
        if (PrimeChecker::isPrime(i)) {
            // get current time
            time_t currentTime = getCurrentTime();

            lock_guard<mutex> guard(printMutex);
            cout << "Thread " << threadId << ": " << i << " at " 
                 << put_time(localtime(&currentTime), "%Y-%m-%d %H:%M:%S") << endl;        
        }
    }
}

void PrimeChecker::storePrimes(int start, int end, vector<pair<time_t, int>> &primes) {
    for (int i = start; i <= end; i++) {
        if (PrimeChecker::isPrime(i)) {
            time_t currentTime = getCurrentTime();

            lock_guard<mutex> guard(printMutex);
            primes.push_back(make_pair(currentTime, i));
        }
    }
}

time_t PrimeChecker::getCurrentTime() {
    auto now = chrono::system_clock::now();
    return chrono::system_clock::to_time_t(now);
}