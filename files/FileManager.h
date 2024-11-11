//
// Created by Jakub Janak on 9/14/24.
//

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <__filesystem/directory_entry.h>

#include "../graph/TSInstance.h"

class FileManager {
public:
    static const std::string INSTANCES_PATH;

    static const std::string RESULTS_PATH;

    static std::unique_ptr<TSInstance> read_dot_file(const std::string &file_name);

    static std::vector<std::filesystem::directory_entry> get_dot_instances(const std::string &directory_path);

    static void save_solution(const std::string& file_name, const std::string& file_content);
};


#endif //FILEMANAGER_H
