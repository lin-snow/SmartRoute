# SmartRoute
SmartRoute 是一个前端基于 Vue3 、 Vite 、 Element Plus 、 TypeScript 、 TailwindCSS ;
后端基于 C++ 、 CrowCpp、 NlohmannJson 、 FKYaml 、 CMake 的智能路线规划系统。

## 运行样例
![SmartRoute](./docs/homepage.png)

## 项目结构
``` shell
.
├── build.bat                     // 编译整个项目的bat脚本
├── build_backend.bat             // 编译后端的bat脚本
├── build_frontend.bat            // 编译前端的bat脚本
├── start.bat                     // 编译后的app启动脚本
├── CMakeLists.txt                // Cmake配置文件
├── README.md                     // 项目README
├── LICENSE                       // MIT 开源许可证
│
├── app                           // (文件夹) 存放整个项目编译后的最终可执行文件
├── build                         // (文件夹) 存放Cmake编译链接后的文件
│
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
    └── dist                      // (文件夹) 前端编译构建好的最终文件

```

## 食用方式
### 快速上手
- 法一（推荐）
1. 从Github 的 Release 可直接下载已经编译完的完整可执行文件
2. 解压后直接运行里面的 `start.bat` 文件即可使用


- 法二
1. 配置 [`Mingw64`](https://www.mingw-w64.org/) + [`Cmake`](https://cmake.org/) + [`Nodejs`](https://nodejs.org/) 环境后
2. clone repo 到本地 `git clone https://github.com/lin-snow/SmartRoute.git`
3. 导航到`web` 目录下执行 `npm i` ，等待执行完成
4. 执行项目根目录下的 `build.bat`  文件等待编译完成
5. 项目启动后打开浏览器访问 `http://127.0.0.1:23333` 即可使用

## TODOS
- [x] 实现所有功能基本可用
- [ ] 实现Log日志
- [ ] 算法优化，如最省时、最省钱、最少换成等...
- [ ] 更好的UI / UX
- [ ] 完善的文档
- [ ] 实现一键构建所需运行环境
- [ ] ~~更丰富的服务，如对规划完的路线提供一键订票~~
- [ ] ~~跨平台~~  

## 为什么会有SmartRoute?
本项目起源于本鼠鼠的大二数据结构课设中的一个题目，由于本人不会qt，然后又在往后端开发发展，所以索性拿这个课设过一下前后端开发，算是一次练习吧！

## 为什么要使用C++开发后端呢？
一是出于好奇，想尝试一下什么体验，二是可以顺便学一学Cmake和Cpp等。

# 致谢
[Asio](https://think-async.com/Asio/) : Asio is a cross-platform C++ library for network and low-level I/O programming that provides developers with a consistent asynchronous model using a modern C++ approach.

[CrowCpp](https://github.com/CrowCpp/Crow) : A Fast and Easy to use microframework for the web.

[Nlohmann Json](https://github.com/nlohmann/json) : JSON for Modern C++

[fkYAML](https://github.com/fktn-k/fkYAML) : A C++ header-only YAML library