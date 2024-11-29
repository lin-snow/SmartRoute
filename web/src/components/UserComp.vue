<template>

  <div class="mx-auto absolute top-1/4 left-1/4 ">
    <div class="grid grid-cols-2 gap-4 w-fit mx-auto ">
        <div class=" border-2 border-double border-amber-700 rounded-md p-1 shadow-md">
          <h2 class="font-mono font-bold">所有可行的方案</h2>
          <el-table
            :data="userStore.formatedAllRoutes"
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
                  <el-table-column label="距离(km)" prop="distance" />
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

        <div class="shadow-md w-fit border-2 border-double rounded-md border-amber-700 p-1 my-2">
          <div>
          <!-- 返回首页 -->
          <el-button
            type="primary"
            plain
            class="my-2 mr-1"
          >
            <span>
              <el-icon class="mr-1"><homeIcon /></el-icon>
            </span>
            <router-link to="/" class="mr-2">返回首页</router-link>
          </el-button>

        </div>

          <div class="border-b-2 border-gray-600 border-t-2">
            <!-- 最快路线的表格 -->
            <h2 class="font-bold font-mono">最快路线</h2>
            <el-table :data="userStore.formatedFastestRoute" style="width: 100%">
              <el-table-column label="路线ID" prop="routeId" />
              <el-table-column label="出发城市" prop="from" />
              <el-table-column label="到达城市" prop="to" />
              <el-table-column label="距离(km)" prop="distance" />
              <el-table-column label="出发时间" prop="departureTime" />
              <el-table-column label="到达时间" prop="arrivalTime" />
              <el-table-column label="费用" prop="cost" />
            </el-table>
        </div>

        <div>
        <!-- 最经济路线的表格 -->
            <h2 class="font-bold font-mono">最经济路线</h2>
            <el-table :data="userStore.formatedEconomicRoute" style="width: 100%">
              <el-table-column label="路线ID" prop="routeId" />
              <el-table-column label="出发城市" prop="from" />
              <el-table-column label="到达城市" prop="to" />
              <el-table-column label="距离(km)" prop="distance" />
              <el-table-column label="出发时间" prop="departureTime" />
              <el-table-column label="到达时间" prop="arrivalTime" />
              <el-table-column label="费用" prop="cost" />
            </el-table>
        </div>



        </div>
      </div>
  </div>

</template>

<script setup lang="ts">
import { useUserStore } from '@/stores/userStore';

const userStore = useUserStore();

</script>
