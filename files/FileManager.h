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

    static std::unique_ptr<TSInstance> readDotFile(const std::string &filename);

    static std::vector<std::filesystem::directory_entry> getDotInstances(const std::string &directoryPath);

    static void saveSolution(const std::string& fileName, const std::string& fileContent);
};


#endif //FILEMANAGER_H
