<template>
  <div class="min-h-screen bg-gradient py-8 px-4 flex justify-center items-center">
    <div class="w-full max-w-2xl bg-white rounded-xl shadow-lg p-8 border border-gray-200 glass-effect">
      <el-button
        class="mb-6"
        @click="router.push('/admin/route')"
        type="default"
        :icon="ArrowLeft"
      >
        返回线路管理
      </el-button>

      <h2 class="text-2xl font-bold text-gray-800 mb-8 text-center">编辑线路信息</h2>

      <el-form
        ref="routeFormRef"
        :model="form"
        :rules="rules"
        label-width="120px"
        class="space-y-6"
      >
        <el-form-item label="出发站点代码" prop="from">
          <!-- 输入出发点 -->
          <input type="text" v-model="form.from" disabled />

        </el-form-item>
        <el-form-item label="目标站点代码" prop="to">
          <!-- 输入目的地 -->
          <input type="text" v-model="form.to" disabled>
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
        <el-form-item class="flex justify-center gap-4 pt-6">
          <el-button
            type="primary"
            @click="onSubmit"
            class="w-32"
            :icon="Check"
          >
            保存更改
          </el-button>
          <el-button
            @click="onReset"
            class="w-32"
            :icon="RefreshLeft"
          >
            重置
          </el-button>
        </el-form-item>
      </el-form>
    </div>
  </div>
</template>

<script setup lang="ts">
import { useRoutesStore } from '@/stores/routeStore';
import { useRouter } from 'vue-router';
import { reactive, ref } from 'vue';
import { ElNotification } from 'element-plus';
import { apiClient } from '@/utils/axios/axios';
import type { FormInstance } from 'element-plus';
import { ArrowLeft, Check, RefreshLeft } from '@element-plus/icons-vue'

const router = useRouter();
const routesStore = useRoutesStore();

// 获取当前路由参数
const curRouteId = router.currentRoute.value.params.routeId;

// 获取当前线路信息
const oldRoute = routesStore.allRoutes.find((route) => route.routeId.toString() == curRouteId) || null;

// 初始化两个时间范围
const rangeTime = ref<[Date, Date]>()
// 初始化出发时间和到达时间
const departureTime = ref<string>(oldRoute ? oldRoute.departureTime : '');
const arrivalTime = ref<string>(oldRoute ? oldRoute.arrivalTime : '');

// 处理时间变化的函数
const handleTimeChange = (value: [Date, Date]) => {
  if (value) {
    departureTime.value = value[0].getHours().toString().padStart(2, '0') + ':' + value[0].getMinutes().toString().padStart(2, '0');
    arrivalTime.value = value[1].getHours().toString().padStart(2, '0') + ':' + value[1].getMinutes().toString().padStart(2, '0');
  }
};

const routeFormRef = ref<FormInstance | null>(null);
const form = reactive({
  from: oldRoute ? oldRoute.from : '', // 出发地
  to: oldRoute ? oldRoute.to : '', // 目的地
  vehicleType: oldRoute ? oldRoute.vehicleType : '', // 交通工具类型
  vehicleCode: oldRoute ? oldRoute.vehicleCode : '', // 班号
  departureTime: oldRoute ? oldRoute.departureTime : '', // 出发时间
  arrivalTime: oldRoute ? oldRoute.arrivalTime : '', // 到达时间
  cost: oldRoute ? oldRoute.cost : '', // 票价
  distance: oldRoute ? oldRoute.distance : '', // 距离
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
    if (valid && oldRoute) {
      try {
        // 将两个时间分别转成字符串
        form.departureTime = departureTime.value;
        form.arrivalTime = arrivalTime.value;
        console.log(form);
        console.log("submit")

        const formData = new FormData();
        formData.append('routeId', oldRoute.routeId.toString());
        formData.append('from', form.from.toString());
        formData.append('to', form.to.toString());
        formData.append('vehicleType', form.vehicleType.toString());
        formData.append('vehicleCode', form.vehicleCode.toString());
        formData.append('departureTime', form.departureTime);
        formData.append('arrivalTime', form.arrivalTime);
        formData.append('cost', form.cost.toString());
        formData.append('distance', form.distance.toString());

        // 提交表单
      await apiClient.put('admin/route/update', formData) // 直接发送 formData 对象
        .then((res) => {
          console.log(res);
          if (res.data.code !== 200) {
            ElNotification({
              title: 'Error',
              message: '修改失败',
              type: 'error',
            });
            return;
          }

          console.log(res);
          routesStore.fetchRoutes();
          ElNotification({
            title: 'Success',
            message: '修改成功',
            duration: 1200,
            type: 'success',
          })
          router.push('/admin/route');
        })
        .catch((error) => {
          console.error('Error submitting form:', error);
          ElNotification({
            title: 'Error',
            message: '修改失败',
            duration: 800,
            type: 'error',
          })
        });

      } catch {
        ElNotification({
          title: 'Error',
          message: '修改失败',
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
    vehicleType: '',
    vehicleCode: '',
    departureTime: '',
    arrivalTime: '',
    cost: null,
    distance: null,
  });
};

</script>

<style scoped>
.bg-gradient {
  background: linear-gradient(135deg,
    #a8edea 0%,
    #fed6e3 100%
  );
  /* 或者可以选择以下任一渐变方案：
  background: linear-gradient(120deg, #e0c3fc 0%, #8ec5fc 100%);
  background: linear-gradient(to right, #f6d365 0%, #fda085 100%);
  background: linear-gradient(120deg, #a1c4fd 0%, #c2e9fb 100%);
  */
}

.glass-effect {
  background: rgba(255, 255, 255, 0.2);
  backdrop-filter: blur(10px);
  box-shadow: 0 4px 30px rgba(0, 0, 0, 0.1);
  border: 1px solid rgba(255, 255, 255, 0.3);
  border-radius: 16px;
}

:deep(.el-form-item__label) {
  font-weight: 600;
  color: #374151;
}

:deep(.el-input__wrapper) {
  box-shadow: 0 1px 2px 0 rgba(0, 0, 0, 0.05);
}

:deep(.el-input__wrapper:hover) {
  box-shadow: 0 1px 3px 0 rgba(0, 0, 0, 0.1);
}

:deep(.el-button) {
  transition: all 0.2s;
}

:deep(.el-button:hover) {
  transform: translateY(-1px);
}

:deep(.el-radio__label) {
  color: #374151;
}

:deep(.el-time-picker) {
  width: 100%;
}
</style>
