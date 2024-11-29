import { defineStore } from "pinia";
import { ref } from "vue";
import { apiClient } from "@/utils/axios/axios";
import { useUserStore } from "./userStore";
import { useCityStore } from "./cityStore";
import { ElMessage } from "element-plus";

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

interface FormattedRoute {
  routeId: number;
  from: string;
  to: string;
  distance: number;
  duration: number;
  vehicleType: number;
  vehicleCode: string;
  departureTime: string;
  arrivalTime: string;
  cost: number;
}

const cityStore = useCityStore();
const userStore = useUserStore();

export const useRoutesStore = defineStore('allRoutes', () => {
  // State
  const allRoutes = ref<Route[]>([]);
  const formattedAllRoutes = ref<FormattedRoute[]>([]);

  const loading = ref(true);

  // Actions
  const fetchRoutes = async () => {
    try {
      const response = await apiClient.get('data/get');

      allRoutes.value = response.data.data.routes
      if (allRoutes.value.length > 0) {
        console.log('Routes fetched successfully');
        loading.value = false;
      }

      cityStore.fetchCities();
      formattedAllRoutes.value = formatAllRoutes();

    } catch (error) {
      console.error(error);
    }
  }

  const formatAllRoutes = () => {
    if (allRoutes.value.length > 0) {
      return allRoutes.value
        .slice() // 创建副本，避免直接修改原数组
        .sort((a, b) => b.routeId - a.routeId) // 按 routeId 降序排列
        .map((route) => {
            const fromCity = userStore.formatCityName(route.from.toString());
            const toCity = userStore.formatCityName(route.to.toString());

            return {
                ...route,
                from: fromCity,
                to: toCity,
            };
        });
    } else {
      return [];
    }
  }

  const deleteRoute = async (index: number, row: Route) => {
    try {
      if (!row.routeId) return;
      // 将from和to转成对应的cityCode
      const fromCity = cityStore.allCities.find(city => city.name == row.from.toString());
      const toCity = cityStore.allCities.find(city => city.name == row.to.toString());

      // 构建查询参数
      const params = {
        routeId: row.routeId,
        from: fromCity ? fromCity.name : '',
        to: toCity ? toCity.cityCode : ''
      };

      // 发送带有查询参数的 GET 请求
      const response = await apiClient.get(`admin/route/delete`, { params });

      if (response.status === 200) {
        allRoutes.value.splice(index, 1); // 删除成功后，删除对应的行
        ElMessage.success('删除成功');
      } else {
        console.error(response);
        ElMessage.error('删除失败');
      }
    } catch (error) {
      console.error(error);
      ElMessage.error('删除失败');
    }
  }

  fetchRoutes();

  return {
    allRoutes,
    formattedAllRoutes,
    fetchRoutes,
    deleteRoute,
    formatAllRoutes
  }
})
