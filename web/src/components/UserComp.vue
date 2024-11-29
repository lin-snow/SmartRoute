<template>
  <div>
    <h1>These are all plans for you </h1>

    <el-container>
      <el-aside>
        <h2>All Plans</h2>
        <h2>所有可行的方案</h2>
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
      </el-aside>
      <el-aside>
        <!-- 最快路线的表格 -->
      <h2>最快路线</h2>
      <el-table :data="userStore.formatedFastestRoute" style="width: 100%">
        <el-table-column label="路线ID" prop="routeId" />
        <el-table-column label="出发城市" prop="from" />
        <el-table-column label="到达城市" prop="to" />
        <el-table-column label="距离(km)" prop="distance" />
        <el-table-column label="出发时间" prop="departureTime" />
        <el-table-column label="到达时间" prop="arrivalTime" />
        <el-table-column label="费用" prop="cost" />
      </el-table>

      <!-- 最经济路线的表格 -->
      <h2>最经济路线</h2>
      <el-table :data="userStore.formatedEconomicRoute" style="width: 100%">
        <el-table-column label="路线ID" prop="routeId" />
        <el-table-column label="出发城市" prop="from" />
        <el-table-column label="到达城市" prop="to" />
        <el-table-column label="距离(km)" prop="distance" />
        <el-table-column label="出发时间" prop="departureTime" />
        <el-table-column label="到达时间" prop="arrivalTime" />
        <el-table-column label="费用" prop="cost" />
      </el-table>
      </el-aside>
    </el-container>

  </div>
</template>

<script setup lang="ts">
import { useUserStore } from '@/stores/userStore';

const userStore = useUserStore();

</script>
