import { defineStore } from "pinia";
import { ref } from "vue";
import { apiClient } from "@/axios/axios";

interface City {
  name: string;
  cityCode: string;
}

export const useCityStore = defineStore('allCitys', () => {
  // State
  const allCities = ref<City[]>([]);
  const loading = ref(true);

  // Actions
  const  fetchCities = async () => {
    try {
      const response = await apiClient.get('/data/get');

      allCities.value = response.data.data.list
      if (response.data.data.list.length > 0) {
        console.log('Cities fetched successfully');
        loading.value = false;
      }
    } catch (error) {
      console.error(error);
    }
  }

  fetchCities();

  return {
    allCities,
    fetchCities
  }
})
