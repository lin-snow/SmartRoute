<template>
  <div class="flex flex-col items-center justify-center min-h-screen">
    <div class="text-center">
      <h1 class="text-xl font-mono font-bold mb-4">关于</h1>

      <div class="bg-gradient-to-r from-blue-100 to-purple-100 p-6 rounded-lg shadow-md max-w-2xl">
        <p class="font-mono text-lg leading-relaxed mb-6 text-gray-700">
          SmartRoute 是一个智能路线规划系统，融合了现代前端和后端技术：
          <br>
          <span class="font-semibold text-blue-600">前端：</span> Vue3、Vite、Element Plus、TypeScript、TailwindCSS
          <br>
          <span class="font-semibold text-purple-600">后端：</span> C++、CrowCpp、NlohmannJson、FKYaml、CMake
        </p>

        <div class="bg-white p-4 rounded-md shadow-inner">
          <p class="font-light text-gray-600">
            管理员账号: <span class="font-medium text-red-500">admin</span>
            密码: <span class="font-medium text-red-500">admin</span>
          </p>
        </div>

        <p class="mt-6 text-gray-700">
          作者：
          <a href="https://soopy.cn" class="group">
            <span class="text-amber-700 font-semibold group-hover:text-amber-500 transition-colors duration-300 border-b-2 border-amber-300"> L1nSn0w </span>
          </a>
        </p>
      </div>

      <!-- 回到首页 -->
      <el-button
        type="primary"
        plain
        size="large"
        class="mt-6 shadow-2xl"
      >
        <span>
          <el-icon class="mr-1"><homeIcon /></el-icon>
        </span>
        <router-link to="/" class="mr-2">返回首页</router-link>
      </el-button>
    </div>
  </div>
</template>
