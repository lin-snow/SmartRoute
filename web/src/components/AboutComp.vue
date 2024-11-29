<template>
  <div class="text-center absolute top-1/3 left-96">
    <h1 class="text-xl font-mono font-bold">About</h1>

    <p class="font-mono font-light my-4">
      SmartRoute 是一个前端基于 Vue3 、 Vite 、 Element Plus 、 TypeScript 、 TailwindCSS ,<br>
      后端基于 C++ 、 CrowCpp、 NlohmannJson 、 FKYaml 、 CMake 的智能路线规划系统。
    </p>

    <p>作者:
      <a href="https://soopy.cn">
        <span class="text-amber-700 underline"> L1nSn0w </span>
      </a>
    </p>

    <!-- 回到首页 -->
    <el-button
      type="primary"
      plain
      class="my-2 mr-1"
    >
      <span>
        <el-icon class="mr-1"><homeIcon /></el-icon>
      </span>
      <router-link to="/" class="mr-2">返回首页</router-link>
    </el-button>
  </div>
</template>
