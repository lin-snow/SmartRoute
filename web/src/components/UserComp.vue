<template>
  <div class="mx-auto min-w-fit mt-12">
    <div class="grid grid-cols-2 gap-8 w-fit mx-auto">
      <div class="border-2 border-double border-amber-700 rounded-lg p-4 shadow-lg text-center bg-white">
        <h2 class="font-mono font-bold text-xl mb-4 text-amber-800">所有可行的方案</h2>
        <el-table
          :data="userStore.formatedAllRoutes"
          :default-expand-all="false"
          style="width: 100%"
          class="route-table"
        >
          <el-table-column type="expand">
            <template #default="scope">
              <!-- 这里使用 scope.row.routes 来访问每个方案中的路线数组 -->
              <el-table :data="scope.row.routes" border style="width: 100%">
                <el-table-column label="路线ID" prop="routeId" width="70" />
                <el-table-column label="出发城市" prop="from" width="100" />
                <el-table-column label="到达城市" prop="to" width="100" />
                <el-table-column label="距离(km)" prop="distance" width="100" />
                <el-table-column label="出发时间" prop="departureTime" width="115" />
                <el-table-column label="到达时间" prop="arrivalTime" width="115" />
                <el-table-column label="费用" prop="cost" width="105" />
              </el-table>
            </template>
          </el-table-column>
          <!-- 这里使用 scope.row.index 来访问方案编号 -->
          <el-table-column label="方案编号" prop="index" />
        </el-table>
      </div>

      <div class="shadow-lg bg-white border-2 border-double rounded-lg border-amber-700 p-4">
        <div class="flex justify-center mb-6">
          <el-button type="primary" plain size="large" class="w-36 shadow-md hover:shadow-lg transition-shadow">
            <el-icon class="mr-2"><homeIcon /></el-icon>
            <router-link to="/">返回首页</router-link>
          </el-button>
        </div>
        <div class="space-y-6">
          <div class="route-section">
            <h2 class="font-bold font-mono text-lg text-amber-800 mb-3">最快路线</h2>
            <el-table :data="userStore.formatedFastestRoute" border style="width: 100%" class="route-table">
              <el-table-column label="路线ID" prop="routeId" width="70" />
              <el-table-column label="出发城市" prop="from" width="100" />
              <el-table-column label="到达城市" prop="to" width="100" />
              <el-table-column label="距离(km)" prop="distance" width="88" />
              <el-table-column label="出发时间" prop="departureTime" width="100" />
              <el-table-column label="到达时间" prop="arrivalTime" width="100" />
              <el-table-column label="费用" prop="cost" width="100" />
            </el-table>
          </div>

          <div class="route-section">
            <h2 class="font-bold font-mono text-lg text-amber-800 mb-3">最经济路线</h2>
            <el-table :data="userStore.formatedEconomicRoute" border style="width: 100%" class="route-table">
              <el-table-column label="路线ID" prop="routeId" width="70" />
              <el-table-column label="出发城市" prop="from" width="100" />
              <el-table-column label="到达城市" prop="to" width="100" />
              <el-table-column label="距离(km)" prop="distance" width="88" />
              <el-table-column label="出发时间" prop="departureTime" width="100" />
              <el-table-column label="到达时间" prop="arrivalTime" width="100" />
              <el-table-column label="费用" prop="cost" width="100" />
            </el-table>
          </div>

          <div class="route-section">
            <h2 class="font-bold font-mono text-lg text-amber-800 mb-3">最少换乘路线</h2>
            <el-table :data="userStore.formatedTransferRoute" border style="width: 100%" class="route-table">
              <el-table-column label="路线ID" prop="routeId" width="70" />
              <el-table-column label="出发城市" prop="from" width="100" />
              <el-table-column label="到达城市" prop="to" width="100" />
              <el-table-column label="距离(km)" prop="distance" width="88" />
              <el-table-column label="出发时间" prop="departureTime" width="100" />
              <el-table-column label="到达时间" prop="arrivalTime" width="100" />
              <el-table-column label="费用" prop="cost" width="100" />
            </el-table>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
import { useUserStore } from '@/stores/userStore'
import { ElNotification } from 'element-plus'
import { onMounted } from 'vue'

const userStore = useUserStore()

onMounted(() => {
  ElNotification({
    title: '查找成功！',
    message: '已经为您找到所有可行的方案',
    type: 'success',
    duration: 1000,
  })

  userStore.clearRawData()
})
</script>

<style scoped>
.route-section {
  @apply p-4 border border-gray-200 rounded-md bg-gray-50;
}

.route-table :deep(.el-table__header) {
  @apply bg-amber-50;
}

.route-table :deep(.el-table__row:hover) {
  @apply bg-amber-50/50;
}
</style>
