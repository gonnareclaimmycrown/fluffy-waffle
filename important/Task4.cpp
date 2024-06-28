#include <iostream>
#include <fstream>
#include <C:\Users\unluckyme\source\repos\labsUP\projects\helloworld\json.hpp>
#include "functions.h"
#include <filesystem>
void Task4(int argc, char* argv[]) {
    try {
        CheckArgumentsAmount(2);

        const std::filesystem::path input_path = R"(C:\Users\unluckyme\source\repos\kazan\lab4var1)";
        CheckInputPath1(input_path);

        nlohmann::json fs_info = GetFsObjectInfo(input_path);

        std::cout << fs_info.dump(4) << std::endl;

        std::filesystem::path output_path = input_path.parent_path() / "fs_object_info.json";

        if (!std::filesystem::exists(output_path.parent_path())) {
            std::filesystem::create_directories(output_path.parent_path());
        }

        std::ofstream output_file(output_path);
        if (!output_file) {
            throw std::runtime_error("Failed to create output file.");
        }

        output_file << fs_info.dump(4);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}