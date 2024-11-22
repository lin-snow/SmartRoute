#include <iostream>
#include <string>
#include <winsock2.h>
#include <asio.hpp>
#include "crow.h"
#include "nlohmann/json.hpp"
#include "fkYAML/node.hpp"

#include "./function/main.h"

using json = nlohmann::json;

int main() {
    // 设置UTF-8编码
    system("chcp 65001");
    
    crow::SimpleApp app;

    

    std::string configPath = "config/config.yaml";
    std::ifstream ifs(configPath);

    // deserialize the loaded file contents.
    fkyaml::node root = fkyaml::node::deserialize(ifs);

    // print the deserialized YAML nodes by serializing them back.
    std::cout << root << std::endl;

    CROW_ROUTE(app, "/")([](){
        printHello();
        // 返回json数据
        std::string jsonPath = "data/data.json";
        std::ifstream jsonFile(jsonPath);

        std::string jsonData((std::istreambuf_iterator<char>(jsonFile)), std::istreambuf_iterator<char>());
        
        jsonFile.close();

        crow::json::wvalue x;
        x = crow::json::load(jsonData.c_str(), jsonData.size());

        crow::json::wvalue res;
        res["msg"] = "Hello, SmartRoute!";
        res["code"] = 200;
        res["data"] = crow::json::load(jsonData.c_str(), jsonData.size());

        return res;
    });

    app.port(18080).multithreaded().run();
}