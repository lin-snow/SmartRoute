#include "main/main.h"
#include <asio.hpp>
#include "crow.h"
#include "nlohmann/json.hpp"

#include "utils/yamlTool.hpp"


int main() {
    system("chcp 65001"); // UTF-8
    system("cls"); // clear screen

    /* Start the system */
    start();

    return 0;
}