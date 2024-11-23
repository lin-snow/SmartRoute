# SmartRoute
developing...

## 项目结构
```
D:.
│  build.sh              # 构建脚本
│  CMakeLists.txt        # CMake 构建文件
│  README.md             # 项目说明文件
│  
├─app                    # 存放可执行文件或应用程序的目录
├─build                  # 用于存放构建文件、临时文件等
├─config                 # 配置文件目录 (yaml)
├─data                   # 数据文件存放目录 (json)
├─docs                   # 文档和说明文件
├─frontend               # 前端代码目录（后期 Web 支持）
├─include                # 管理外部依赖目录
├─logs                   # 日志目录
├─src                    # 源代码目录
│  │  main.cpp           # 控制台应用入口文件
│  ├─function            # 核心功能实现（如算法、业务逻辑）
│  ├─graph               # 图算法相关实现（如交通图）
│  ├─server              # 后端服务相关模块（后期可扩展为 Web 服务）
│  └─utils               # 工具类文件
└─test                   # 测试代码目录
```