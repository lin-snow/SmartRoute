<template>
  <div class="h-auto w-fit grid grid-cols-[1.5fr_3fr] gap-4 relative top-10 mx-auto">
    <!-- 左侧添加路线表单 -->
    <div class="bg-white rounded-xl shadow-lg p-4 border border-gray-200 glass-effect min-w-[400px]">
      <div class="mb-4">
        <h2 class="text-lg font-bold text-gray-800 text-center">添加线路</h2>
        <div class="w-12 h-1 bg-amber-500 mx-auto mt-1"></div>
      </div>

      <el-form
        ref="routeFormRef"
        :model="form"
        :rules="rules"
        label-width="90px"
        class="max-w-sm mx-auto"
      >
        <el-form-item label="出发点" prop="from">
          <el-select v-model="form.from" placeholder="请选择出发点" filterable>
            <el-option
              v-for="city in cityStore.allCities"
              :key="city.cityCode"
              :label="city.name"
              :value="city.cityCode"
            />
          </el-select>
        </el-form-item>

        <el-form-item label="目的地" prop="to">
          <el-select v-model="form.to" placeholder="请选择目的地" filterable>
            <el-option
              v-for="city in cityStore.allCities"
              :key="city.cityCode"
              :label="city.name"
              :value="city.cityCode"
            />
          </el-select>
        </el-form-item>

        <el-form-item label="交通工具" prop="vehicleType">
          <el-radio-group v-model="form.vehicleType">
            <el-radio :label="'0'">火车</el-radio>
            <el-radio :label="'1'">飞机</el-radio>
          </el-radio-group>
        </el-form-item>

        <el-form-item label="班号" prop="vehicleCode">
          <el-input v-model="form.vehicleCode" placeholder="输入班号" />
        </el-form-item>

        <el-form-item label="时间">
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

        <el-form-item class="flex justify-center gap-3 mt-4">
          <el-button type="primary" @click="onSubmit" class="w-24">创建</el-button>
          <el-button @click="onReset" class="w-24">重置</el-button>
        </el-form-item>
      </el-form>
    </div>

    <!-- 右侧状态和管理面板 -->
    <div class="bg-white rounded-xl shadow-lg p-4 min-w-[600px] border border-gray-200 glass-effect">
      <div class="mb-4">
        <h2 class="text-lg font-bold text-gray-800 text-center">线路状态</h2>
        <div class="w-12 h-1 bg-amber-500 mx-auto mt-1"></div>
      </div>

      <div class="grid grid-cols-2 gap-3 mb-4">
        <div class="bg-gray-50 rounded-lg p-2 text-center">
          <h3 class="text-sm font-semibold text-gray-700 mb-1">线路统计</h3>
          <div class="text-xl font-bold text-green-500">
            {{ routesStore.routesCount }}
          </div>
        </div>

        <div class="bg-gray-50 rounded-lg p-2 text-center">
          <h3 class="text-sm font-semibold text-gray-700 mb-1">运行状况</h3>
          <div v-if="routesStore.routesCount > 0" class="text-base font-bold text-green-500">
            一切正常
          </div>
          <div v-else class="text-base font-bold text-yellow-500">无线路</div>
        </div>
      </div>

      <div class="mb-4">
        <h2 class="text-lg font-bold text-gray-800 text-center">线路管理</h2>
        <div class="w-12 h-1 bg-amber-500 mx-auto mt-1"></div>
      </div>

      <el-table
        :data="routesStore.formattedAllRoutes"
        border
        style="width: 100%"
        empty-text="暂无线路数据"
        height="20rem"
        class="custom-table"
      >
        <el-table-column label="Route ID" prop="routeId" width="80" align="center" />
        <el-table-column label="出发点" prop="from" width="85" align="center" />
        <el-table-column label="目的地" prop="to" width="85" align="center" />
        <el-table-column label="距离(km)" prop="distance" width="85" align="center" />
        <el-table-column label="耗时(m)" prop="duration" width="85" align="center" />
        <el-table-column label="费用(￥)" prop="cost" width="85" align="center" />
        <el-table-column label="交通工具" prop="vehicleType" width="85" align="center" />
        <el-table-column label="班号" prop="vehicleCode" width="85" align="center" />
        <el-table-column label="出发时间" prop="departureTime" width="85" align="center" />
        <el-table-column label="到达时间" prop="arrivalTime" width="85" align="center" />
        <el-table-column label="操作" align="center" width="180">
          <template #default="scope">
            <el-button
              type="primary"
              size="small"
              plain
              class="mr-2 hover:shadow-md transition-shadow"
              @click="handleEdit(scope.$index, scope.row)"
            >
              编辑
            </el-button>
            <el-button
              type="danger"
              size="small"
              plain
              class="hover:shadow-md transition-shadow"
              @click="handleDelete(scope.$index, scope.row)"
            >
              删除
            </el-button>
          </template>
        </el-table-column>
      </el-table>

      <div class="flex justify-center mt-4">
        <el-button type="primary" plain size="large" class="shadow-md hover:shadow-lg transition-shadow">
          <el-icon class="mr-2"><AdminIcon /></el-icon>
          <router-link to="/admin">返回面板</router-link>
        </el-button>
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
import { useRouter } from 'vue-router';

const routesStore = useRoutesStore();
const cityStore = useCityStore();
const router = useRouter();

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
          if (res.data.code !== 200) {
            ElNotification({
              title: 'Error',
              message: '添加失败',
              duration: 800,
              type: 'error',
            });
            return;
          }
          routesStore.fetchRoutes();
          ElNotification({
            title: 'Success',
            message: '添加成功',
            duration: 1200,
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
            duration: 800,
            type: 'error',
          })
        });

      } catch {
        ElNotification({
          title: 'Error',
          message: '添加失败',
          duration: 800,
          type: 'error',
        });
      }
    } else {
      ElNotification({
        title: '表单错误',
        message: '请检查表单',
        duration: 800,
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
  router.push(`/admin/route/edit/${row.routeId}`);
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
.glass-effect {
  backdrop-filter: blur(10px);
  background-color: rgba(255, 255, 255, 0.9);
}

.custom-table :deep(.el-table__header-wrapper) {
  border-radius: 8px 8px 0 0;
}

.custom-table :deep(.el-table__body-wrapper) {
  border-radius: 0 0 8px 8px;
}
</style>
