<template>
  <div>
    <el-container>
      <el-main>
        <el-aside>
          hello
        </el-aside>

        <el-aside>
          <h2>Add Route</h2>
          <el-form
            ref="routeFormRef"
            :model="form"
            :rules="rules"
            label-width="auto"
            style="max-width: 600px"
          >
            <el-form-item label="出发点" prop="from">
              <el-select
                v-model="form.from"
                placeholder="Please select your departure city"
                filterable
              >
                <el-option
                  v-for="city in cityStore.allCities"
                  :key="city.cityCode"
                  :label="city.name"
                  :value="city.cityCode"
                />
              </el-select>
            </el-form-item>
            <el-form-item label="目的地" prop="to">
              <el-select
                v-model="form.to"
                placeholder="Please select your destination city"
                filterable
              >
                <el-option
                  v-for="city in cityStore.allCities"
                  :key="city.cityCode"
                  :label="city.name"
                  :value="city.cityCode"
                />
              </el-select>
            </el-form-item>
            <el-form-item label="交通工具类型" prop="vehicleType">
              <el-radio-group v-model="form.vehicleType">
                <el-radio :label="'0'">火车</el-radio>
                <el-radio :label="'1'">飞机</el-radio>
              </el-radio-group>
            </el-form-item>
            <el-form-item label="班号" prop="vehicleCode">
              <el-input v-model="form.vehicleCode" placeholder="Enter vehicle code" />
            </el-form-item>
            <el-form-item label="出发和到达时间">
              <el-time-picker
              v-model="rangeTime"
              is-range
              range-separator="To"
              start-placeholder="Start time"
              end-placeholder="End time"
              format="HH:mm"
              @change="handleTimeChange"
            />

            </el-form-item>
            <el-form-item label="票价" prop="cost">
              <el-input v-model.number="form.cost" placeholder="Enter cost (￥)" />
            </el-form-item>
            <el-form-item label="距离" prop="distance">
              <el-input v-model.number="form.distance" placeholder="Enter distance (km)" />
            </el-form-item>
            <el-form-item>
              <el-button type="primary" @click="onSubmit">Create</el-button>
              <el-button @click="onReset">Cancel</el-button>
            </el-form-item>
          </el-form>
        </el-aside>
      </el-main>
      <el-main>
        <h2>Manage Route</h2>
        <el-table :data="routesStore.formattedAllRoutes" style="width: 100%" empty-text="no routes available!">
        <el-table-column label="Route ID" prop="routeId" />
        <el-table-column label="出发点" prop="from" />
        <el-table-column label="目的地" prop="to" />
        <el-table-column label="距离" prop="distance" />
        <el-table-column label="耗时" prop="duration" />
        <el-table-column label="费用" prop="cost" />
        <el-table-column label="交通工具" prop="vehicleType" />
        <el-table-column label="班号" prop="vehicleCode" />
        <el-table-column label="出发时间" prop="departureTime" />
        <el-table-column label="到达时间" prop="arrivalTime" />
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
      </el-main>
    </el-container>
  </div>
</template>

<script setup lang="ts">
import { useRoutesStore } from '@/stores/routeStore';
import { apiClient } from '@/utils/axios/axios';
import { useCityStore } from '@/stores/cityStore';
import { ElMessage, type FormInstance } from 'element-plus'
import { onMounted, reactive, ref } from 'vue';

const routesStore = useRoutesStore();
const cityStore = useCityStore();

//------------------------ Add Route ------------------------

// 初始化两个时间范围
const rangeTime = ref<[Date, Date]>()
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
        ElMessage.success('Route 添加成功');
        routesStore.fetchRoutes();
        onReset();
      } catch {
        ElMessage.error('Route 添加失败');
      }
    } else {
      ElMessage.error('请填写正确的信息');
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
//------------------------ Add Route ------------------------

//------------------------ Manage Route ------------------------
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

const handleDelete = (index: number, row: Route) => {
  routesStore.deleteRoute(index, row);
};


//------------------------ Manage Route ------------------------
onMounted(async () => {
  await cityStore.fetchCities();
  routesStore.fetchRoutes();
});
</script>
