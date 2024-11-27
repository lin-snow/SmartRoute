<template>
  <div>
    <h1>Admin City Management</h1>
    <!-- add city by post -->
    <h2> Show all cities</h2>
    <el-table :data="tableData" border style="width: 100%">
      <el-table-column prop="CityName" label="CityName" width="270" />
      <el-table-column prop="CityCode" label="CityCode" width="270" />
    </el-table>


    <h2> Add City </h2>
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


    <h2> Delete City </h2>
    <h3>Choose what to del</h3>
    <div>
    <!-- 城市选择框 -->
    <el-select
      v-model="cityToDelete"
      placeholder="请选择城市"
      filterable
      style="width: 300px"
    >
      <el-option
        v-for="city in selectableCities"
        :key="city.CityCode"
        :label="city.CityName"
        :value="city.CityCode"
      />
    </el-select>
    </div>

    <el-button type="danger" @click="deleteCity(cityToDelete)">Delete</el-button>

    <h2> Edit City </h2>
  </div>
</template>

<script setup lang="ts">
import { onMounted, reactive, ref } from 'vue'
import type { FormInstance, FormRules } from 'element-plus'
import { useCityStore } from '@/stores/cityStore';
import { apiClient } from '@/utils/axios/axios';


const cityStore = useCityStore();
const cityToDelete = ref(null);
const selectableCities = ref<Array<{ CityName: string; CityCode: string }>>([]);

const ruleFormRef = ref<FormInstance>()

// 将allCities的数据转换为tableData的数据
const tableData = ref<Array<{ CityName: string; CityCode: string }>>([]);



const validateName = (rule: any, value: any, callback: any) => {
  if (value === '') {
    callback(new Error('Please input the Name'))
  } else {
    if (ruleForm.name !== '') {
      // 检查是否与allCities中的name重复
      if (cityStore.allCities.some((city) => city.name === ruleForm.name)) {
        callback(new Error('City Name already exists'))
      }
    }
    callback()
  }
}

const validateCode = (rule: any, value: any, callback: any) => {
  if (value === '') {
    callback(new Error('Please input the Code'))
  } else {
    if (ruleForm.code !== '') {
      // 检查是否与allCities中的cityCode重复
      if (cityStore.allCities.some((city) => city.cityCode == ruleForm.code)) {
        callback(new Error('City Code already exists'))
      }
    }
    callback()
  }
}

const ruleForm = reactive({
  name: '',
  code: '',
})

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
        .then((res) => {
          console.log(res);
          cityStore.fetchCities();
        })
        .catch((error) => {
          console.error('Error:', error);
        });
    } else {
      console.log('error submit!')
    }
  })
}

// get query
const deleteCity = (cityCode: string | null) => {
  if (!cityCode) return;
  apiClient.get(`admin/city/delete?cityCode=${cityCode}`)
    .then((res) => {
      console.log(res);
      cityStore.fetchCities();
    })
    .catch((error) => {
      console.error('Error:', error);
    });
}

const resetForm = (formEl: FormInstance | undefined) => {
  if (!formEl) return
  formEl.resetFields()
}

onMounted(async () => {
  await cityStore.fetchCities();
  await cityStore.genSelectableCities();

  selectableCities.value = cityStore.selectableCities;
  tableData.value = cityStore.allCities.map((city) => ({
    CityName: city.name,
    CityCode: city.cityCode,
  }));
})


</script>
