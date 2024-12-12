#!/bin/bash

set -e  # 遇到错误立即退出

# 清理并创建固定目录
clean_build_dir() {
    echo ">>> 清理并创建 build 目录"
    rm -rf build
    mkdir -p build
}

clean_dist_dir() {
    echo ">>> 清理并创建 dist 目录"
    rm -rf web/dist
    mkdir -p web/dist
}

build_backend() {
    echo ">>> 开始构建后端"
    clean_build_dir
    cd build
    cmake .. && make
    cd ..
    echo ">>> 后端构建完成"
}

build_frontend() {
    echo ">>> 开始构建前端"
    cd web
    npm install
    clean_dist_dir
    npm run build:dev
    cp -r dist ../build
    cd ..
    echo ">>> 前端构建完成"
}

build_app() {
    echo ">>> 开始构建应用"
    rm -rf app
    mkdir -p app
    cd build
    cp SmartRoute ../app
    cp -r dist ../app
    cp -r config ../app
    cp -r data ../app
    cd ..
    echo ">>> 应用构建完成"
}

run_app() {
    echo ">>> 运行 SmartRoute"
    cd app && ./SmartRoute
}

# 主逻辑
echo "========== 开始构建项目 =========="
build_backend
build_frontend
build_app
echo "========== 项目构建完成 =========="


# # 询问是否运行
# read -p "是否运行 SmartRoute? (y/n) " -n 1 -r

# if [[ $REPLY =~ ^[Yy]$ ]]; then
#     run_app
# fi

