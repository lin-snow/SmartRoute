<!-- eslint-disable @typescript-eslint/no-explicit-any -->
<template>
  <div class="w-68 mx-auto h-auto absolute top-1/3 left-1/3 ">
    <h2 class="font-mono font-bold mx-1 my-2 italic">Login to <span class="text-lg italic text-sky-500">Admin Panel!</span></h2>
    <el-form
    ref="ruleFormRef"
    style="max-width: 600px"
    :model="ruleForm"
    status-icon
    :rules="rules"
    label-width="auto"
    class="demo-ruleForm"
  >
    <el-form-item label="用户名" prop="user">
      <el-input v-model="ruleForm.user" type="username" autocomplete="on" />
    </el-form-item>
    <el-form-item label="密码" prop="pass">
      <el-input
        v-model="ruleForm.pass"
        type="password"
        autocomplete="on"
      />
    </el-form-item>
    <el-form-item>
      <el-button type="primary" @click="submitForm(ruleFormRef)">
        登录
      </el-button>
      <el-button @click="resetForm(ruleFormRef)">重置</el-button>
      <br>
      <!-- 返回首页 -->
      <el-button
        type="primary"
        plain
        class="my-2 mx-2"
      >
        <span>
          <el-icon class="mr-1"><homeIcon /></el-icon>
        </span>
        <router-link to="/" class="mr-2">返回首页</router-link>
      </el-button>
    </el-form-item>
  </el-form>
  </div>
</template>

<script setup lang="ts">
import { reactive, ref, onMounted } from 'vue'
import type { FormInstance, FormRules } from 'element-plus'
import { ElNotification } from 'element-plus'
import { apiClient } from '@/utils/axios/axios'
import { useRouter } from 'vue-router'

const router = useRouter()



const ruleFormRef = ref<FormInstance>()

// eslint-disable-next-line @typescript-eslint/no-explicit-any
const validateUser = (rule: any, value: any, callback: any) => {
  if (value === '') {
    callback(new Error('Please input the password again'))
  } else {
    callback()
  }
}

// eslint-disable-next-line @typescript-eslint/no-explicit-any
const validatePass = (rule: any, value: any, callback: any) => {
  if (value === '') {
    callback(new Error('Please input the password'))
  } else {
    callback()
  }
}

const ruleForm = reactive({
  user: '',
  pass: '',
})

const rules = reactive<FormRules<typeof ruleForm>>({
  pass: [{ validator: validatePass, trigger: 'blur' }],
  user: [{ validator: validateUser, trigger: 'blur' }],
})

const submitForm = (formEl: FormInstance | undefined) => {
  if (!formEl) return;
  formEl.validate(async (valid) => {
    if (valid) {
      const formData = new FormData();
      formData.append('username', ruleForm.user);
      formData.append('password', ruleForm.pass);

      console.log('submit!');

      try {
        const response = await apiClient.post('admin/login', formData);
        if (response.data.code === 200) {
          console.log('Login successful');
          ElNotification({
            title: '登录成功！',
            message: '尊贵的管理员，欢迎回来！',
            type: 'success',
          });

          // Save user info to local storage
          localStorage.setItem('user', JSON.stringify(ruleForm.user));
          localStorage.setItem('pass', JSON.stringify(ruleForm.pass));

          // Clear form
          resetForm(formEl);

          // Redirect to admin panel
          router.push('/admin');
        } else {
          console.log('Login failed');
          ElNotification({
            title: '登录失败！',
            message: '请检查用户名和密码',
            type: 'error',
          });
        }
      } catch (error) {
        console.error(error);
        ElNotification({
          title: 'Error',
          message: 'An error occurred',
          type: 'error',
        });
      }
    } else {
      console.log('error submit!');
      // 注意：不需要 return false，这里直接退出即可
    }
  });
};

const resetForm = (formEl: FormInstance | undefined) => {
  if (!formEl) return
  formEl.resetFields()
}

onMounted(() => {
  console.log('Login component mounted')
  if (localStorage.getItem('user') && localStorage.getItem('pass')) {
    ruleForm.user = localStorage.getItem('user') as string
    ruleForm.pass = localStorage.getItem('pass') as string
  }
  console.log('User:', ruleForm.user)
  console.log('Pass:', ruleForm.pass)

  // Redirect to admin panel if user is already logged in
  if (ruleForm.user && ruleForm.pass) {
    router.push('/admin')
  }
})
</script>
