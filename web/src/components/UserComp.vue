<template>
  <div class="mx-auto min-w-fit mt-8">
    <div class="grid grid-cols-2 gap-6 w-fit mx-auto">
      <div class="border-2 border-double border-amber-700 rounded-md p-1 shadow-md text-center">
        <h2 class="font-mono font-bold my-2">所有可行的方案</h2>
        <el-table
          :data="userStore.formatedAllRoutes"
          :default-expand-all="false"
          style="width: 100%"
        >
          <el-table-column type="expand">
            <template #default="scope">
              <!-- 这里使用 scope.row.routes 来访问每个方案中的路线数组 -->
              <el-table :data="scope.row.routes" border style="width: 100%">
                <el-table-column label="路线ID" prop="routeId" width="70" />
                <el-table-column label="出发城市" prop="from" width="100" />
                <el-table-column label="到达城市" prop="to" width="100" />
                <el-table-column label="距离(km)" prop="distance" width="88" />
                <el-table-column label="出发时间" prop="departureTime" width="100" />
                <el-table-column label="到达时间" prop="arrivalTime" width="100" />
                <el-table-column label="费用" prop="cost" width="100" />
              </el-table>
            </template>
          </el-table-column>
          <!-- 这里使用 scope.row.index 来访问方案编号 -->
          <el-table-column label="方案编号" prop="index" />
        </el-table>
      </div>

      <div class="shadow-md w-fit border-2 border-double rounded-md border-amber-700 p-1">
        <div class="mx-auto ml-32 mb-2">
          <!-- 返回首页 -->
          <el-button type="primary" plain size="large" class="mx-auto my-2 w-36 shadow">
            <span>
              <el-icon class="mr-1"><homeIcon /></el-icon>
            </span>
            <router-link to="/" class="mr-2">返回首页</router-link>
          </el-button>
        </div>
        <div class="border-b-2 border-gray-600 text-center border-t-2 border-dashed">
          <!-- 最快路线的表格 -->
          <h2 class="font-bold font-mono">最快路线</h2>
          <el-table :data="userStore.formatedFastestRoute" border style="width: 100%">
            <el-table-column label="路线ID" prop="routeId" width="70" />
            <el-table-column label="出发城市" prop="from" width="100" />
            <el-table-column label="到达城市" prop="to" width="100" />
            <el-table-column label="距离(km)" prop="distance" width="88" />
            <el-table-column label="出发时间" prop="departureTime" width="100" />
            <el-table-column label="到达时间" prop="arrivalTime" width="100" />
            <el-table-column label="费用" prop="cost" width="100" />
          </el-table>
        </div>

        <div class="text-center border-b-2 border-gray-600 border-dashed">
          <!-- 最经济路线的表格 -->
          <h2 class="font-bold font-mono">最经济路线</h2>
          <el-table :data="userStore.formatedEconomicRoute" border style="width: 100%">
            <el-table-column label="路线ID" prop="routeId" width="70" />
            <el-table-column label="出发城市" prop="from" width="100" />
            <el-table-column label="到达城市" prop="to" width="100" />
            <el-table-column label="距离(km)" prop="distance" width="88" />
            <el-table-column label="出发时间" prop="departureTime" width="100" />
            <el-table-column label="到达时间" prop="arrivalTime" width="100" />
            <el-table-column label="费用" prop="cost" width="100" />
          </el-table>
        </div>

        <div class="text-center">
          <!-- 最少换乘路线 -->
          <h2 class="font-bold font-mono text-center">最少换乘路线</h2>
          <el-table :data="userStore.formatedTransferRoute" border style="width: 100%">
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
