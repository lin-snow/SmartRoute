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
    } else if (filepath.rfind(".ico") == filepath.size() - 4) {
        return "image/x-icon";
    } else if (filepath.rfind(".ttf") == filepath.size() - 4) {
        return "font/ttf";
    } else if (filepath.rfind(".otf") == filepath.size() - 4) {
        return "font/otf";
    } else if (filepath.rfind(".woff") == filepath.size() - 5) {
        return "font/woff";
    } else if (filepath.rfind(".woff2") == filepath.size() - 6) {
        return "font/woff2";
    } else if (filepath.rfind(".eot") == filepath.size() - 4) {
        return "font/eot";
    } else if (filepath.rfind(".mp3") == filepath.size() - 4) {
        return "audio/mpeg";
    } else if (filepath.rfind(".mp4") == filepath.size() - 4) {
        return "video/mp4";
    } else if (filepath.rfind(".pdf") == filepath.size() - 4) {
        return "application/pdf";
    }
    return "application/octet-stream"; // 默认类型
}