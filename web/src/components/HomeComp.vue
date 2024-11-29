<template>
  <div class="w-2/5 mx-auto relative top-64">
    <div>
      <h1 class="my-2 font-mono">Welcome to <a href="/about" class="no-underline text-sky-400 font-bold italic text-lg">SmartRoute!</a> </h1>

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

  <el-radio-group v-model="vehicleType" class="my-2">
      <el-radio :label="'0'">火车</el-radio>
      <el-radio :label="'1'">飞机</el-radio>
  </el-radio-group>

  <br>
  <el-button type="primary" plain @click="queryRoutes" class="my-2" size="large">
    <p class="font-sans">GO!</p>
  </el-button>
  </div>




  </div>
</template>

<script setup lang="ts">
import { onMounted, ref } from 'vue';
import { useCityStore } from '@/stores/cityStore';
import { useUserStore } from '@/stores/userStore';
import { useRouter } from 'vue-router';

const cityStore = useCityStore();
const userStore = useUserStore();
const startCity = ref<string>('');
const destinationCity = ref<string>('');
const vehicleType = ref<string>('0');
const router = useRouter();

const queryRoutes = () => {
  userStore.fetchResult(startCity.value, destinationCity.value, vehicleType.value);
  router.push('/user');
};

onMounted(() => {
  cityStore.fetchCities();
});
</script>
