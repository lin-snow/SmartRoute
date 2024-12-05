<template>
  <div>
      <h1>Update City</h1>
      <p>Current city code: {{ curCityCode }}</p>

      <p>name: {{ oldCity?.name }}</p>
      <p>cityCode: {{ oldCity?.cityCode }}</p>

      <div class="border-2 rounded-md border-double p-1 mx-auto mb-2 shadow w-48 border-orange-500">
        <div class="mb-2 border-b-2">
          <h2 class="font-mono font-bold text-center">更新站点</h2>
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
  </div>
</template>

<script setup lang="ts">
import { useRouter } from 'vue-router';
import { reactive, ref } from 'vue';
import { useCityStore } from '@/stores/cityStore';
import type { FormRules, FormInstance } from 'element-plus';



const router = useRouter();
const cityStore = useCityStore();

// 获取当前路由参数
const curCityCode = router.currentRoute.value.params.cityCode;

// 获取当前城市信息
const oldCity = cityStore.allCities.find((city) => city.cityCode == curCityCode) || null;
console.log(oldCity)

const ruleFormRef = ref<FormInstance>()
const ruleForm = reactive({
  name: oldCity ? oldCity.name : '',
  code: oldCity ? oldCity.cityCode : ''
})


// eslint-disable-next-line @typescript-eslint/no-explicit-any
const validateName = (rule: any, value: any, callback: any) => {
  // 检查是否为空
  if (!value) {
    return callback(new Error('Please input the Name'));
  }

  // 检查新的City是否与其他City有冲突(除去本身)
  if (cityStore.allCities && cityStore.allCities.some((city) => city.name === value && (oldCity && (city.name !== oldCity.name && city.cityCode !== oldCity.cityCode)))) {
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

  // 检查新的City是否与其他City有冲突(除去本身)
  if (cityStore.allCities && cityStore.allCities.some((city) => city.cityCode == value && (oldCity && (city.name !== oldCity.name && city.cityCode !== oldCity.cityCode)))) {
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
  formEl.validate(async (isValid) => {
    if (!isValid) return;

    console.log('submit!');
    // 提交表单
    // 创建 FormData 实例

    if (!oldCity) return;

    const formData = new FormData();

    // 添加表单字段到 FormData 对象中
    formData.append('oldName', oldCity?.name);
    formData.append('oldCityCode', oldCity?.cityCode);
    formData.append('name', ruleForm.name);
    formData.append('cityCode', ruleForm.code);

    await cityStore.updateCity(formData)

    // 跳转到城市列表
    router.push("/admin/city");
  })
}

const resetForm = (formEl: FormInstance | undefined) => {
  if (!formEl) return
  formEl.resetFields()
}

</script>
