# 使用 Ubuntu 22.04 LTS 作为基础镜像
FROM ubuntu:22.04

# 设置工作目录
WORKDIR /app

# 禁用交互模式，防止 Docker 构建卡住
ENV DEBIAN_FRONTEND=noninteractive

# 更新系统并安装必要的工具和依赖
RUN apt update && apt install -y \
    software-properties-common \
    build-essential \
    wget \
    curl \
    git \
    libssl-dev \
    libpthread-stubs0-dev \
    apt-transport-https \
    ca-certificates \
    lsb-release \
    gnupg \
    unzip \
    snapd \
    && apt clean

# 安装 CMake（使用 snap 安装最新版本）
RUN snap install cmake --classic

# 安装最新版本的 GCC 和 G++
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test && apt update && apt install -y \
    gcc-13 \
    g++-13 \
    && apt clean

# 设置 GCC 和 G++ 的默认版本
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 100 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-13 100

# 安装 fnm (Fast Node Manager) 以安装指定版本的 Node.js
RUN curl -fsSL https://fnm.vercel.app/install | bash

# 激活 fnm
RUN echo 'source ~/.bashrc' >> ~/.bashrc

# 下载并安装 Node.js 22 版本
RUN bash -c "source ~/.bashrc && fnm use --install-if-missing 22"

# 验证 Node.js 和 npm 版本
RUN bash -c "source ~/.bashrc && node -v && npm -v"

# 拷贝项目的所有文件到容器中
COPY . /app

# 确保 build.sh 文件可执行
RUN chmod +x /app/build.sh

# 执行 build.sh 脚本来编译前后端，并生成 app 文件夹
RUN bash /app/build.sh

# 将生成的可执行文件和其他必要的文件复制到容器中
COPY app /app

# 暴露服务端口
EXPOSE 23333

# 容器启动时，进入 /app 目录并执行 SmartRoute
CMD ["bash", "-c", "cd /app && ./SmartRoute"]
