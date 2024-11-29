<template>
  <div>
    <h1>Hi! Welcome to using SmartRoute ! </h1>
    <h2>Choose your starting point</h2>
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

  <h2>Choose your destination</h2>
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
  <el-radio-group v-model="vehicleType">
      <el-radio :label="'0'">Train</el-radio>
      <el-radio :label="'1'">Plane</el-radio>
  </el-radio-group>
  <br>
  <el-button @click="queryRoutes">Query</el-button>
  <div>
    <!-- 最快路线的表格 -->
    <h2>最快路线</h2>
    <el-table :data="formattedFastestRoute" style="width: 100%">
      <el-table-column label="路线ID" prop="routeId" />
      <el-table-column label="出发城市" prop="from" />
      <el-table-column label="到达城市" prop="to" />
      <el-table-column label="距离" prop="distance" />
      <el-table-column label="出发时间" prop="departureTime" />
      <el-table-column label="到达时间" prop="arrivalTime" />
      <el-table-column label="费用" prop="cost" />
    </el-table>

    <!-- 最经济路线的表格 -->
    <h2>最经济路线</h2>
    <el-table :data="formattedCheapestRoute" style="width: 100%">
      <el-table-column label="路线ID" prop="routeId" />
      <el-table-column label="出发城市" prop="from" />
      <el-table-column label="到达城市" prop="to" />
      <el-table-column label="距离" prop="distance" />
      <el-table-column label="出发时间" prop="departureTime" />
      <el-table-column label="到达时间" prop="arrivalTime" />
      <el-table-column label="费用" prop="cost" />
    </el-table>
  </div>
  <div>
    <h2>所有可行的方案</h2>
    <el-table
      :data="formattedTableData"
      :default-expand-all="false"
      style="width: 100%"
    >
      <el-table-column type="expand">
        <template #default="scope">
          <!-- 这里使用 scope.row.routes 来访问每个方案中的路线数组 -->
          <el-table :data="scope.row.routes" style="width: 100%">
            <el-table-column label="路线ID" prop="routeId" />
            <el-table-column label="出发城市" prop="from" />
            <el-table-column label="到达城市" prop="to" />
            <el-table-column label="距离" prop="distance" />
            <el-table-column label="出发时间" prop="departureTime" />
            <el-table-column label="到达时间" prop="arrivalTime" />
            <el-table-column label="费用" prop="cost" />
          </el-table>
        </template>
      </el-table-column>
      <!-- 这里使用 scope.row.index 来访问方案编号 -->
      <el-table-column label="方案编号" prop="index" />
    </el-table>
  </div>

  </div>
</template>

<script setup lang="ts">
import { computed, onMounted } from 'vue'
import { useCityStore } from '@/stores/cityStore';
import { useRoutesStore } from '@/stores/routesStore';
import { ref } from 'vue'
import { apiClient } from '@/utils/axios/axios';

const cityStore = useCityStore();
const routeStore = useRoutesStore();
const selectableCities = ref<Array<{ CityName: string; CityCode: string }>>([]);

// 定义绑定的选中值
const startCity = ref<string>('');
const destinationCity = ref<string>('');
const vehicleType = ref<string>('');

const allRoutesData = ref<Array<Array<Route>>>([]);
const allRoutes = ref<Array<RoutePlan>>([])
const fastestRoute = ref<Array<Route>>()
const cheapestRoute = ref<Array<Route>>()

interface RoutePlan {
  index: string;
  routes: Route[];
}

console.log(cityStore.selectableCities);



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


const queryRoutes = async () => {
  try {
    const params = {
      from: startCity.value,
      to: destinationCity.value,
      vehicleType: vehicleType.value
    };

    const res = await apiClient.get('user/query', { params }); // 直接使用 await 获取响应
    console.log(res);
    if (res.data && res.data.data) {
      fastestRoute.value = res.data.data.fastestRoute;
      cheapestRoute.value = res.data.data.economicRoute;
      allRoutesData.value = res.data.data.allRoutes;
      allRoutes.value = allRoutesData.value.map((routes, index) => ({
        index: `方案${index + 1}`,
        routes,
      }));

      // console.log("Fastest Route:", fastestRoute.value);
      // console.log("Cheapest Route:", cheapestRoute.value);
      // console.log("############@@@@@@@@@@@")
      // console.log("All Routes:", allRoutes.value);
    }
  } catch (error) {
    console.error('Error querying routes:', error);
  }
};

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

const formattedTableData = computed(() => {
  return allRoutesData.value.map((routes, index) => ({
    index: `方案${index + 1}`,
    routes: routes.map(route => ({
      ...route,
      from: formatCityName(route.from.toString()), // 转换出发城市ID为城市名
      to: formatCityName(route.to.toString()), // 转换到达城市ID为城市名
    }))
  }));
});

const formattedFastestRoute = computed(() => {
  return fastestRoute.value?.map((route: Route) => ({
    ...route,
    from: formatCityName(route.from.toString()), // 转换出发城市ID为城市名
    to: formatCityName(route.to.toString()), // 转换到达城市ID为城市名
  }));
})

const formattedCheapestRoute = computed(() => {
  return cheapestRoute.value?.map((route: Route) => ({
    ...route,
    from: formatCityName(route.from.toString()), // 转换出发城市ID为城市名
    to: formatCityName(route.to.toString()), // 转换到达城市ID为城市名
  }));
})


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


































