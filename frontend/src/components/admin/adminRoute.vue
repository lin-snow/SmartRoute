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

    <h2>Manage Route</h2>
    <el-table :data="formattedTableData" style="width: 100%">
    <el-table-column label="Route ID" prop="routeId" />
    <el-table-column label="From" prop="from" />
    <el-table-column label="To" prop="to" />
    <el-table-column label="Distance" prop="distance" />
    <el-table-column label="Duration" prop="duration" />
    <el-table-column label="Cost" prop="cost" />
    <el-table-column label="Vehicle Type" prop="vehicleType" />
    <el-table-column label="Vehicle Code" prop="vehicleCode" />
    <el-table-column label="Departure Time" prop="departureTime" />
    <el-table-column label="Arrival Time" prop="arrivalTime" />
    <el-table-column label="Actions" align="right">
      <template #default="scope">
        <!-- <el-button size="small" @click="handleEdit(scope.$index, scope.row)">
          Edit
        </el-button> -->
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
  </div>
</template>

<script setup lang="ts">
import { onMounted, reactive, ref, computed } from 'vue'
import { ElMessage } from 'element-plus'
import type { FormInstance } from 'element-plus';
import { useCityStore } from '@/stores/cityStore';
import { useRoutesStore } from '@/stores/routesStore';
import { apiClient } from '@/utils/axios/axios';

// 初始化两个时间范围
const value1 = ref<[Date, Date]>()
// 初始化出发时间和到达时间
const departureTime = ref<string>('');
const arrivalTime = ref<string>('');

// 处理时间变化的函数
const handleTimeChange = (value: [Date, Date]) => {
  if (value) {
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

const routesStore = useRoutesStore();
interface Route {
  routeId: number;
  from: number;
  to: number;
  distance: number;
  duration: number;
  vehicleType: number;
  vehicleCode: string;
  departureTime: string;
  arrivalTime: string;
  cost: number;
}

const allTableRoutes = ref<Route[]>(routesStore.allRoutes);
// // 编辑按钮事件处理
// const handleEdit = (index: number, row: Route) => {
//   console.log('Edit row:', index, row);
//   // 这里可以添加编辑逻辑，例如打开一个包含表单的对话框
// };

// 格式化城市名称的函数
// 格式化城市名称的函数
const formatCityName = (cityCode: string) => {
  console.log("Searching for city code:", cityCode); // 打印正在搜索的城市代码
  const city = cityStore.selectableCities.find(city => city.CityCode == cityCode);
  if (city) {
    console.log("Found city:", city.CityName); // 如果找到城市，打印城市名称
  } else {
    console.log("City not found for code:", cityCode); // 如果未找到城市，打印城市代码
  }
  return city ? city.CityName : 'Unknown City';
};

// 计算属性：格式化后的表格数据
const formattedTableData = computed(() => {
  return routesStore.allRoutes.map((route) => ({
    ...route,
    from: formatCityName(route.from.toString()), // 确保 route.from 是字符串
    to: formatCityName(route.to.toString()), // 确保 route.to 是字符串
  }));
});


// 删除按钮事件处理
const handleDelete = async (index: number, row: Route) => {
  try {
    await apiClient.delete(`/data/delete/${row.routeId}`); // 确保路径正确
    ElMessage.success('Route deleted successfully');
    routesStore.allRoutes.splice(index, 1);
  } catch (error) {
    console.error('Error deleting route:', error);
    ElMessage.error('Failed to delete route');
  }
};

onMounted(async () => {
  await cityStore.fetchCities();
  await cityStore.genSelectableCities();
  await routesStore.fetchRoutes();
  selectableCities.value = cityStore.selectableCities;
  allTableRoutes.value = routesStore.allRoutes;
})
</script>
