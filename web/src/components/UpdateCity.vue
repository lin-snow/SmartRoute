<template>
  <div class="h-auto w-fit relative top-40 mx-auto">
    <div class="bg-white rounded-xl shadow-lg p-6 min-w-[500px] border border-gray-200 glass-effect">
      <div class="mb-6">
        <h2 class="text-2xl font-bold text-gray-800 text-center">编辑站点</h2>
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

        <el-form-item class="flex justify-center items-center gap-3 mt-6">
          <el-button
            @click="router.push('/admin/city')"
            class="w-24 hover:shadow-md transition-shadow"
          >
            返回
          </el-button>
          <el-button
            @click="resetForm(ruleFormRef)"
            class="w-24 hover:shadow-md transition-shadow"
          >
            重置
          </el-button>
          <el-button
            type="primary"
            @click="submitForm(ruleFormRef)"
            class="w-24 hover:shadow-md transition-shadow"
          >
            保存更改
          </el-button>
        </el-form-item>
      </el-form>
    </div>
  </div>
</template>

<script setup lang="ts">
import { useRouter } from 'vue-router';
import { reactive, ref } from 'vue';
import { useCityStore } from '@/stores/cityStore';
import { type FormRules, type FormInstance, ElNotification } from 'element-plus';



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
  if (!formEl) return;

  formEl.validate(async (isValid) => {
    if (!isValid) {
      ElNotification({
        title: '表单错误',
        message: '请检查表单是否正确',
        type: 'error',
        duration: 1000,
      })
      return;
    }

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

<style scoped>
.glass-effect {
  background: rgba(255, 255, 255, 0.95);
  backdrop-filter: blur(10px);
}

:deep(.el-input__wrapper) {
  box-shadow: 0 0 0 1px #dcdfe6 !important;
}

:deep(.el-input__wrapper:hover) {
  box-shadow: 0 0 0 1px #c0c4cc !important;
}
</style>
