import { defineStore } from "pinia";
import { ref } from "vue";
import { apiClient } from "@/utils/axios/axios";
import {  ElNotification } from "element-plus";

interface City {
  name: string;
  cityCode: string;
}


export const useCityStore = defineStore('allCitys', () => {
  // State
  const allCities = ref<City[]>([]);
  const citiesCount = ref<number>(0);
  const loading = ref(true);

  // Actions
  const fetchCities = async () => {
    try {
      const response = await apiClient.get('data/get');


      if (response.data.code == 400 || response.data.code == 401) {
        return [];
      }

      if (response.data.data === null || response.data.data.cities === null || response.data.data.cities.length === 0) {
        return [];
      }

      allCities.value = response.data.data.cities
      if (response.data.data.routes.length > 0) {
        console.log('Cities fetched successfully');
        loading.value = false;
        citiesCount.value = allCities.value.length;
      }
    } catch (error) {
      if (error instanceof Error) {
        console.error(error.message);
      }
    }
  }

  const deleteCity = async (index: number, row: City) => {
    try {
      if (!row.cityCode) return;
      await apiClient.get(`admin/city/delete?cityCode=${row.cityCode}`)
          .then(() => {
            allCities.value.splice(index, 1); // 删除成功后，删除对应的行
          })
          .catch((error) => {
            console.error(error);
          });
          ElNotification({
            title: 'Success',
            message: '删除成功',
            type: 'success',
          })
          citiesCount.value -= 1;
    } catch (error) {
      console.error(error);
      ElNotification({
        title: 'Success',
        message: '删除失败',
        type: 'success',
      })
    }
  }

  return {
    allCities,
    citiesCount,
    fetchCities,
    deleteCity
  }
})
