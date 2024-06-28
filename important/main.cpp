#include <iostream>
#include <fstream>
#include <C:\Users\unluckyme\source\repos\labsUP\projects\helloworld\json.hpp>
#include "functions.h"

int main(int argc, char* argv[]) {
    int task_number;
    std::cout << "task_number"; 
    std::cin >> task_number;

    switch (task_number) {
        case 1:
            Task1(argc, argv);
            break;
        case 2:
            Task2(argc, argv);
            break;
        case 3:
            Task3(argc, argv);
            break;
        case 4:
            Task4(argc, argv);
            break;
        case 5:
            Task5(argc, argv);
            break;
        case 6:
            Task6(argc, argv);
            break;
        case 7:
            Task7(argc, argv);
            break;
        case 8:
            Task8(argc - 1, argv + 1);
            break;
        case 9:
            Task9(argc - 1, argv + 1);
            break;
        case 10:
            Task10(argc - 1, argv + 1);
            break;
        default:
            std::cerr << "Invalid task number: " << task_number << std::endl;   
            return 1;
    }
    return 0;
}