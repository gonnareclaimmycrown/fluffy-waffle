#pragma once
#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <filesystem>
#include <C:\Users\unluckyme\source\repos\labsUP\projects\helloworld\json.hpp>
#include <ctime>
#include <string>
#include <set>

void Task1(int argc, char* argv[]);
void Task2(int argc, char* argv[]);
void Task3(int argc, char* argv[]);
void Task4(int argc, char* argv[]);
void Task5(int argc, char* argv[]);
void Task6(int argc, char* argv[]);
void Task7(int argc, char* argv[]);
void Task8(int argc, char* argv[]);
void Task9(int argc, char* argv[]);
void Task10(int argc, char* argv[]);

void CheckArgumentsAmount(int arguments_amount);
void CheckInputPath(const std::filesystem::path& path_to_filesystem_object);
bool IsJsonCorrect(const nlohmann::json& json);


void ModifyJsonObject(nlohmann::json& json_object);


tm GetRequiredDateTime();
nlohmann::json TmToJson(tm date_time);


void CheckInputPath1(const std::filesystem::path& path_to_filesystem_object);
std::size_t Size(const std::filesystem::path& path_to_filesystem_object);


nlohmann::json GetRegularFileInfo(const std::filesystem::path& path_to_file);
nlohmann::json GetDirectoryInfo(const std::filesystem::path& path_to_directory);
nlohmann::json GetFsObjectInfo(const std::filesystem::path& path_to_filesystem_object);

namespace filesystem_object {
    std::size_t Size(const std::filesystem::path& path_to_filesystem_object);

    struct Info {
        std::string name;
        std::string type;
        std::size_t size;
    };

    std::ostream& operator<<(std::ostream& os, const Info& info);
    Info GetInfo(const std::filesystem::path& path_to_filesystem_object);
}

namespace directory_content {
    struct Info {
        std::filesystem::path path_to_directory;
        std::size_t size;
        uint32_t files_amount;
        uint32_t directories_amount;
    };

    std::ostream& operator<<(std::ostream& os, const Info& info);
    Info GetInfo(const std::filesystem::path& path_to_directory);
}


void CheckDirectoryPath(const std::filesystem::path& path_to_directory);
std::string ReadFileContent(const std::filesystem::path& path_to_file);
std::set<std::string> GetFilesContentFromDirectory(const std::filesystem::path& path_to_directory);


class FilesStorage {
public:
    FilesStorage(const std::filesystem::path& path_to_directory);
    void InitStorage();
    void CopyFile(const std::filesystem::path& path_to_file);

private:
    std::filesystem::path path_to_directory_;
    std::set<std::string> files_content_storage_;
};

std::size_t GetFileContentHash(const std::filesystem::path& path_to_file);
void RemoveDuplicatesFromDirectory(const std::filesystem::path& path_to_directory);

std::filesystem::path GetPathToMove(const std::filesystem::path& path_to_file);
void Move(const std::filesystem::path& path_to_file);

class FileName {
public:
    FileName(std::filesystem::path path_to_file);
    void Parse();
    bool IsRemoveRequired() const;

public:
    std::filesystem::path path_to_current_file;
    uint16_t year;
    uint16_t month;
    uint16_t day;
    std::string only_name;
};

std::filesystem::path GetPathToMove1(const std::filesystem::path& path_to_file);
void Move1(const std::filesystem::path& path_to_file);

#endif 