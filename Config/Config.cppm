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
            throw ConfigException("配置文件不存在");
        }
        const auto file_extension = config_file_path_.extension();
        if (file_extension == ".xml") {
            throw ConfigException("不支持的配置文件格式");
        }

        if (file_extension == ".json") {
            throw ConfigException("不支持的配置文件格式");
        }

        if (file_extension == ".txt"){
            std::string line;
            std::ifstream in(config_file_path_);
            if (!in.is_open())
                throw ConfigException("打开配置文件失败");

            while (in >> line) {
                auto split_pos = std::ranges::find(line.begin(), line.end(),split_char_);
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

};


NAMESPACE_END(Config)


