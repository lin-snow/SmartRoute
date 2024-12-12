# Linux使用的编译脚本
set -e

echo "Building Backend ..."

# 删除build目录
rm -rf build && mkdir build

# 进入build目录
cd build

# 编译
cmake .. && make

# 返回上级目录
cd ..

echo "Building Backend Done."

echo "Building Frontend ..."

# 进入web目录
cd web

# 安装依赖
npm install

# 清除dist目录
rm -rf dist

# 构建
npm run build:dev

# 复制dist目录到build目录
cp -r dist ../build

# 返回上级目录
cd ..

echo "Building Frontend Done."

echo "Building App ..."

# 删除app目录
rm -rf app && mkdir app

cd build && cp SmartRoute ../app && cp -r dist ../app && cp -r config ../app && cp -r data ../app

cd .. && cd app

echo "Building App Done."

echo "Build Dond."

# 运行SmartRoute
./SmartRoute


