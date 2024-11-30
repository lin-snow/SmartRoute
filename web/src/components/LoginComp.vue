<!-- eslint-disable @typescript-eslint/no-explicit-any -->
<template>
  <div class="mx-auto">
    <el-form
    ref="ruleFormRef"
    style="max-width: 600px"
    :model="ruleForm"
    status-icon
    :rules="rules"
    label-width="auto"
    class="demo-ruleForm"
  >
    <el-form-item label="Username" prop="user">
      <el-input v-model="ruleForm.user" type="username" autocomplete="on" />
    </el-form-item>
    <el-form-item label="Password" prop="pass">
      <el-input
        v-model="ruleForm.pass"
        type="password"
        autocomplete="on"
      />
    </el-form-item>
    <el-form-item>
      <el-button type="primary" @click="submitForm(ruleFormRef)">
        Submit
      </el-button>
      <el-button @click="resetForm(ruleFormRef)">Reset</el-button>
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
  if (!formEl) return
  formEl.validate(async (valid) => {
    if (valid) {
      const formData = new FormData()
      formData.append('username', ruleForm.user)
      formData.append('password', ruleForm.pass)

      console.log('submit!')

      await apiClient.post('admin/login', formData)
        .then((response) => {
          if (response.data.code === 200) {
            console.log('Login successful')
            ElNotification({
              title: 'Login successful',
              message: 'Welcome back!',
              type: 'success',
            })

            // save user info to local storage
            localStorage.setItem('user', JSON.stringify(formData.get('user')))
            localStorage.setItem('pass', JSON.stringify(formData.get('pass')))

            // clear form
            resetForm(formEl)

            // Redirect to admin panel
            router.push('/admin')
          } else {
            console.log('Login failed')
            ElNotification({
              title: 'Login failed',
              message: 'Please check your credentials',
              type: 'error',
            })
          }
        })
        .catch((error) => {
          console.error(error)
          ElNotification({
            title: 'Error',
            message: 'An error occurred',
            type: 'error',
          })
        })
    } else {
      console.log('error submit!')
      return false
    }
  })
}

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
