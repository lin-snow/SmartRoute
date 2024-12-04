#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "fkYAML/node.hpp"

std::string getHost() {
    std::string configPath = "config/config.yaml";
    std::ifstream ifs(configPath);

    if (ifs.is_open()) {
        // deserialize the yaml file contents
        fkyaml::node root = fkyaml::node::deserialize(ifs);

        std::string host = root["server"][0]["host"].get_value_ref<std::string&>();

        // std::cout << "Host: " << host << std::endl;

        return host;
    } else {
        std::cout << "Unable to open file" << std::endl;
        return "localhost";
    }
}


long getPort() {
    std::string configPath = "config/config.yaml";
    std::ifstream ifs(configPath);

    if (ifs.is_open()) {
        // deserialize the yaml file contents
        fkyaml::node root = fkyaml::node::deserialize(ifs);

        long port = root["server"][1]["port"].get_value<int>();

        // std::cout << "Port: " << port << std::endl;

        return port;
    } else {
        std::cout << "Unable to open file" << std::endl;
        return -1;
    }
}

std::string getWebPath() {
    std::string configPath = "config/config.yaml";
    std::ifstream ifs(configPath);

    if (ifs.is_open()) {
        // deserialize the yaml file contents
        fkyaml::node root = fkyaml::node::deserialize(ifs);

        std::string webPath = root["server"][2]["webPath"].get_value_ref<std::string&>();

        std::cout << "Web path: " << webPath << std::endl;

        return webPath;
    } else {
        std::cout << "Unable to open file" << std::endl;
        return "dist";
    }
}

std::string getAdminPassword() {
    std::string configPath = "config/config.yaml";
    std::ifstream ifs(configPath);

    if (ifs.is_open()) {
        // deserialize the yaml file contents
        fkyaml::node root = fkyaml::node::deserialize(ifs);

        std::string password = root["admin"][1]["password"].get_value_ref<std::string&>();

        std::cout << "Admin Password: " << password << std::endl;

        return password;
    } else {
        std::cout << "Unable to open file" << std::endl;
        return "admin";
    }

}

std::string getAdminUsername() {
    std::string configPath = "config/config.yaml";
    std::ifstream ifs(configPath);

    if (ifs.is_open()) {
        // deserialize the yaml file contents
        fkyaml::node root = fkyaml::node::deserialize(ifs);

        std::string username = root["admin"][0]["username"].get_value_ref<std::string&>();

        std::cout << "Admin Username: " << username << std::endl;

        return username;
    } else {
        std::cout << "Unable to open file" << std::endl;
        return "admin";
    }
}