<template>
  <main class="w-screen h-auto">
    <HomeComp />
    <el-button class="shadow absolute top-2 right-4" type="primary">
      <span class="mr-1">
        <el-icon><adminIcon /></el-icon>
      </span>
        <router-link to="/admin" class="mr-2">Admin</router-link>
  </el-button>
  </main>
</template>

<script setup lang="ts">
import HomeComp from '@/components/HomeComp.vue';
import adminIcon from '@/components/icon/adminIcon.vue';
</script>
