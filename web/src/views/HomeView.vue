<template>
  <main class="w-screen h-auto">
    <el-button
      class="shadow-2xl absolute top-4 right-8 hover:scale-105 transition-transform duration-300 rounded-lg border-2 border-sky-400/50"
      type="primary"
      size="large"
    >
      <span class="mr-2 flex items-center">
        <el-icon class="text-lg"><adminIcon /></el-icon>
      </span>
      <router-link to="/login" class="mr-1 font-mono font-bold text-base">Admin</router-link>
    </el-button>
    <HomeComp />
  </main>
</template>

<script setup lang="ts">
import HomeComp from '@/components/HomeComp.vue';
import adminIcon from '@/components/icon/adminIcon.vue';

</script>
