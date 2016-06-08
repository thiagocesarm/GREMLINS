/*!
 *  @mainpage Project GREMLINS
 *  @authors Thiago César Morais Diniz de Lucena
 *  @authors Yuri Reinaldo da Silva
 *  @date June, 2016
 *  @version 1.0
 *
 *	@file gremlins.cpp
 *
 *  File with the main function, used mostly to test SLPool implementation.
 */
 
#include "header.h"
#include "test_functions.h"

/*!
 *  @brief Main function with the memory pool test options.
 * 
 *  Main function in which the client can see the comparison between the memory pool
 *  and the system management, and view an example of the memory pool behavior via
 *  memory map shown on standard output.
 */
int main()
{
    
    std::cout << " __________________________________________________________" << std::endl;
    std::cout << "| Memory Manager v1.0                                      |" << std::endl;
    std::cout << "|     by Thiago César & Yuri Reinaldo                      |" << std::endl;
    std::cout << "|__________________________________________________________|\n\n" << std::endl;
    
    while (true)
    {
        
        std::cout << ">>> What do you wish to do?" << std::endl;
        std::cout << "1 - A comparison between the memory pool and the system management" << std::endl;   
        std::cout << "2 - Show a set example of memory pool behavior" << std::endl;   
        std::cout << "3 - Exit the program" << std::endl;   
    
        int option;
        std::cin >> option;

        if(option == 1)
        {
            // Allocating memory pool of size 2^29;
            SLPool _pool(pow(2,29));
            auto _rounds(0u);
        
            std::cout << "How many rounds do you wish to run the comparison test?" << std::endl;
            std::cin >> _rounds;
        
            StoragePoolTest( _pool, _rounds );
            std::cout << std::endl;
            SystemTest( _rounds );
        }
        else if (option == 2)
            ShowPoolExample();
        else if (option == 3) 
            break;
        else 
            std::cout << "Invalid option, please try again!" << std::endl;
            
    }
    
    std::cout << "Exiting program..." << std::endl;
    return EXIT_SUCCESS;
}