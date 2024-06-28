#include <iostream>
#include <fstream>
#include <C:\Users\unluckyme\source\repos\labsUP\projects\helloworld\json.hpp>
#include "functions.h"
#include <filesystem>
#include <iomanip>

void Task5(int argc, char* argv[]) {
    try {
        CheckArgumentsAmount(2);

        const std::filesystem::path input_path = R"(C:\Users\unluckyme\source\repos\kazan\lab5var1)";
        CheckInputPath1(input_path);

        directory_content::Info dir_info = directory_content::GetInfo(input_path);

        std::cout << dir_info << std::endl;

        std::cout << "\n";

        for (const auto& entry : std::filesystem::directory_iterator(input_path)) {
            filesystem_object::Info obj_info = filesystem_object::GetInfo(entry.path());
            std::cout << obj_info << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}