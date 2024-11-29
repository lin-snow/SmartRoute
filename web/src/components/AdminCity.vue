<template>
  <div>
    <el-container>
      <el-aside>
        <h2>Manage Your Cities!</h2>
        <el-table :data="cityStore.allCities" style="width: 100%" empty-text="no cities available!">
        <el-table-column label="City Name" prop="name" />
        <el-table-column label="City Code" prop="cityCode" />
        <el-table-column label="Actions" align="right">
          <template #default="scope">
            <el-button
              size="small"
              type="danger"
              @click="handleDelete(scope.$index, scope.row)"
            >
              Delete
            </el-button>
          </template>
        </el-table-column>
      </el-table>

      </el-aside>
      <el-aside>
        <el-form
        ref="ruleFormRef"
        style="max-width: 600px"
        :model="ruleForm"
        status-icon
        :rules="rules"
        label-width="auto"
        class="demo-ruleForm"
      >
        <el-form-item label="City Name" prop="name">
          <el-input v-model="ruleForm.name" />
        </el-form-item>

        <el-form-item label="City Code" prop="code">
          <el-input
            v-model="ruleForm.code"
          />
        </el-form-item>

        <el-form-item>
          <el-button type="primary" @click="submitForm(ruleFormRef)">
            Submit
          </el-button>
          <el-button @click="resetForm(ruleFormRef)">Reset</el-button>
        </el-form-item>
      </el-form>

      </el-aside>
    </el-container>
  </div>
</template>

<script setup lang="ts">
import { useCityStore } from '@/stores/cityStore';
import type { FormInstance, FormRules } from 'element-plus'
import { onMounted, reactive, ref } from 'vue';
import { apiClient } from '@/utils/axios/axios';

interface City {
  name: string;
  cityCode: string;
}

const cityStore = useCityStore();

const handleDelete = (index: number, row: City) => {
  cityStore.deleteCity(index, row);
}

const ruleFormRef = ref<FormInstance>()
const ruleForm = reactive({
  name: '',
  code: '',
})

// eslint-disable-next-line @typescript-eslint/no-explicit-any
const validateName = (rule: any, value: any, callback: any) => {
  if (!value) {
    return callback(new Error('Please input the Name'));
  }

  if (!cityStore.allCities || cityStore.allCities.length === 0) {
    console.error('City data is not loaded yet!');
    return callback(new Error('City data not available'));
  }

  if (cityStore.allCities.some((city) => city.name.toLowerCase() === value.toLowerCase())) {
    return callback(new Error('City Name already exists'));
  }

  callback();
};

// eslint-disable-next-line @typescript-eslint/no-explicit-any
const validateCode = (rule: any, value: any, callback: any) => {
  if (!value) {
    return callback(new Error('Please input the Code'));
  }

  if (!cityStore.allCities || cityStore.allCities.length === 0) {
    console.error('City data is not loaded yet!');
    return callback(new Error('City data not available'));
  }

  if (cityStore.allCities.some((city) => city.cityCode.toString() === value.toString())) {
    return callback(new Error('City Code already exists'));
  }

  callback();
};

const rules = reactive<FormRules<typeof ruleForm>>({
  name: [{ validator: validateName, trigger: 'blur' }],
  code: [{ validator: validateCode, trigger: 'blur' }],
})

const submitForm = (formEl: FormInstance | undefined) => {
  if (!formEl) return
  formEl.validate((valid) => {
    if (valid) {
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
        })
        .catch((error) => {
          console.error('Error submitting form:', error);
        });
    } else {
      console.log('error submit!')
    }
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
