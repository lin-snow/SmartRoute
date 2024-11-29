<template>
  <div>
    <h1>Welcome to SmartRoute! </h1>
    <p>SmartRoute is a route optimization tool that helps you plan your route efficiently. </p>

    <div>
    <!-- 城市选择框 -->
    <el-select
      v-model="startCity"
      placeholder="请选择城市"
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
  <!-- 城市选择框 -->
  <el-select
    v-model="destinationCity"
    placeholder="请选择城市"
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

  <el-radio-group v-model="vehicleType">
      <el-radio :label="'0'">Train</el-radio>
      <el-radio :label="'1'">Plane</el-radio>
  </el-radio-group>

  <br>
  <el-button @click="queryRoutes">Query</el-button>

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
