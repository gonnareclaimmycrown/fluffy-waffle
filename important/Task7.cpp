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

void Task7(int argc, char* argv[]) {
    try {
        CheckArgumentsAmount(2);

        std::filesystem::path sourcePath = R"(C:\Users\unluckyme\source\repos\kazan\lab7_original)";
        CheckDirectoryPath(sourcePath);
        std::filesystem::path destinationPath = R"(C:\Users\unluckyme\source\repos\kazan\lab7_paste_here)";
        CheckDirectoryPath(destinationPath);

        FilesStorage storage(destinationPath);
        storage.InitStorage();

        for (const auto& entry : std::filesystem::directory_iterator(sourcePath)) {
            storage.CopyFile(entry.path());
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