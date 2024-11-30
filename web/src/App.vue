<template>
  <div>
    <router-view></router-view>
  </div>
</template>

<script setup lang="ts">

import { onMounted } from 'vue';
import { frame } from '@/utils/canvas';

onMounted(() => {
  frame();
});

</script>
