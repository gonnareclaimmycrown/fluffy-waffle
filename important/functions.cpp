#include "functions.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <fstream>
#include <string>
#include <set>
#include <iostream>

void CheckArgumentsAmount(int arguments_amount) {
    if (arguments_amount != 2) {
        throw std::invalid_argument("Invalid command line arguments amount: current - " + std::to_string(arguments_amount) + ", required - 2!");
    }
}

void CheckInputPath(const std::filesystem::path& path_to_filesystem_object) {
    if (!std::filesystem::exists(path_to_filesystem_object)) {
        std::ostringstream oss;
        oss << "Filesystem object by path " << path_to_filesystem_object << " does not exist!";
        throw std::invalid_argument(oss.str());
    }

    if (!std::filesystem::is_regular_file(path_to_filesystem_object)) {
        std::ostringstream oss;
        oss << "Filesystem object by path " << path_to_filesystem_object << " is not a regular file!";
        throw std::invalid_argument(oss.str());
    }

    if (path_to_filesystem_object.extension() != ".json") {
        std::ostringstream oss;
        oss << "Filesystem object by path " << path_to_filesystem_object << " has an invalid extension!";
        throw std::invalid_argument(oss.str());
    }
}

bool IsJsonCorrect(const nlohmann::json& json) {
    if (!json.is_object()) {
        return false;
    }
    if (!json.contains("object") || !json["object"].is_object()) {
        return false;
    }
    if (!json["object"].contains("string") || !json["object"]["string"].is_string()) {
        return false;
    }
    if (!json["object"].contains("number") || !json["object"]["number"].is_number()) {
        return false;
    }
    if (!json["object"].contains("inner_array") || !json["object"]["inner_array"].is_array()) {
        return false;
    }
    if (!json.contains("array") || !json["array"].is_array()) {
        return false;
    }
    for (const auto& element : json["array"]) {
        if (!element.is_boolean() && !element.is_null() && !element.is_object()) {
            return false;
        }
    }
    return true;
}

void ModifyJsonObject(nlohmann::json& json_object) {
    for (auto it = json_object.begin(); it != json_object.end();) {
        if (it.value().is_null()) {
            it = json_object.erase(it);
        }
        else {
            ++it;
        }
    }
}

tm GetRequiredDateTime() {
    time_t now = time(nullptr);
    tm local_time{};

    if (localtime_s(&local_time, &now) != 0) {
        throw std::runtime_error("Failed to get local time.");
    }

    local_time.tm_year += 2001;
    local_time.tm_mon += 1;
    mktime(&local_time);

    return local_time;
}

nlohmann::json TmToJson(tm date_time) {
    nlohmann::json json_obj;
    json_obj["tm_sec"] = date_time.tm_sec;
    json_obj["tm_min"] = date_time.tm_min;
    json_obj["tm_hour"] = date_time.tm_hour;
    json_obj["tm_mday"] = date_time.tm_mday;
    json_obj["tm_mon"] = date_time.tm_mon;
    json_obj["tm_year"] = date_time.tm_year;
    json_obj["tm_wday"] = date_time.tm_wday;
    json_obj["tm_yday"] = date_time.tm_yday;

    return json_obj;
}

void CheckInputPath1(const std::filesystem::path& path_to_filesystem_object) {
    if (!std::filesystem::exists(path_to_filesystem_object)) {
        std::ostringstream oss;
        oss << "Filesystem object by path " << path_to_filesystem_object << " is not exists!";
        throw std::invalid_argument(oss.str());
    }

    if (!std::filesystem::is_regular_file(path_to_filesystem_object) && !std::filesystem::is_directory(path_to_filesystem_object)) {
        std::ostringstream oss;
        oss << "Filesystem object by path " << path_to_filesystem_object << " has invalid type!";
        throw std::invalid_argument(oss.str());
    }
}

std::size_t Size(const std::filesystem::path& path_to_filesystem_object) {
    if (std::filesystem::is_directory(path_to_filesystem_object)) {
        std::size_t size = 0;
        for (const auto& entry : std::filesystem::recursive_directory_iterator(path_to_filesystem_object)) {
            if (std::filesystem::is_regular_file(entry.path())) {
                size += std::filesystem::file_size(entry.path());
            }
        }
        return size;
    }
    else if (std::filesystem::is_regular_file(path_to_filesystem_object)) {
        return std::filesystem::file_size(path_to_filesystem_object);
    }
    else {
        throw std::invalid_argument("Invalid filesystem object type for size calculation.");
    }
}

nlohmann::json GetRegularFileInfo(const std::filesystem::path& path_to_file) {
    nlohmann::json json_obj;
    json_obj["type"] = "regular_file";
    json_obj["full_name"] = path_to_file.filename().string();
    json_obj["name_without_extension"] = path_to_file.stem().string();
    json_obj["extension"] = path_to_file.has_extension() ? path_to_file.extension().string() : nullptr;
    json_obj["size"] = Size(path_to_file);

    return json_obj;
}

nlohmann::json GetDirectoryInfo(const std::filesystem::path& path_to_directory) {
    nlohmann::json json_obj;
    json_obj["type"] = "directory";
    json_obj["name"] = path_to_directory.stem().string();
    json_obj["size"] = Size(path_to_directory);

    std::size_t files_amount = 0;
    std::size_t directories_amount = 0;

    for (const auto& entry : std::filesystem::directory_iterator(path_to_directory)) {
        if (std::filesystem::is_regular_file(entry.path())) {
            files_amount++;
        }
        else if (std::filesystem::is_directory(entry.path())) {
            directories_amount++;
        }
    }

    json_obj["files_amount"] = files_amount;
    json_obj["directories_amount"] = directories_amount;

    return json_obj;
}

nlohmann::json GetFsObjectInfo(const std::filesystem::path& path_to_filesystem_object) {
    if (std::filesystem::is_directory(path_to_filesystem_object)) {
        return GetDirectoryInfo(path_to_filesystem_object);
    }
    else if (std::filesystem::is_regular_file(path_to_filesystem_object)) {
        return GetRegularFileInfo(path_to_filesystem_object);
    }
    else {
        throw std::invalid_argument("Invalid filesystem object type.");
    }
}

namespace filesystem_object {

    std::size_t Size(const std::filesystem::path& path_to_filesystem_object) {
        std::size_t size = 0;
        if (std::filesystem::is_directory(path_to_filesystem_object)) {
            for (auto& p : std::filesystem::recursive_directory_iterator(path_to_filesystem_object)) {
                if (std::filesystem::is_regular_file(p)) {
                    size += std::filesystem::file_size(p);
                }
            }
        }
        else {
            size = std::filesystem::file_size(path_to_filesystem_object);
        }
        return size;
    }

    std::ostream& operator<<(std::ostream& os, const Info& info) {
        os << std::left << std::setw(50) << std::setfill(' ') << info.name
            << std::setw(20) << info.type
            << std::setw(20) << info.size;
        return os;
    }

    Info GetInfo(const std::filesystem::path& path_to_filesystem_object) {
        Info info;
        info.name = path_to_filesystem_object.stem().string();
        info.size = Size(path_to_filesystem_object);
        if (std::filesystem::is_directory(path_to_filesystem_object)) {
            info.type = "directory";
        }
        else if (path_to_filesystem_object.has_extension()) {
            info.type = path_to_filesystem_object.extension().string();
        }
        else {
            info.type = "file without extension";
        }
        return info;
    }

}

namespace directory_content {

    std::ostream& operator<<(std::ostream& os, const Info& info) {
        os << std::left << std::setw(50) << std::setfill(' ') << "path_to_directory: " << info.path_to_directory << '\n'
            << std::setw(50) << "size: " << info.size << '\n'
            << std::setw(50) << "files_amount: " << info.files_amount << '\n'
            << std::setw(50) << "directories_amount: " << info.directories_amount << '\n';
        return os;
    }

    Info GetInfo(const std::filesystem::path& path_to_directory) {
        Info info;
        info.path_to_directory = path_to_directory;
        info.size = filesystem_object::Size(path_to_directory);
        info.files_amount = 0;
        info.directories_amount = 0;

        for (const auto& entry : std::filesystem::directory_iterator(path_to_directory)) {
            if (entry.is_regular_file()) {
                ++info.files_amount;
            }
            else if (entry.is_directory()) {
                ++info.directories_amount;
            }
        }

        return info;
    }

}

void CheckDirectoryPath(const std::filesystem::path& path_to_directory) {
    if (!std::filesystem::exists(path_to_directory)) {
        throw std::runtime_error("Filesystem object by path " + path_to_directory.string() + " is not exists!");
    }
    if (!std::filesystem::is_directory(path_to_directory)) {
        throw std::runtime_error("Filesystem object by path " + path_to_directory.string() + " is not a directory!");
    }
}

std::string ReadFileContent(const std::filesystem::path& path_to_file) {
    if (!std::filesystem::exists(path_to_file)) {
        throw std::invalid_argument("Filesystem object by path " + path_to_file.string() + " is not exists!");
    }

    std::ifstream file(path_to_file, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("File by path " + path_to_file.string() + " hasn't been opened!");
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}

std::set<std::string> GetFilesContentFromDirectory(const std::filesystem::path& path_to_directory) {
    std::set<std::string> filesContent;
    for (const auto& entry : std::filesystem::directory_iterator(path_to_directory)) {
        if (std::filesystem::is_regular_file(entry)) {
            std::string fileContent = ReadFileContent(entry.path());
            filesContent.insert(fileContent);
        }
    }
    return filesContent;
}

FilesStorage::FilesStorage(const std::filesystem::path& path_to_directory)
    : path_to_directory_(path_to_directory) {}

void FilesStorage::InitStorage() {
    for (const auto& entry : std::filesystem::directory_iterator(path_to_directory_)) {
        files_content_storage_.insert(ReadFileContent(entry.path()));
    }
}

void FilesStorage::CopyFile(const std::filesystem::path& path_to_file) {
    if (files_content_storage_.find(ReadFileContent(path_to_file)) == files_content_storage_.end()) {
        std::filesystem::copy_file(path_to_file, path_to_directory_ / path_to_file.filename());
        std::cout << "File by path " << path_to_file.string() << " has been copied to directory by path " << path_to_directory_.string() << "!" << std::endl;
        files_content_storage_.insert(ReadFileContent(path_to_file));
    }
}

std::size_t GetFileContentHash(const std::filesystem::path& path_to_file) {
    std::string file_content = ReadFileContent(path_to_file);
    return std::hash<std::string>{}(file_content);
}

void RemoveDuplicatesFromDirectory(const std::filesystem::path& directory_path) {
    std::unordered_map<std::size_t, std::vector<std::filesystem::path>> file_hashes;

    for (const auto& entry : std::filesystem::directory_iterator(directory_path)) {
        if (std::filesystem::is_regular_file(entry.path())) {
            std::size_t file_hash = GetFileContentHash(entry.path());
            file_hashes[file_hash].push_back(entry.path());
        }
    }

    for (const auto& [hash, paths] : file_hashes) {
        if (paths.size() > 1) {
            for (size_t i = 1; i < paths.size(); ++i) {
                std::filesystem::remove(paths[i]);
            }
        }
    }
}

std::filesystem::path GetPathToMove(const std::filesystem::path& path_to_file) {
    std::string fileName = path_to_file.filename().string();
    if (fileName.find("_") == std::string::npos) {
        throw std::invalid_argument("Invalid filename. File path: " + path_to_file.string());
    }
    std::filesystem::path newPath = path_to_file.parent_path();
    std::string stem = path_to_file.stem().string();
    std::size_t underscorePos = stem.find("_");
    newPath /= stem.substr(0, underscorePos) + "/" + stem;
    return newPath;
}


void Move(const std::filesystem::path& path_to_file) {
    std::filesystem::path new_path = GetPathToMove(path_to_file);
    std::filesystem::create_directories(new_path.parent_path());
    std::filesystem::rename(path_to_file, new_path);
    std::cout << "File by path " << path_to_file.string() << " has been moved to " << new_path.string() << std::endl;
}

FileName::FileName(std::filesystem::path path_to_file)
    : path_to_current_file(std::move(path_to_file)) {
}

void FileName::Parse() {
    std::string filename = path_to_current_file.filename().string();
    size_t underscorePos = filename.find('_');
    if (underscorePos == std::string::npos) {
        throw std::invalid_argument("Invalid filename: " + path_to_current_file.string() + "!");
    }

    std::string dateStr = filename.substr(0, underscorePos);
    year = static_cast<uint16_t>(std::stoul(dateStr.substr(0, 4)));
    month = static_cast<uint16_t>(std::stoul(dateStr.substr(4, 2)));
    day = static_cast<uint16_t>(std::stoul(dateStr.substr(6, 2)));

    only_name = filename.substr(underscorePos + 1);
}

bool FileName::IsRemoveRequired() const {
    return year % 5 == 0 && day % 5 == 0;
}

std::filesystem::path GetPathToMove1(const std::filesystem::path& path_to_file) {
    FileName file(path_to_file);
    file.Parse();

    std::filesystem::path newPath = file.path_to_current_file.parent_path();
    newPath.append(std::to_string(file.year) + "_" + std::to_string(file.month) + "_" + std::to_string(file.day) + "_" + file.only_name);
    return newPath;
}

void Move1(const std::filesystem::path& path_to_file) {
    std::filesystem::path newPath = GetPathToMove(path_to_file);

    if (!std::filesystem::exists(newPath.parent_path())) {
        std::filesystem::create_directories(newPath.parent_path());
    }

    std::filesystem::rename(path_to_file, newPath);
    std::cout << "File by path " << path_to_file << " has been moved to " << newPath << "!" << std::endl;
}