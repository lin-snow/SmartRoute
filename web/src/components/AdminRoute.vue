<template>
  <div class="mx-auto grid grid-rows-2 gap-2 min-w-fit mt-4">
    <div class="mx-auto grid grid-cols-2 gap-32 ">
        <div class=" border-2 border-double border-amber-700 p-1 rounded-md shadow-md ">
          <h2 class="font-mono font-bold mx-auto text-center">添加线路</h2>
          <div>
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
                    placeholder="请选择你的出发点"
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
                    placeholder="请选择你的目的地"
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
                  <el-input v-model="form.vehicleCode" placeholder="输入班号" />
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
                  <el-input v-model.number="form.cost" placeholder="输入票价 (￥)" />
                </el-form-item>
                <el-form-item label="距离" prop="distance">
                  <el-input v-model.number="form.distance" placeholder="输入距离 (km)" />
                </el-form-item>
                <el-form-item class="ml-12 grid grid-rows-2 gap-8 mt-10">
                  <el-button type="primary" @click="onSubmit">创建</el-button>
                  <el-button @click="onReset">取消</el-button>
                </el-form-item>
              </el-form>
          </div>
        </div>

      <div class="min-w-fit border-2 border-double border-amber-700 p-1 rounded-md shadow-md">
        <!-- 线路统计 -->
        <div class=" p-1 mx-auto mb-4 w-48 h-auto py-2 grid grid-rows-2 gap-4">
          <div class="border-1 w-44 h-24 m-1 rounded-md text-center mx-auto">
              <span class="font-mono mb-2 font-bold my-1">线路统计</span>
              <div class="mx-auto w-32 h-12 shadow-inner rounded-xl">
                <span class="text-green-500 relative top-2">
                  {{ routesStore.routesCount }}
                </span>
              </div>
          </div>
          <div class="border-1 w-44 h-24 m-1 rounded-md text-center ">
              <span class="font-bold font-mono">运行状况</span>
              <div class="mx-auto w-32 h-14 shadow-inner rounded-xl text-center ">
                <div v-if="routesStore.routesCount > 0" class="text-green-500 relative top-4">
                  一切正常
                </div>
                <div v-else class="text-yellow-500 relative top-4">
                  无线路
                </div>
                </div>
          </div>
          </div>
        <!-- 回到面板 -->
        <div class="mx-auto w-36">
          <el-button
            type="primary"
            plain
            size="large"
            class="mx-auto shadow-md w-36 rounded-lg"
          >
            <span>
              <el-icon class="mr-1"><AdminIcon /></el-icon>
            </span>
            <router-link to="/admin">返回面板</router-link>
          </el-button>
        </div>

      </div>
    </div>

    <div class="border-2 border-amber-700 mx-auto h-auto rounded-md shadow-md min-w-fit p-2 mb-12">
      <h2 class="font-mono font-bold mx-auto border-b-2 border-amber-400 border-dotted">线路管理</h2>
      <div class=" w-full">
        <el-table :data="routesStore.formattedAllRoutes" border style="width: 100%" empty-text="no routes available!" height="18rem">
        <el-table-column label="Route ID" prop="routeId" width="90" />
        <el-table-column label="出发点" prop="from" width="95" />
        <el-table-column label="目的地" prop="to" width="95"/>
        <el-table-column label="距离(km)" prop="distance" width="95"/>
        <el-table-column label="耗时(m)" prop="duration" width="95"/>
        <el-table-column label="费用(￥)" prop="cost" width="95"/>
        <el-table-column label="交通工具" prop="vehicleType" width="95"/>
        <el-table-column label="班号" prop="vehicleCode" width="95"/>
        <el-table-column label="出发时间" prop="departureTime" width="95"/>
        <el-table-column label="到达时间" prop="arrivalTime" width="95"/>
        <el-table-column label="Actions" align="center" width="150">
          <template #default="scope">
            <el-button size="small" @click="handleEdit(scope.$index, scope.row)">
              Edit
            </el-button>

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
    </div>

  </div>
</template>

<script setup lang="ts">
import { useRoutesStore } from '@/stores/routeStore';
import { apiClient } from '@/utils/axios/axios';
import { useCityStore } from '@/stores/cityStore';
import { ElNotification, type FormInstance } from 'element-plus'
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
          routesStore.fetchRoutes();
          ElNotification({
            title: 'Success',
            message: '添加成功',
            type: 'success',
          })
          onReset();
          routesStore.routesCount += 1;
        })
        .catch((error) => {
          console.error('Error submitting form:', error);
          ElNotification({
            title: 'Error',
            message: '添加失败',
            type: 'error',
          })
        });

      } catch {
        ElNotification({
          title: 'Error',
          message: '添加失败',
          type: 'error',
        });
      }
    } else {
      ElNotification({
        title: 'Error',
        message: '请检查表单',
        type: 'error',
      });
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
  ElNotification({
    title: 'Success',
    message: '删除成功',
    type: 'success',
  })
};

const handleEdit = (index: number, row: Route) => {
  console.log('Edit:', index, row);
  ElNotification({
    title: 'Edit',
    message: '开发中...',
    type: 'info',
  })
};


//------------------------ Manage Route ------------------------
onMounted(async () => {
  // 设置
  if(routesStore.allRoutes.length === 0) {
    routesStore.fetchRoutes();
  }
});
</script>

<style scoped>
.shadow-inner {
  --tw-shadow: inset 0 0px 9px 0 rgb(39 27 18 / 15%);
}
</style>
