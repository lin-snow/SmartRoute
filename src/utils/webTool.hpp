#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

std::string readFile(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        return ""; // 文件不存在或无法打开
    }
    std::ostringstream content;
    content << file.rdbuf();
    return content.str();
}

// 获取文件的 MIME 类型
std::string getMimeType(const std::string& filepath) {
    if (filepath.rfind(".js") == filepath.size() - 3) {
        return "application/javascript";
    } else if (filepath.rfind(".css") == filepath.size() - 4) {
        return "text/css";
    } else if (filepath.rfind(".html") == filepath.size() - 5) {
        return "text/html";
    } else if (filepath.rfind(".json") == filepath.size() - 5) {
        return "application/json";
    } else if (filepath.rfind(".png") == filepath.size() - 4) {
        return "image/png";
    } else if (filepath.rfind(".jpg") == filepath.size() - 4 || filepath.rfind(".jpeg") == filepath.size() - 5) {
        return "image/jpeg";
    } else if (filepath.rfind(".svg") == filepath.size() - 4) {
        return "image/svg+xml";
    }
    return "application/octet-stream"; // 默认类型
}