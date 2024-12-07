<template>
  <div class="w-2/5 mx-auto relative top-64">
    <div>
      <h1 class="my-2 font-mono">
        Welcome to
        <a href="/about" class="no-underline text-sky-400 font-bold italic text-xl">SmartRoute!</a>
      </h1>

      <div class="--el-box-shadow-lighter">
        <!-- 城市选择框 -->
        <el-select
          v-model="startCity"
          placeholder="请选择出发点"
          filterable
          style="width: 300px"
          class="mb-2 rounded-md"
        >
          <el-option
            v-for="city in cityStore.allCities"
            :key="city.cityCode"
            :label="city.name"
            :value="city.cityCode"
          />
        </el-select>
      </div>

      <div>
        <!-- 城市选择框 -->
        <el-select
          v-model="destinationCity"
          placeholder="请选择目的地"
          filterable
          style="width: 300px"
        >
          <el-option
            v-for="city in cityStore.allCities"
            :key="city.cityCode"
            :label="city.name"
            :value="city.cityCode"
          />
        </el-select>
      </div>
      <div>
        <span class="font-light text-sm text-gray-500"> 选择出行工具：</span>
        <el-radio-group v-model="vehicleType" class="my-2">
          <el-radio :value="'0'">火车</el-radio>
          <el-radio :value="'1'">飞机</el-radio>
        </el-radio-group>
      </div>

      <br />
      <el-button type="primary" plain @click="queryRoutes" class="my-2 w-28" size="large">
        <p class="font-sans">GO!</p>
      </el-button>
    </div>
  </div>
</template>

<script setup lang="ts">
import { onMounted, ref } from 'vue'
import { useCityStore } from '@/stores/cityStore'
import { useUserStore } from '@/stores/userStore'
import { useRouter } from 'vue-router'
import { ElNotification } from 'element-plus'

const cityStore = useCityStore()
const userStore = useUserStore()
const startCity = ref<string>('')
const destinationCity = ref<string>('')
const vehicleType = ref<string>('0')
const router = useRouter()

const queryRoutes = async () => {
  ElNotification({
    title: '查询中',
    message: '查询中',
    type: 'info',
    duration: 1000,
  })

  await userStore.fetchResult(startCity.value, destinationCity.value, vehicleType.value)

  if (
    userStore.allRoutes === null ||
    userStore.allRoutes.length === 0 ||
    userStore.loading === true
  ) {
    ElNotification({
      title: '暂无线路',
      message: '暂无线路',
      type: 'warning',
      duration: 2000,
    })
    return
  }

  router.push('/user')
}

onMounted(() => {
  cityStore.fetchCities()
  userStore.loading = true
})
</script>
