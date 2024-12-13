# 使用官方的 Ubuntu 作为基础镜像
FROM ubuntu:latest

# 设置工作目录
WORKDIR /app

# 禁用交互模式，防止 Docker 构建卡住
ENV DEBIAN_FRONTEND=noninteractive

# 更新系统并安装必要的工具和依赖
RUN apt update && apt install -y \
    bash \
    build-essential \
    wget \
    curl \
    git \
    unzip \
    xz-utils \
    dos2unix \
    && apt clean

# 安装 CMake（从官网下载最新版本）
RUN curl -L https://github.com/Kitware/CMake/releases/download/v3.31.2/cmake-3.31.2-linux-x86_64.sh -o cmake.sh \
    && chmod +x cmake.sh \
    && ./cmake.sh --skip-license --prefix=/usr/local \
    && rm cmake.sh

# 下载 Node.js 预构建的二进制文件
RUN wget https://nodejs.org/dist/v22.12.0/node-v22.12.0-linux-x64.tar.xz

# 解压 Node.js 二进制文件
RUN tar -xJf node-v22.12.0-linux-x64.tar.xz -C /usr/local

# 设置 Node.js 的路径
ENV PATH=/usr/local/node-v22.12.0-linux-x64/bin:$PATH

# 清理下载的 tar.xz 文件
RUN rm node-v22.12.0-linux-x64.tar.xz

# 验证 Node.js 安装
RUN node -v
RUN npm -v

# 拷贝项目的所有文件到容器中
COPY . /app

RUN cd /app

# 将 build.sh 文件转换为 Unix 风格的换行符
RUN dos2unix build.sh

# 确保 build.sh 文件可执行
RUN chmod +x build.sh

# 执行 build.sh 脚本来编译前后端，并生成 app 文件夹
RUN bash build.sh

# 暴露服务端口
EXPOSE 23333

# 容器启动时，进入 /app 目录并执行 SmartRoute
CMD ["bash", "-c", "cd app && ./SmartRoute"]