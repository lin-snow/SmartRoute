import { defineStore } from "pinia";
import { ref } from "vue";
import { apiClient } from "@/utils/axios/axios";
import { watch } from "vue";

interface City {
  name: string;
  cityCode: string;
}

export const useCityStore = defineStore('allCitys', () => {
  // State
  const allCities = ref<City[]>([]);
  const selectableCities = ref<Array<{CityName: string, CityCode: string}>>([]);
  const loading = ref(true);

  // Actions
  const fetchCities = async () => {
    try {
      const response = await apiClient.get('data/get');
      console.log(response.data.data.cities);
      if (response.data.data.cities === null) {
        return [];
      }

      allCities.value = response.data.data.cities
      if (response.data.data.routes.length > 0) {
        console.log('Cities fetched successfully');
        loading.value = false;
      }
    } catch (error) {
      if (error instanceof Error) {
        console.error(error.message);
      }
    }
  }

  // construct selectableCities
  function genSelectableCities() {
    if (allCities.value != null) {
      selectableCities.value = allCities.value.map((city) => ({
        CityName: city.name,
        CityCode: city.cityCode
      }))
    } else {
      return [];
    }
  }

  fetchCities();
  watch(allCities, () => {
    genSelectableCities(); // 监听 allCities 的变化，并更新 selectableCities
    console.log("生成的 selectableCities:", selectableCities.value);
  });

  return {
    allCities,
    fetchCities,
    selectableCities,
    genSelectableCities
  }
})
