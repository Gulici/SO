#include "philosophers.h"

std::mutex forks[NUM_PHILOSOPHERS];
std::mutex cout_mutex;