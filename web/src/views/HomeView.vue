<template>
  <main class="w-screen h-auto">
    <el-button
      class="shadow-xl absolute top-4 right-8 rounded-lg border-2 border-sky-400/50"
      type="primary"
      size="large"
    >
      <span class="mr-2 flex items-center">
        <el-icon class="text-lg"><adminIcon /></el-icon>
      </span>
      <router-link to="/login" class="mr-1 font-mono font-bold text-base">Admin</router-link>
    </el-button>

    <!-- RouteMap Button -->
    <el-button
      class="shadow-xl absolute top-4 right-40 rounded-lg border-2 border-sky-400/50"
      type="primary"
      size="large"
    >
      <span class="mr-2 flex items-center">
        <el-icon class="text-lg"><mapIcon /></el-icon>
      </span>
      <router-link to="/routeMap" class="mr-1 font-mono font-bold text-base">RouteMap</router-link>
    </el-button>

    <HomeComp />
  </main>
</template>

<script setup lang="ts">
import HomeComp from '@/components/HomeComp.vue';
import adminIcon from '@/components/icon/adminIcon.vue';
import mapIcon from '@/components/icon/mapIcon.vue';

import { ElNotification } from 'element-plus';
import { onMounted } from 'vue';
import { frame } from '@/utils/canvas';

onMounted(() => {
  frame();
  ElNotification({
    title: '欢迎！',
    message: '欢迎使用SmartRoute！',
    type: 'success',
    duration: 1500,
  });
});
</script>
