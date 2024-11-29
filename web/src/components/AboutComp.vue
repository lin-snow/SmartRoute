<template>
  <div class="text-center absolute top-1/3 left-96">
    <h1 class="text-xl font-mono font-bold">About</h1>

    <p>作者:
      <a href="https://soopy.cn"> L1nSn0w</a>
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
