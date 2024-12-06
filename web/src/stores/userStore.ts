import { defineStore } from "pinia";
import { ref } from "vue";
import { apiClient } from "@/utils/axios/axios";
import { useCityStore } from "./cityStore";



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

interface RoutePlan {
  index: string;
  routes: Route[];
}


export const useUserStore = defineStore('queryResult', () => {
  // State
  // 响应的数据
  const allRoutesData = ref<Array<Array<Route>>>([]);
  const allRoutes = ref<Array<RoutePlan>>([])
  const fastestRoute = ref<Array<Route>>([])
  const economicRoute = ref<Array<Route>>([])
  const transferRoute = ref<Array<Route>>([])
  // 格式化后的数据 (用于展示)
  const formatedAllRoutes = ref()
  const formatedFastestRoute = ref()
  const formatedEconomicRoute = ref()
  const formatedTransferRoute = ref()

  const loading = ref(true);
  const cityStore = useCityStore();

  // get请求的query参数
  const queryParam = ref({
    from: '',
    to: '',
    vehicleType: '',
  })

  // Actions
  const fetchResult = async (from: string, to: string, vehicleType: string) => {
    try {
      queryParam.value.from = from;
      queryParam.value.to = to;
      queryParam.value.vehicleType = vehicleType;

      const response = await apiClient.get('user/query', {
        params: queryParam.value
      });

      if (response.data.code != 200) {
        console.log("Fetch result failed!");
        return [];
      }

      allRoutesData.value = response.data.data.allRoutes;
      fastestRoute.value = response.data.data.fastestRoute;
      economicRoute.value = response.data.data.economicRoute;
      transferRoute.value = response.data.data.transferRoute;

      // 再封装allRoutes
      allRoutes.value = allRoutesData.value.map((routes, index) => ({
        index: `方案${index + 1} ( 总费用 ${routes.reduce((acc, route) => acc + route.cost, 0)} ￥ - 总时间 ${routes.reduce((acc, route) => acc + route.duration, 0)} min - 中转次数 ${routes.length - 1} 次 ) `,
        routes,
      }));

      console.log("Fetch result successfully!");

      loading.value = false;

      formatData();

      console.log("Format data successfully!");

    } catch (error) {
      console.error(error);
    }
  }

  // 格式化数据
  const formatCityName = (cityCode: string) => {
    const city = cityStore.allCities.find(city => city.cityCode == cityCode);

    if (!city) {
      console.log("City not found!");
    }

    return city ? city.name : 'Unknown';
  }

  const formatData = () => {
    // 格式化allRoutes （将from和to转换为城市名）
    formatedAllRoutes.value = allRoutes.value.map((routePlan) => ({
      index: routePlan.index,
      routes: routePlan.routes.map((route) => ({
        ...route,
        from: formatCityName(route.from.toString()),
        to: formatCityName(route.to.toString()),
      }))
    }));

    // 格式化fastestRoute （将from和to转换为城市名）
    formatedFastestRoute.value = fastestRoute.value.map((route) => ({
      ...route,
      from: formatCityName(route.from.toString()),
      to: formatCityName(route.to.toString()),

    }));

    // 格式化economicRoute （将from和to转换为城市名）
    formatedEconomicRoute.value = economicRoute.value.map((route) => ({
      ...route,
      from: formatCityName(route.from.toString()),
      to: formatCityName(route.to.toString()),
    }));

    // 格式化transferRoute （将from和to转换为城市名）
    formatedTransferRoute.value = transferRoute.value.map((route) => ({
      ...route,
      from: formatCityName(route.from.toString()),
      to: formatCityName(route.to.toString()),
    }));
  }

  const clearRawData = () => {
    loading.value = true;
  }

  return {
    allRoutes,
    fastestRoute,
    economicRoute,
    transferRoute,
    formatedAllRoutes,
    formatedFastestRoute,
    formatedEconomicRoute,
    formatedTransferRoute,
    loading,
    queryParam,
    fetchResult,
    formatData,
    formatCityName,
    clearRawData,
  }
})
