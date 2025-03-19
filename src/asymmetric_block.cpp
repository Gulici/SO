#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <random>
#include "philosophers.h"


// Funkcja reprezentująca zachowanie filozofa
void philosopherAsymmetric(int id) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(100, 500); // Losowy czas oczekiwania

    for (int i = 0; i < 5; ++i) { // Każdy filozof je 5 razy
        {   
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Filozof " << id << " myśli...\n";
        }
        // std::this_thread::sleep_for(std::chrono::milliseconds(dist(gen))); // Filozof myśli przez losowy czas
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Filozof myśli przez ustalony czas
        
        int left_fork = id; // Lewy widelec
        int right_fork = (id + 1) % NUM_PHILOSOPHERS; // Prawy widelec
        
        // Asymetryczne blokowanie w celu uniknięcia zakleszczenia
        // Filozof o parzystym ID najpierw bierze lewy widelec, a o nieparzystym prawy.
        if (id % 2 == 0) {
            forks[left_fork].lock();
            forks[right_fork].lock();
        } else {
            forks[right_fork].lock();
            forks[left_fork].lock();
        }
        
        
        {   
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Filozof " << id << " je...\n";
        }

        // std::this_thread::sleep_for(std::chrono::milliseconds(dist(gen))); // Filozof je przez losowy czas
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Filozof je przez ustalony czas
        
        // Odkładanie widelców po zakończeniu jedzenia
        forks[left_fork].unlock();
        forks[right_fork].unlock();
    }

    {   
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Filozof " << id << " skończył ucztę.\n";
    }
    
}


void runAsymmetric() {
    std::vector<std::thread> philosophers;
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers.emplace_back(philosopherAsymmetric, i);
    }
    for (auto &p : philosophers) {
        p.join();
    }
}
