<template>
  <div>
    <h1>Route Update</h1>
    <p>Current RouteId : {{ curRouteId }}</p>

    <p>From: {{ curRoute?.from }}</p>
    <p>To: {{ curRoute?.to }}</p>

  </div>
</template>

<script setup lang="ts">
import { useRoutesStore } from '@/stores/routeStore';
import { useRouter } from 'vue-router';
import { ref } from 'vue';

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

const router = useRouter();
const routeStore = useRoutesStore();
const curRoute = ref<Route | null>(null);

// 获取当前路由参数
const curRouteId = router.currentRoute.value.params.routeId;

curRoute.value = routeStore.allRoutes.find((route) => route.routeId.toString() == curRouteId) || null;

</script>
