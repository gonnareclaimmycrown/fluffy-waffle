#include <iostream>
#include <fstream>
#include <C:\Users\unluckyme\source\repos\labsUP\projects\helloworld\json.hpp>
#include "functions.h"
#include <filesystem>
void Task1(int argc, char* argv[]){
    try {
        CheckArgumentsAmount(2);

        const std::filesystem::path input_path = R"(C:\Users\unluckyme\source\repos\kazan\lab1var1.json)";
        CheckInputPath(input_path);

        nlohmann::json json_data;
        std::ifstream input_file(input_path);
        input_file >> json_data;

        if (IsJsonCorrect(json_data)) {
            std::cout << "Structure of JSON-file by path " << input_path << " is correct." << std::endl;
        }
        else {
            std::cout << "Structure of JSON-file by path " << input_path << " is incorrect." << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit (1);
    }
}