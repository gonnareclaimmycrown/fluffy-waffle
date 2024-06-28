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

void Task10(int argc, char* argv[]) {
    try {
        CheckArgumentsAmount(2);

        std::filesystem::path input_path = R"(C:\Users\unluckyme\source\repos\kazan\lab10_original)";
        CheckDirectoryPath(input_path);

        for (const auto& entry : std::filesystem::directory_iterator(input_path)) {
            FileName file(entry.path());

            if (file.IsRemoveRequired()) {
                std::cout << "Removing file: " << entry.path() << std::endl;
                std::filesystem::remove(entry.path());
            }
            else {
                Move1(entry.path());
            }
        }
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(1);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(1);
    }
}