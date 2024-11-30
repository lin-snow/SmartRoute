<template>
  <div class="w-2/5 mx-auto relative top-64">

      <h1 class="my-2 font-mono">Welcome to <span class="italic text-sky-400 text-2xl">Admin Panel!</span> </h1>

      <!-- 返回首页 -->
      <el-button
        plain
        size="large"
        class="my-2 mr-1 shadow-2xl"
      >
        <span>
          <el-icon class="mr-1"><homeIcon /></el-icon>
        </span>
        <router-link to="/">返回首页</router-link>
      </el-button>

      <el-button
        type="primary"
        plain
        size="large"
        class="my-2 mr-1 shadow-2xl"
      >
        <span>
          <el-icon class="mr-1"><cityIcon /></el-icon>
        </span>
        <router-link to="/admin/city">管理站点</router-link>
      </el-button>
      <el-button
        type="primary"
        plain
        size="large"
        class="my-2 mr-1 shadow-2xl"
      >
        <span>
          <el-icon class="mr-1"><routeIcon /></el-icon>
        </span>
        <router-link to="/admin/route">管理路线</router-link>
      </el-button>

      <br><br>



      <!-- shutdown -->
        <el-button
          type="danger"
          plain
          class="my-2 ml-1 mr-4"
          @click="dialogVisible = true"
        >
          <span>
            <el-icon class="mr-1"><routeIcon /></el-icon>
          </span>
          停止服务
      </el-button>

        <el-dialog
          v-model="dialogVisible"
          title="警告"
          width="500"
          align-center
        >
          <span>确定要保存并关闭服务器吗？</span>
          <template #footer>
          <span  class="dialog-footer">
            <el-button @click="dialogVisible = false">取 消</el-button>
            <el-button type="danger" @click="shutdown">确 定</el-button>
          </span>
          </template>
        </el-dialog>


      <!-- Logout -->
      <el-button
        type="warning"
        plain
        class="my-2"
        @click="logout"
      >
        <span>
          <el-icon class="mr-1"><routeIcon /></el-icon>
        </span>
        退出登录
      </el-button>

  </div>
</template>

<script setup lang="ts">
import { apiClient } from '@/utils/axios/axios';
import cityIcon from './icon/cityIcon.vue';
import routeIcon from './icon/routeIcon.vue';
import homeIcon from './icon/homeIcon.vue';
import { useRouter } from 'vue-router';
import { onMounted, ref } from 'vue';
import { ElNotification } from 'element-plus';

const router = useRouter();

const dialogVisible = ref(false)

const shutdown = () => {
  console.log('Shutting down server...');

  // 关闭当前的el-dialog
  dialogVisible.value = false;

  ElNotification({
        title: '服务器已关闭',
        message: '服务器已关闭',
        type: 'success',
      });

  apiClient.get('admin/shutdown') // This is a custom endpoint that shuts down the server
    .then(() => {
      console.log('Server has been shut down');
    })
    .catch((err) => {
      console.error(err);
    });
};

const logout = () => {
  console.log('Logging out...');
  // clear the local storage
  localStorage.removeItem('user');
  localStorage.removeItem('pass');

  // redirect to login page
  router.push('/login');
};

onMounted(() => {
  console.log('Admin Panel mounted');
  ElNotification({
    title: '欢迎！',
    message: '欢迎回到控制面板!',
    type: 'success',
  });
})
</script>
