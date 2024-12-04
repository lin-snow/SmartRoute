# SmartRoute
SmartRoute 是一个前端基于 Vue3 、 Vite 、 Element Plus 、 TypeScript 、 TailwindCSS ;
后端基于 C++ 、 CrowCpp、 NlohmannJson 、 FKYaml 、 CMake 的智能路线规划系统。

## 运行样例
...

## 项目结构
```
.
├── build.bat                     // 编译整个项目的bat脚本
├── build_backend.bat             // 编译后端的bat脚本
├── build_frontend.bat            // 编译前端的bat脚本
├── start.bat                     // 编译后的app启动脚本
├── CMakeLists.txt                // Cmake配置文件
├── README.md                     // 项目README
├── LICENSE                       // MIT 开源许可证
|
├── app                           // (文件夹) 存放整个项目编译后的最终可执行文件
├── build                         // (文件夹) 存放Cmake编译链接后的文件
|
├── config                        // (文件夹) 存放SmartRoute的配置文件
│   └── config.yaml               // SmartRoute的配置文件
├── data                          // (文件夹) 存放SmartRoute的数据文件
│   ├── cities.json               // 站点数据文件
│   └── routes.json               // 线路数据文件
├── docs                          // 存放项目文档
├── include                       // 后端使用的第三方库
│   ├── asio                      // CrowCpp依赖的独立ASIO库
│   ├── crow                      // CrowCpp后端框架库
│   ├── fkYAML                    // 用于支持读写yaml格式配置文件的库
│   └── nlohmann                  // 用于支持读写json格式数据文件的库
├── logs                          // 存放服务器运行的日志
├── src                           // (文件夹) 存放后端所有源代码
│   ├── graph                     // (文件夹) 存放与图数据结构相关的模块
│   │   ├── graph.h               // 图数据结构的相关数据类型定义
│   │   └── graph.hpp             // 图数据结构的实现
│   ├── main                      // (文件夹) 存放main.cpp的头文件和实现
│   │   ├── main.h                // main.cpp所需的函数签名
│   │   └── main.hpp              // mian.h的函数实现
│   ├── main.cpp                  // 后端的主入口
│   ├── module                    // (文件夹)定义项目所需的数据模型
│   │   ├── constants.h           // 存放自定义的常量数据
│   │   ├── module.h              // 存放SmartRotue相关的数据模型定义
│   │   └── module.hpp            // 模型的具体实现
│   ├── server                    // (文件夹) 存放实现后端所需的源文件
│   │   ├── server.h              // 定义服务器模型
│   │   └── server.hpp            // 服务器模型的具体实现
│   ├── system                    // (文件夹) 存放SmartRoute项目系统相关的源代码
│   │   ├── system.h              // SmartRoute系统数据模型定义
│   │   └── system.hpp            // SmartRoute系统的具体实现
│   └── utils                     // (文件夹) 存放必要的实用操作函数的源代码
│       ├── jsonTool.hpp          // 存放与json相关的实用组件
│       ├── webTool.hpp           // 存放与web相关的实用组件
│       └── yamlTool.hpp          // 存放与yaml相关的实用组件
└── web                           // (文件夹) 存放前端的工程文件夹
    ├── dist                      // (文件夹) 前端编译构建好的最终文件

```

## 食用方式
### 快速上手
1. 双击运行app目录下的  `start.bat` 文件即可启动项目的前后端


### 从零编译
1. 配置`Mingw64` + `Cmake` + `Nodejs` 环境后
2. 双击运行根目录的 `build.bat` 后等待构建前后端
3. 导航到 `app` 目录下执行 `start.bat` 文件即可启动

## TODOS
...

## 为什么会有SmartRoute?
...

# 致谢
writing...