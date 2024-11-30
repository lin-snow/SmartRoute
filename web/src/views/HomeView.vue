<template>
  <main class="w-screen h-auto">
    <el-button class="shadow-xl absolute top-4 right-8" type="primary">
      <span class="mr-1">
        <el-icon><adminIcon /></el-icon>
      </span>
        <router-link to="/login" class="mr-2">Admin</router-link>
    </el-button>
    <HomeComp />
  </main>
</template>

<script setup lang="ts">
import HomeComp from '@/components/HomeComp.vue';
import adminIcon from '@/components/icon/adminIcon.vue';
</script>
