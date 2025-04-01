#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include "philosophers.h"

std::mutex waiter; // Kelner jako globalny mutex

void philosopherWaiter(int id) {
    for (int i = 0; i < 5; ++i) { // Każdy filozof je 5 razy
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Filozof " << id << " mysli " << i + 1 << " raz\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Myślenie
        
        int left_fork = id;
        int right_fork = (id + 1) % NUM_PHILOSOPHERS;
        
        // Prośba o dostęp do widelców przez kelnera
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Filozof " << id << " prosi o widelce: " << left_fork << " " << right_fork << "\n" ;
        }

        waiter.lock();
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Filozof " << id << " jest obslugiwany przez kelnera\n" ;
        }
        forks[left_fork].lock();
        forks[right_fork].lock();
        waiter.unlock();
        
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Filozof " << id << " je " << i + 1 << " raz\n";
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Jedzenie
        
        // Odkładanie widelców
        forks[left_fork].unlock();
        forks[right_fork].unlock();
        
    }
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Filozof " << id << " skonczyl uczte.\n";
    }
}

void runWaiter() {
    std::vector<std::thread> philosophers;
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers.emplace_back(philosopherWaiter, i);
    }
    for (auto &p : philosophers) {
        p.join();
    }
}
