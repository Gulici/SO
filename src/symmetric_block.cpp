#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <random>
#include "philosophers.h"

// Funkcja reprezentująca zachowanie filozofa
void philosopherSymmetric(int id) {
    for (int i = 0; i < 5; ++i) { // Każdy filozof je 5 razy
        {   
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Filozof " << id << " mysli " << i + 1 << " raz\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Filozof myśli przez ustalony czas
        
        int left_fork = id; // Lewy widelec
        int right_fork = (id + 1) % NUM_PHILOSOPHERS; // Prawy widelec
        
        // Symetryczne blokowanie, może doprowadzić do deadlock
        forks[left_fork].lock();
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Filozof " << id << " wzial lewy widelec o id: " << left_fork << "\n";
        }
        forks[right_fork].lock();
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Filozof " << id << " wzial prawy widelec o id: " << right_fork << "\n";
        }
        
        
        {   
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Filozof " << id << " je " << i + 1 << " raz\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Filozof je przez ustalony czas
        
        // Odkładanie widelców po zakończeniu jedzenia
        forks[left_fork].unlock();
        forks[right_fork].unlock();
    }

    {   
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Filozof " << id << " skonczyl uczte.\n";
    }
    
}

void runSymmetric() {
    std::vector<std::thread> philosophers;
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers.emplace_back(philosopherSymmetric, i);
    }
    for (auto &p : philosophers) {
        p.join();
    }
}
