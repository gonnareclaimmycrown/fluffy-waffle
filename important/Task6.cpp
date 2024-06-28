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

void Task6(int argc, char* argv[]) {
    try {
        CheckArgumentsAmount(2);
        std::filesystem::path sourcePath = R"(C:\Users\unluckyme\source\repos\kazan\lab6_original)";
        std::filesystem::path destPath = R"(C:\Users\unluckyme\source\repos\kazan\lab6_paste_here)";

        CheckDirectoryPath(sourcePath);
        CheckDirectoryPath(destPath);

        std::set<std::string> filesContent = GetFilesContentFromDirectory(sourcePath);

        std::cout << "Found " << filesContent.size() << " unique files in the source directory." << std::endl;

        for (const auto& file : std::filesystem::directory_iterator(sourcePath)) {
            if (std::filesystem::is_regular_file(file)) {
                std::string fileContent = ReadFileContent(file.path());
                if (filesContent.find(file.path().string()) == filesContent.end()) {
                    std::filesystem::copy_file(file.path(), destPath / file.path().filename());
                    std::cout << "File by path " << file.path().string() << " has been copied to directory by path " << destPath.string() << "!" << std::endl;
                    filesContent.insert(file.path().string());
                }
                else {
                    std::cout << "Skipping file by path " << file.path().string() << " because its content is already in the set." << std::endl;
                }
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(1);
    }
}