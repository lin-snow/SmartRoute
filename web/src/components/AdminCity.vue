<template>
  <div class="h-auto w-fit grid grid-cols-2 gap-4 relative top-20 mx-auto mb-24">
    <div class="bg-white rounded-xl shadow-lg p-6 min-w-[500px] border border-gray-200 glass-effect">
      <div class="mb-6">
        <h2 class="text-2xl font-bold text-gray-800 text-center">站点管理</h2>
        <div class="w-16 h-1 bg-amber-500 mx-auto mt-2"></div>
      </div>

      <el-table
        :data="cityStore.allCities"
        border
        style="width: 100%"
        empty-text="暂无站点数据"
        height="26rem"
        class="custom-table"
      >
        <el-table-column
          label="站点名称"
          prop="name"
          width="160"
          align="center"
        />
        <el-table-column
          label="站点代码"
          prop="cityCode"
          width="120"
          align="center"
        />
        <el-table-column
          label="操作"
          align="center"
          width="200"
        >
          <template #default="scope">
            <el-button
              type="primary"
              size="small"
              plain
              class="mr-2 hover:shadow-md transition-shadow"
              @click="handleEdit(scope.$index, scope.row)"
            >
              编辑
            </el-button>

            <el-button
              type="danger"
              size="small"
              plain
              class="hover:shadow-md transition-shadow"
              @click="handleDelete(scope.$index, scope.row)"
            >
              删除
            </el-button>
          </template>
        </el-table-column>
      </el-table>
    </div>

    <div class="bg-white rounded-xl shadow-lg p-6 min-w-[500px] border border-gray-200 glass-effect">
      <div class="mb-6">
        <h2 class="text-2xl font-bold text-gray-800 text-center">站点状态</h2>
        <div class="w-16 h-1 bg-amber-500 mx-auto mt-2"></div>
      </div>

      <div class="grid grid-cols-2 gap-4 mb-8">
        <div class="bg-gray-50 rounded-lg p-4 text-center">
          <h3 class="text-lg font-semibold text-gray-700 mb-2">站点统计</h3>
          <div class="text-3xl font-bold text-green-500">
            {{ cityStore.citiesCount }}
          </div>
        </div>

        <div class="bg-gray-50 rounded-lg p-4 text-center">
          <h3 class="text-lg font-semibold text-gray-700 mb-2">运行状况</h3>
          <div v-if="cityStore.citiesCount > 0" class="text-xl font-bold text-green-500">
            一切正常
          </div>
          <div v-else class="text-xl font-bold text-yellow-500">无站点</div>
        </div>
      </div>

      <div class="mb-6">
        <h2 class="text-2xl font-bold text-gray-800 text-center">添加站点</h2>
        <div class="w-16 h-1 bg-amber-500 mx-auto mt-2"></div>
      </div>

      <el-form
        ref="ruleFormRef"
        :model="ruleForm"
        status-icon
        :rules="rules"
        label-width="100px"
        class="max-w-md mx-auto"
      >
        <el-form-item label="站点名" prop="name">
          <el-input v-model="ruleForm.name" placeholder="请输入站点名称" />
        </el-form-item>

        <el-form-item label="代码" prop="code">
          <el-input v-model="ruleForm.code" placeholder="请输入站点代码" />
        </el-form-item>

        <el-form-item class="flex justify-center gap-4 mt-6">
          <el-button type="primary" @click="submitForm(ruleFormRef)" class="w-32">
            创建
          </el-button>
          <el-button @click="resetForm(ruleFormRef)" class="w-32">重置</el-button>
        </el-form-item>
      </el-form>

      <div class="flex justify-center mt-8">
        <el-button type="primary" plain size="large" class="shadow-md hover:shadow-lg transition-shadow">
          <el-icon class="mr-2"><AdminIcon /></el-icon>
          <router-link to="/admin">返回面板</router-link>
        </el-button>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
import { useCityStore } from '@/stores/cityStore'
import { ElNotification, type FormInstance, type FormRules } from 'element-plus'
import { onMounted, reactive, ref } from 'vue'
import { useRouter } from 'vue-router'
import { apiClient } from '@/utils/axios/axios'
import AdminIcon from './icon/adminIcon.vue'

interface City {
  name: string
  cityCode: string
}

const cityStore = useCityStore()
const router = useRouter()

const handleDelete = (index: number, row: City) => {
  cityStore.deleteCity(index, row)
}

const handleEdit = (index: number, row: City) => {
  router.push(`/admin/city/edit/${row.cityCode}`)
}

const ruleFormRef = ref<FormInstance>()
const ruleForm = reactive({
  name: '',
  code: '',
})

// eslint-disable-next-line @typescript-eslint/no-explicit-any
const validateName = (rule: any, value: any, callback: any) => {
  // 检查是否为空
  if (!value) {
    return callback(new Error('Please input the Name'))
  }

  // 检查是否已经存在
  if (cityStore.allCities && cityStore.allCities.some((city) => city.name === value)) {
    return callback(new Error('City Name already exists'))
  }

  callback()
}

// eslint-disable-next-line @typescript-eslint/no-explicit-any
const validateCode = (rule: any, value: any, callback: any) => {
  // 检查是否为空
  if (!value) {
    return callback(new Error('Please input the Code'))
  }

  // 检查是否为数字
  if (!/^\d+$/.test(value)) {
    return callback(new Error('City Code must be a number'))
  }

  // 检查是否已经存在
  if (cityStore.allCities && cityStore.allCities.some((city) => city.cityCode == value)) {
    return callback(new Error('City Code already exists'))
  }

  callback()
}

const rules = reactive<FormRules<typeof ruleForm>>({
  name: [{ validator: validateName, trigger: 'blur' }],
  code: [{ validator: validateCode, trigger: 'blur' }],
})

const submitForm = (formEl: FormInstance | undefined) => {
  if (!formEl) {
    ElNotification({
      title: '表单错误',
      message: '请检查表单',
      duration: 800,
      type: 'error',
    })
    return
  }

  formEl.validate((isValid) => {
    if (!isValid) {
      ElNotification({
        title: 'Error',
        message: '请检查表单',
        duration: 800,
        type: 'error',
      })
      return
    }

    console.log('submit!')
    // 提交表单
    // 创建 FormData 实例
    const formData = new FormData()
    // 添加表单字段到 FormData 对象中
    formData.append('name', ruleForm.name)
    formData.append('cityCode', ruleForm.code)

    // 提交表单
    apiClient
      .post('admin/city/add', formData) // 直接发送 formData 对象
      .then(() => {
        cityStore.fetchCities()

        resetForm(formEl)

        ElNotification({
          title: 'Success',
          message: '添加成功',
          type: 'success',
        })

        cityStore.citiesCount += 1
      })
      .catch((error) => {
        console.error('Error submitting form:', error)
        ElNotification({
          title: 'Error',
          message: '添加失败',
          type: 'error',
        })
      })
  })
}

const resetForm = (formEl: FormInstance | undefined) => {
  if (!formEl) return
  formEl.resetFields()
}

onMounted(() => {
  cityStore.fetchCities()
})
</script>

<style scoped>
.shadow-inner {
  --tw-shadow: inset 0 0px 9px 0 rgb(39 27 18 / 15%);
}
</style>
