<template>
  <div>
    <router-view></router-view>
  </div>
</template>

<script setup lang="ts">

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
