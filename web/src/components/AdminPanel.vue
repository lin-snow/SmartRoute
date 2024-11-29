<template>
  <div class="w-2/5 mx-auto relative top-64">
    <div>
      <h1 class="my-2 font-mono">Welcome to Admin Panel! </h1>

      <el-button
        type="primary"
        plain
        class="my-2 mr-1"
      >
        <span>
          <el-icon class="mr-1"><cityIcon /></el-icon>
        </span>
        <router-link to="/admin/city">管理站点</router-link>
      </el-button>
      <el-button
        type="primary"
        plain
        class="my-2 mr-1"
      >
        <span>
          <el-icon class="mr-1"><routeIcon /></el-icon>
        </span>
        <router-link to="/admin/route">管理路线</router-link>
      </el-button>
    </div>
  </div>
</template>

<script setup lang="ts">
import cityIcon from './icon/cityIcon.vue';
import routeIcon from './icon/routeIcon.vue';
</script>
