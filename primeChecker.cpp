#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <mutex>
#include <ctime>
#include <atomic>
#include <thread>
#include <string>
#include <iomanip>
#include <cmath>

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
            
            string currentTime = getCurrentTime();
            lock_guard<mutex> guard(printMutex);
            cout << "Thread " << threadId << ": " << i << " at " << currentTime << endl;
        }
    }
}

void PrimeChecker::storePrimes(int start, int end, int threadNo, vector<tuple<string, int, int>> &primes) {
    for (int i = start; i <= end; i++) {
        if (PrimeChecker::isPrime(i)) {

            string currentTime = getCurrentTime();
            lock_guard<mutex> guard(printMutex);
            primes.push_back(make_tuple(currentTime, i, threadNo));
        }
    }
}

string PrimeChecker::getCurrentTime() {
    auto now = chrono::system_clock::now();
    auto currentTime = chrono::system_clock::to_time_t(now);
    auto ms = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()) % 1000;
    auto ns = chrono::duration_cast<chrono::nanoseconds>(now.time_since_epoch()) % 1000000000;
    stringstream ss;
    ss << put_time(localtime(&currentTime), "%Y-%m-%d %H:%M:%S") << '.' << setfill('0') << setw(3) << ms.count() << '.' << setfill('0') << setw(9) << ns.count();
    return ss.str();
}

void PrimeChecker::divisibilityChecker(int n, int divisor, atomic <bool> &isPrime, atomic <int> &threadId, int i) {
    if (n % divisor == 0 && n != divisor) {
        isPrime.store(false);
        threadId.store(i);
    }
}