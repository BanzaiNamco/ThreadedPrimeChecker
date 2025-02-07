#pragma once
#include <vector>
#include <thread>
#include <atomic>

namespace linearSearch {
    void immediatePrint(int numOfThreads, int maxNum);
    void delayPrint(int numOfThreads, int maxNum);
    void threadDispatch(std::atomic<int> &currentNumber, std::atomic<int> &currentDivisor, std::atomic<bool> &isPrime, std::atomic<int> &threadId, int numOfThreads, std::vector<std::thread> &threads);
    void updateToNextNumber(std::atomic<int> &currentNumber, std::atomic<int> &currentDivisor, std::atomic<bool> &isPrime);
};
