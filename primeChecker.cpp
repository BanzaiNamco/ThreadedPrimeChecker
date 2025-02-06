#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <mutex>
#include <ctime>
#include <string>
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
            
            string currentTime = getCurrentTime();
            lock_guard<mutex> guard(printMutex);
            cout << "Thread " << threadId << ": " << i << " at " << currentTime << endl;
        }
    }
}

void PrimeChecker::storePrimes(int start, int end, vector<pair<string, int>> &primes) {
    for (int i = start; i <= end; i++) {
        if (PrimeChecker::isPrime(i)) {

            string currentTime = getCurrentTime();
            lock_guard<mutex> guard(printMutex);
            primes.push_back(make_pair(currentTime, i));
        }
    }
}

string PrimeChecker::getCurrentTime() {
    auto now = chrono::system_clock::now();
    auto currentTime = chrono::system_clock::to_time_t(now);
    auto ms = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()) % 1000;
    stringstream ss;
    ss << put_time(localtime(&currentTime), "%Y-%m-%d %H:%M:%S") << '.' << setfill('0') << setw(3) << ms.count();
    return ss.str();
}