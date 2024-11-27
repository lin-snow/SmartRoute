<template>
  <div>
    <h1>Admin Panel</h1>
    <p>Click on the buttons below to navigate to the city or route management page.</p>

    <!-- 模块切换 -->
    <el-switch
      v-model="value1"
      class="mb-2"
      active-text="Admin Route"
      inactive-text="Admin City"
    />

    <!-- 动态显示子组件 -->
    <component :is="currentComponent" />
  </div>
</template>

<script setup lang="ts">
import { ref, computed, onMounted } from 'vue';
import { defineAsyncComponent } from 'vue';
import { useCityStore } from '@/stores/cityStore';

const cityStore = useCityStore();

// 切换状态
const value1 = ref(true);

// 动态导入组件
const AdminCity = defineAsyncComponent(() => import('@/components/admin/adminCity.vue'));
const AdminRoute = defineAsyncComponent(() => import('@/components/admin/adminRoute.vue'));

// 计算当前显示的组件
const currentComponent = computed(() => (value1.value ? AdminRoute : AdminCity ));

onMounted(() => {
  cityStore.fetchCities();
  console.log('Admin Panel Mounted');
});

</script>
