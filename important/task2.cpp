#include <iostream>
#include <fstream>
#include <C:\Users\unluckyme\source\repos\labsUP\projects\helloworld\json.hpp>
#include "functions.h"
#include <filesystem>

void Task2(int argc, char* argv[]) {
    try {
        CheckArgumentsAmount(2);

        std::filesystem::path input_path = R"(C:\Users\unluckyme\source\repos\kazan\lab2var1.json)";
        CheckInputPath(input_path);

        if (std::filesystem::exists(input_path)) {
            std::ifstream input_file(input_path);
            if (input_file.is_open()) {
                nlohmann::json data;
                input_file >> data;

                ModifyJsonObject(data);

                std::filesystem::path output_dir = input_path.parent_path() / "output";
                if (!std::filesystem::exists(output_dir)) {
                    std::filesystem::create_directory(output_dir);
                }

                for (auto& [key, value] : data.items()) {
                    std::filesystem::path output_path = output_dir / (key + ".json");
                    std::ofstream output_file(output_path);
                    if (output_file.is_open()) {
                        output_file << value.dump(4);
                    }
                    else {
                        std::cerr << "Не удалось открыть файл: " << output_path << std::endl;
                    }
                }
            }
            else {
                std::cerr << "Не удалось открыть файл: " << input_path << std::endl;
            }
        }
        else {
            std::cerr << "Файл не существует: " << input_path << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(1);
    }
}