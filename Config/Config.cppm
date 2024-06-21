/*******************************************************************************
 * @Author : yongheng
 * @Data   : 2024/06/18 22:30
*******************************************************************************/

module;
#include <algorithm>


#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <utility>
#include "../Macros.h"
export module Config;


void CreateDefaultConfigFile(std::filesystem::path default_file_path) { 
    std::ofstream out(default_file_path);
    out << "color=RED";
}

export NAMESPACE_BEGIN(Config)
class ConfigException final : public std::exception {
    std::string message_;
public:
    explicit ConfigException(std::string  message) : message_(std::move(message)) {  }

    [[nodiscard]]
    const char *what() const noexcept override {
        return message_.c_str();
    }


};

class Config {
    std::filesystem::path config_file_path_;
    std::map<std::string,std::string> config_map_;
    char split_char_ = '=';
public:
    Config(std::filesystem::path path,char split_char) : Config(std::move(path)) {  }

    explicit Config(std::filesystem::path path) : config_file_path_(std::move(path)){
        if (!std::filesystem::exists(config_file_path_)) {
            CreateDefaultConfigFile(config_file_path_);
        }
        const auto file_extension = config_file_path_.extension();
        if (file_extension == ".xml") {
            throw ConfigException("unsupport config file format");
        }

        if (file_extension == ".json") {
            throw ConfigException("unsupport config file format");
        }

        if (file_extension == ".txt"){
            std::string line;
            std::ifstream in(config_file_path_);
            if (!in.is_open())
                throw ConfigException("open config file is bad");
            
            while (in >> line) {
                auto split_pos = std::ranges::find(line.begin(), line.end(),split_char_);
                if (split_pos == line.end())
                    throw ConfigException("config file format is error: " + line);

                auto key = std::string(line.begin(),split_pos++);
                auto val = std::string(split_pos ,line.end());
                config_map_.insert({key,val});
                std::cout << key << ": " << val << std::endl;
            }
        }

        else {
            throw ConfigException("不支持的配置文件格式");
        }
    }


    std::string operator[] (const std::string &key) const {
        const auto pair = config_map_.find(key);
        if (pair == config_map_.end())
            throw ConfigException("找不到键值: " + key);
        return pair->second;
    }
};


NAMESPACE_END(Config)


