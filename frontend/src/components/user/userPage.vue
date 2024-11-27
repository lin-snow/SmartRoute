<template>
  <div>
    <h1>Hi! Welcome to using SmartRoute ! </h1>
    <h2>Choose what you want to start.</h2>
    <div>
    <!-- 城市选择框 -->
    <el-select
      v-model="startCity"
      placeholder="请选择城市"
      filterable
      style="width: 300px"
    >
      <el-option
        v-for="city in selectableCities"
        :key="city.CityCode"
        :label="city.CityName"
        :value="city.CityCode"
      />
    </el-select>
    </div>

    <!-- 选中的城市
    <div v-if="selectedCity" style="margin-top: 16px;">
      您选择的城市代码是：<strong>{{ selectedCity }}</strong>
    </div>
  </div> -->

  <h2>choose your destination</h2>
  <div>
    <!-- 城市选择框 -->
    <el-select
      v-model="destinationCity"
      placeholder="请选择城市"
      filterable
      style="width: 300px"
    >
      <el-option
        v-for="city in selectableCities"
        :key="city.CityCode"
        :label="city.CityName"
        :value="city.CityCode"
      />
    </el-select>
    </div>
  <br>
  <el-time-picker
      v-model="value1"
      is-range
      range-separator="To"
      start-placeholder="Start time"
      end-placeholder="End time"
      format="HH:mm"
    />
  </div>
</template>

<script setup lang="ts">
import { onMounted } from 'vue'
import { useCityStore } from '@/stores/cityStore';
import { useRoutesStore } from '@/stores/routesStore';

const cityStore = useCityStore();
const routeStore = useRoutesStore();

import { ref } from 'vue'

// 从 store 中解构需要的值
const selectableCities = ref<Array<{ CityName: string; CityCode: string }>>([]);


// 定义绑定的选中值
const startCity = ref(null);
const destinationCity = ref(null);

console.log(cityStore.selectableCities);



const value1 = ref<[Date, Date]>([
  new Date(2016, 9, 10, 8, 40),
  new Date(2016, 9, 10, 9, 40),
]);

onMounted(async () => {
  await cityStore.fetchCities(); // 等待 fetchCities 执行完毕
  await routeStore.fetchRoutes(); // 等待 fetchRoutes 执行完毕

  // 确保数据已经加载完成再打印
  console.log("All Cities:", cityStore.allCities);
  console.log("All Routes:", routeStore.allRoutes);
  console.log("Selectable Cities:", cityStore.selectableCities);
  selectableCities.value = cityStore.selectableCities;
});
</script>

<style scoped>
.demo-range .el-date-editor {
  margin: 8px;
}

.demo-range .el-range-separator {
  box-sizing: content-box;
}
</style>


































