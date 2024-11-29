<template>
  <div>
    <h1>Admin City Management</h1>
    <!-- add city by post -->
    <h2>Manage Cities!</h2>
    <el-table :data="allCities" style="width: 100%" empty-text="no cities available!">
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

  </div>
</template>

<script setup lang="ts">
import { onMounted, reactive, ref, watch, computed} from 'vue'
import type { FormInstance, FormRules } from 'element-plus'
import { ElMessage } from 'element-plus';
import { useCityStore } from '@/stores/cityStore';
import { apiClient } from '@/utils/axios/axios';

interface City {
  name: string;
  cityCode: string;
}

// 计算属性：格式化后的表格数据
const allCities = computed(() => cityStore.allCities);

// 删除按钮事件处理
const handleDelete = async (index: number, row: City) => {
  try {
    if (!row.cityCode) return;
    await apiClient.get(`admin/city/delete?cityCode=${row.cityCode}`)
      .then((res) => {
        console.log(res);
        cityStore.fetchCities();
      })
      .catch((error) => {
        console.error('Error:', error);
      });
    ElMessage.success('City deleted successfully');
    cityStore.allCities.splice(index, 1); // 更新状态
  } catch (error) {
    console.error('Error deleting city:', error);
    ElMessage.error('Failed to delete city');
  }
};

const cityStore = useCityStore();
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

watch(cityStore.allCities, () => {
  updateTableData();
})

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
          updateTableData();
          resetForm(formEl);
        })
        .catch((error) => {
          console.error('Error:', error);
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
const updateTableData = () => {
  tableData.value = cityStore.allCities.map((city) => ({
    CityName: city.name,
    CityCode: city.cityCode,
  }));
}

onMounted(async () => {
  await cityStore.fetchCities();
  await cityStore.genSelectableCities();

  if (cityStore.allCities.length > 0) {
    selectableCities.value = cityStore.selectableCities;
    tableData.value = cityStore.allCities.map((city) => ({
      CityName: city.name,
      CityCode: city.cityCode,
    }));
  }
})


</script>
