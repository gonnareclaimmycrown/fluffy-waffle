#include <iostream>
#include <C:\Users\unluckyme\source\repos\labsUP\projects\helloworld\json.hpp>
#include "functions.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <fstream>
#include <string>
#include <set>

void Task8(int argc, char* argv[]) {
    try {
        CheckArgumentsAmount(2);
        std::filesystem::path input_path = R"(C:\Users\unluckyme\source\repos\kazan\lab8_original)";
        CheckDirectoryPath(input_path);
        RemoveDuplicatesFromDirectory(input_path);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(1);
    }
}