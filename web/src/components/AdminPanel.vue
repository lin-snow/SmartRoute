<template>
  <div class="w-2/5 mx-auto relative top-64">
    <div>
      <h1 class="my-2 font-mono">Welcome to Admin Panel! </h1>

      <!-- 返回首页 -->
      <el-button
        plain
        class="my-2 mr-1"
      >
        <span>
          <el-icon class="mr-1"><homeIcon /></el-icon>
        </span>
        <router-link to="/">返回首页</router-link>
      </el-button>

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

      <el-button
        type="danger"
        plain
        class="my-2 mr-1"
        @click="shutdown"
      >
        <span>
          <el-icon class="mr-1"><routeIcon /></el-icon>
        </span>
        停止服务
      </el-button>
    </div>
  </div>
</template>

<script setup lang="ts">
import { apiClient } from '@/utils/axios/axios';
import cityIcon from './icon/cityIcon.vue';
import routeIcon from './icon/routeIcon.vue';
import homeIcon from './icon/homeIcon.vue';

const shutdown = () => {
  console.log('Shutting down server...');
  apiClient.get('admin/shutdown') // This is a custom endpoint that shuts down the server
    .then(() => {
      console.log('Server has been shut down');
    })
    .catch((err) => {
      console.error(err);
    });
};
</script>
