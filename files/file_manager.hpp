#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <cgraph.h>
#include <gvcext.h>
#include <map>
#include <string>
#include <filesystem>

#include "../graph/ts_instance.hpp"

class file_manager {
    static void load_graph_into_program(Agraph_t *graph, std::map<std::string, std::shared_ptr<node> > &nodesMap, std::vector<std::shared_ptr<edge> > &edges);

    static bool load_graph(const std::string &file_name, GVC_t *gvc, Agraph_t *&graph, std::unique_ptr<ts_instance> &value1);

    static void folder_exists_check();

    static void file_naming_conflicts_check(const std::string &file_name, std::string &output_file);

public:
    static const std::string INSTANCES_PATH;

    static const std::string RESULTS_PATH;

    static std::unique_ptr<ts_instance> read_dot_file(const std::string &file_name);

    static std::vector<std::filesystem::directory_entry> get_dot_instances(const std::string &directory_path);

    static void save_solution(const std::string &file_name, const std::string &file_content);
};


#endif
