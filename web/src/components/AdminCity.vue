<template>
  <div class="h-auto w-fit grid grid-cols-2 gap-4 relative top-40 mx-auto">
        <!-- <h2>Manage Your Cities!</h2> -->
        <div class="border-2 rounded-md border-double p-1 mx-auto shadow  min-w-fit border-orange-500">
          <div class="border-b-2">
            <h2 class="font-mono font-bold text-center">站点列表</h2>
          </div>

          <el-table :data="cityStore.allCities" border style="width: 100%" empty-text="no cities available!" height="26rem">
          <el-table-column label="Name" prop="name" width="120"/>
          <el-table-column label="Code" prop="cityCode" width="90"/>
          <el-table-column label="Actions" align="center" width="180">
            <template #default="scope">
              <el-button size="small" @click="handleEdit(scope.$index, scope.row)">
                Edit
              </el-button>

              <el-button
                size="small"
                type="danger"
                @click="handleDelete(scope.$index, scope.row)"
              >
                删除
              </el-button>
            </template>
          </el-table-column>
        </el-table>
        </div>
      <div class="w-auto">
        <div class="border-2 rounded-md border-double p-1 mx-auto mb-4 shadow w-48 h-auto py-2 border-orange-500 grid grid-rows-2 gap-4">
          <div class="border-1 w-44 h-24 m-1 rounded-md text-center">
                    <span class="font-mono mb-2 font-light">站点统计</span>
                    <div class="mx-auto w-32 h-12 shadow-inner rounded-xl">
                      <span class="text-green-500 relative top-2 font-extrabold">
                        {{ cityStore.citiesCount }}
                      </span>
                    </div>
                </div>

                <div class="border-1 w-44 h-24 m-1 rounded-md text-center ">
                    <span class="font-light font-mono ">运行状况</span>
                    <div class="mx-auto w-32 h-14 shadow-inner rounded-xl text-center font-bold ">
                      <div class="mx-auto w-32 h-14 shadow-inner rounded-xl text-center ">
                      <div v-if="cityStore.citiesCount > 0" class="text-green-500 relative top-4">
                        一切正常
                      </div>
                      <div v-else class="text-yellow-500 relative top-4">
                        无站点
                      </div>
                    </div>
                    </div>
                </div>
        </div>

        <div class="border-2 rounded-md border-double p-1 mx-auto mb-2 shadow w-48 border-orange-500">
        <div class="mb-2 border-b-2">
          <h2 class="font-mono font-bold text-center">添加站点</h2>
        </div>

        <div>
          <el-form
          ref="ruleFormRef"
          style="max-width: 600px"
          :model="ruleForm"
          status-icon
          :rules="rules"
          label-width="auto"
          class="demo-ruleForm"
        >
          <el-form-item label="站点名" prop="name">
            <el-input v-model="ruleForm.name" />
          </el-form-item>

          <el-form-item label="代码" prop="code">
            <el-input
              v-model="ruleForm.code"
            />
          </el-form-item>

          <el-form-item>
            <el-button type="primary" @click="submitForm(ruleFormRef)" class="mx-auto">
              创建
            </el-button>
            <el-button @click="resetForm(ruleFormRef)" class="mx-auto">Reset</el-button>
          </el-form-item>
        </el-form>
        </div>

      </div>


      <div class=" p-1 mx-auto w-48 ">
        <div class="mx-auto w-24">
            <el-button
            type="primary"
            plain
            size="large"
            class="mx-auto shadow-2xl"
          >
            <span>
              <el-icon class="mr-1"><AdminIcon /></el-icon>
            </span>
            <router-link to="/admin">返回面板</router-link>
          </el-button>
        </div>
      </div>


      </div>

  </div>
</template>

<script setup lang="ts">
import { useCityStore } from '@/stores/cityStore';
import { ElNotification, type FormInstance, type FormRules } from 'element-plus'
import { onMounted, reactive, ref } from 'vue';
import { useRouter } from 'vue-router';
import { apiClient } from '@/utils/axios/axios';
import AdminIcon from './icon/adminIcon.vue';

interface City {
  name: string;
  cityCode: string;
}

const cityStore = useCityStore();
const router = useRouter();

const handleDelete = (index: number, row: City) => {
  cityStore.deleteCity(index, row);
}

const handleEdit = (index: number, row: City) => {
  router.push(`/admin/city/edit/${row.cityCode}`);
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
    return callback(new Error('Please input the Name'));
  }

  // 检查是否已经存在
  if (cityStore.allCities && cityStore.allCities.some((city) => city.name === value)) {
    return callback(new Error('City Name already exists'));
  }

  callback();
};

// eslint-disable-next-line @typescript-eslint/no-explicit-any
const validateCode = (rule: any, value: any, callback: any) => {
  // 检查是否为空
  if (!value) {
    return callback(new Error('Please input the Code'));
  }

  // 检查是否为数字
  if (!/^\d+$/.test(value)) {
    return callback(new Error('City Code must be a number'));
  }

  // 检查是否已经存在
  if (cityStore.allCities && cityStore.allCities.some((city) => city.cityCode == value)) {
    return callback(new Error('City Code already exists'));
  }

  callback();
};

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
    return;
  }

  formEl.validate((isValid) => {
    if (!isValid) {
      ElNotification({
        title: 'Error',
        message: '请检查表单',
        duration: 800,
        type: 'error',
      })
      return;
    }

      console.log('submit!')
      // 提交表单
      // 创建 FormData 实例
      const formData = new FormData();
      // 添加表单字段到 FormData 对象中
      formData.append('name', ruleForm.name);
      formData.append('cityCode', ruleForm.code);

      // 提交表单
      apiClient.post('admin/city/add', formData) // 直接发送 formData 对象
        .then(() => {
          cityStore.fetchCities();

          resetForm(formEl);

          ElNotification({
            title: 'Success',
            message: '添加成功',
            type: 'success',
          })

          cityStore.citiesCount += 1;
        })
        .catch((error) => {
          console.error('Error submitting form:', error);
          ElNotification({
            title: 'Error',
            message: '添加失败',
            type: 'error',
          })
        });

  })
}

const resetForm = (formEl: FormInstance | undefined) => {
  if (!formEl) return
  formEl.resetFields()
}

onMounted(() => {
  cityStore.fetchCities();
})
</script>

<style scoped>
.shadow-inner {
  --tw-shadow: inset 0 0px 9px 0 rgb(39 27 18 / 15%);
}
</style>
