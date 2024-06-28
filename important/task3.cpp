#include <iostream>
#include <fstream>
#include <C:\Users\unluckyme\source\repos\labsUP\projects\helloworld\json.hpp>
#include "functions.h"
#include <filesystem>

void Task3(int argc, char* argv[]){
    try {
        CheckArgumentsAmount(2);

        const std::filesystem::path input_path = R"(C:\Users\unluckyme\source\repos\kazan\lab3var1.json)";
        CheckInputPath(input_path);

        tm required_time = GetRequiredDateTime();
        nlohmann::json json_time = TmToJson(required_time);

        std::cout << json_time.dump(4) << std::endl;

        std::filesystem::path output_path = input_path.parent_path() / input_path.filename();
        if (!std::filesystem::exists(output_path.parent_path())) {
            std::filesystem::create_directories(output_path.parent_path());
        }

        std::ofstream output_file(output_path);
        if (!output_file) {
            throw std::runtime_error("Failed to create output file.");
        }

        output_file << json_time.dump(4);

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}