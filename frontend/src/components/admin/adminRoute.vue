<template>
  <div>
    <h1>Admin Route Management!</h1>
    <h2>Add Route</h2>
    <el-form
      ref="routeFormRef"
      :model="form"
      :rules="rules"
      label-width="auto"
      style="max-width: 600px"
    >
      <el-form-item label="Departure City" prop="from">
        <el-select
          v-model="form.from"
          placeholder="Please select your departure city"
          filterable
        >
          <el-option
            v-for="city in selectableCities"
            :key="city.CityCode"
            :label="city.CityName"
            :value="city.CityCode"
          />
        </el-select>
      </el-form-item>
      <el-form-item label="Destination City" prop="to">
        <el-select
          v-model="form.to"
          placeholder="Please select your destination city"
          filterable
        >
          <el-option
            v-for="city in destinationCities"
            :key="city.CityCode"
            :label="city.CityName"
            :value="city.CityCode"
          />
        </el-select>
      </el-form-item>
      <el-form-item label="Vehicle Type" prop="vehicleType">
        <el-radio-group v-model="form.vehicleType">
          <el-radio :label="'0'">Train</el-radio>
          <el-radio :label="'1'">Plane</el-radio>
        </el-radio-group>
      </el-form-item>
      <el-form-item label="Vehicle Code" prop="vehicleCode">
        <el-input v-model="form.vehicleCode" placeholder="Enter vehicle code" />
      </el-form-item>
      <el-form-item label="Time Range">
        <el-time-picker
        v-model="value1"
        is-range
        range-separator="To"
        start-placeholder="Start time"
        end-placeholder="End time"
        format="HH:mm"
        @change="handleTimeChange"
      />

      </el-form-item>
      <el-form-item label="Cost" prop="cost">
        <el-input v-model.number="form.cost" placeholder="Enter cost (￥)" />
      </el-form-item>
      <el-form-item label="Distance" prop="distance">
        <el-input v-model.number="form.distance" placeholder="Enter distance (km)" />
      </el-form-item>
      <el-form-item>
        <el-button type="primary" @click="onSubmit">Create</el-button>
        <el-button @click="onReset">Cancel</el-button>
      </el-form-item>
    </el-form>
  </div>
</template>

<script setup lang="ts">
import { onMounted, reactive, ref } from 'vue'
import { ElMessage } from 'element-plus'
import type { FormInstance } from 'element-plus';
import { useCityStore } from '@/stores/cityStore';
import { apiClient } from '@/utils/axios/axios';

// 初始化两个时间范围
const value1 = ref<[Date, Date]>()
// 初始化出发时间和到达时间
const departureTime = ref<string>('');
const arrivalTime = ref<string>('');

// 处理时间变化的函数
const handleTimeChange = (value: [Date, Date]) => {
  if (value) {
    console.log("@@@@@@@@@@@@@@@@@@@@@@@@@@@")
    console.log(value);
    departureTime.value = value[0].getHours().toString().padStart(2, '0') + ':' + value[0].getMinutes().toString().padStart(2, '0');
    arrivalTime.value = value[1].getHours().toString().padStart(2, '0') + ':' + value[1].getMinutes().toString().padStart(2, '0');
  }
};

const routeFormRef = ref<FormInstance | null>(null);

// 使用 Pinia Store
const cityStore = useCityStore();

// 城市数据
const selectableCities = ref(cityStore.selectableCities); // 出发城市
const destinationCities = ref(cityStore.selectableCities); // 目的地城市

const form = reactive({
  from: '',
  to: '',
  vehicleType: '',
  vehicleCode: '',
  departureTime: '',
  arrivalTime: '',
  cost: '',
  distance: '',
});

const rules = reactive({
  from: [{ required: true, message: 'Please select a departure city', trigger: 'change' }],
  to: [{ required: true, message: 'Please select a destination city', trigger: 'change' }],
  vehicleType: [{ required: true, message: 'Please select a vehicle type', trigger: 'change' }],
  vehicleCode: [{ required: true, message: 'Please enter the vehicle name', trigger: 'blur' }],
  departureDate: [{ required: true, message: 'Please select a departure date', trigger: 'change' }],
  arrivalTime: [
    { required: true, message: 'Please select an arrival time', trigger: 'change' },
    { pattern: /^([0-1]\d|2[0-3]):([0-5]\d)$/, message: 'Time must be in HH:mm format', trigger: 'change' },
  ],
  cost: [
    { required: true, message: 'Please enter the cost', trigger: 'blur' },
    { type: 'number', message: 'Cost must be a number', trigger: 'blur' },
  ],
  distance: [
    { required: true, message: 'Please enter the distance', trigger: 'blur' },
    { type: 'number', message: 'Distance must be a number', trigger: 'blur' },
  ],
});


const onSubmit = async () => {
  routeFormRef.value?.validate(async (valid) => {
    if (valid) {
      try {
        // 将两个时间分别转成字符串
        form.departureTime = departureTime.value;
        form.arrivalTime = arrivalTime.value;
        console.log(form);
        console.log("submit")

        const formData = new FormData();
        formData.append('from', form.from);
        formData.append('to', form.to);
        formData.append('vehicleType', form.vehicleType);
        formData.append('vehicleCode', form.vehicleCode);
        formData.append('departureTime', form.departureTime);
        formData.append('arrivalTime', form.arrivalTime);
        formData.append('cost', form.cost);
        formData.append('distance', form.distance);

        // 提交表单
      await apiClient.post('admin/route/add', formData) // 直接发送 formData 对象
        .then((res) => {
          console.log(res);
          cityStore.fetchCities();
        })
        .catch((error) => {
          console.error('Error:', error);
        });
        ElMessage.success('Route added successfully');
        onReset();
      } catch {
        ElMessage.error('Failed to add route');
      }
    } else {
      ElMessage.error('Please fill in all required fields');
    }
  });
}

const onReset = () => {
  if (routeFormRef.value) {
    routeFormRef.value.resetFields();
  }
  Object.assign(form, {
    departureCity: '',
    destinationCity: '',
    vehicleType: '',
    vehicleName: '',
    departureDate: '',
    arrivalTime: '',
    cost: null,
    distance: null,
  });
};

onMounted(async () => {
  await cityStore.fetchCities();
  await cityStore.genSelectableCities();

  selectableCities.value = cityStore.selectableCities;
})
</script>
