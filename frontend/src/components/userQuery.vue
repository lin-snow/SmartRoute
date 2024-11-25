<template>
  <div>
    <h1>User Query</h1>

  </div>
</template>

<script setup lang="ts">
import { onMounted } from 'vue'
import { useCityStore } from '@/stores/cityStore';

const cityStore = useCityStore();

onMounted(() => {
  cityStore.fetchCities();
  console.log(cityStore.allCities);
});
</script>

<style scoped>
</style>
