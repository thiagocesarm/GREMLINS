// #include "header.h"

#include <iostream>
#include "mempool_common.h"
// #include "storagepool.h"
#include "slpool.h"


int main ()
{
    SLPool mem(110);
    
    // auto my_mem = mem.Allocate(100);
    
    /*
    std::cout << "1\n";
    long long int * x = new (mem) long long int;
    long long int gu = 1974;
    x = &gu;
    std::cout << "x é " << *x << std::endl;
    
    std::cout << "e 2?\n";
    std::string * y = new (mem) std::string;
    std::string guava = "Goiaba";
    y = &guava;
    std::cout << "y é " << *y << std::endl;
    
    std::cout << "e 3?\n";
    double * z = new (mem) double;
    double pi = 3.1417;
    z = &pi;
    std::cout << "z é " << *z << std::endl;
    
    std::cout << "e 4?\n";
    long long int * w = new (mem) long long int;
    std::cout << "e 5?\n";
    long long int * k = new (mem) long long int;
    */

    return EXIT_SUCCESS;
}

