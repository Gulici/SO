#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <mutex>

constexpr int NUM_PHILOSOPHERS = 5;
extern std::mutex forks[NUM_PHILOSOPHERS]; 
extern std::mutex cout_mutex;

void runSymmetric();
void runAsymmetric();
void runWaiter();

#endif