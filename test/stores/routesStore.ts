import { defineStore } from "pinia";
import { ref } from "vue";
import { apiClient } from "@/utils/axios/axios";

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

export const useRoutesStore = defineStore('allRoutes', () => {
  // State
  const allRoutes = ref<Route[]>([]);
  const loading = ref(true);

  // Actions
  const fetchRoutes = async () => {
    try {
      const response = await apiClient.get('/data/get');

      allRoutes.value = response.data.data.routes
      if (response.data.data.list.routes.length > 0) {
        console.log('Routes fetched successfully');
        loading.value = false;
      }
    } catch (error) {
      console.error(error);
    }
  }

  fetchRoutes();

  return {
    allRoutes,
    fetchRoutes
  }
})
