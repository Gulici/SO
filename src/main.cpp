#include "philosophers.h"
#include <iostream>

int main() {

    std::cout << "Menu: 1>runAsymetric 2>runSymetric\n";
    char wybor = '0';
    std::cin >> wybor;

    switch (wybor)
    {
    case '1':
        runAsymmetric();
        break;
    case '2':
        runSymmetric();
        break;
    case '3':
        runWaiter();
        break;
    default:
        break;
    }    
    return 0;
}