<template>
  <div>
    <h1>Admin Route Management!</h1>
    <h2>Routes List.</h2>


    <h2> Add Route </h2>
    <el-form
    ref="routeForm"
    :model="routeForm"
    :rules="rules"
    label-width="120px"
    class="demo-routeForm"
    :size="formSize"
    status-icon
  >

    <el-form-item label="From City Code" prop="from">
      <!-- <el-input v-model="routeForm.from" placeholder="City code of the starting city" /> -->
      <el-select
      v-model="startCity"
      placeholder="请选择城市"
      filterable
      style="width: 300px"
    >
      <el-option
        v-for="city in selectableCities"
        :key="city.CityCode"
        :label="city.CityName"
        :value="city.CityCode"
      />
    </el-select>
    </el-form-item>
    <el-form-item label="To City Code" prop="to">
      <!-- <el-input v-model="routeForm.to" placeholder="City code of the destination city" /> -->
      <el-select
      v-model="startCity"
      placeholder="请选择城市"
      filterable
      style="width: 300px"
    >
      <el-option
        v-for="city in selectableCities"
        :key="city.CityCode"
        :label="city.CityName"
        :value="city.CityCode"
      />
    </el-select>
    </el-form-item>
    <el-form-item label="Distance (m)" prop="distance">
      <el-input v-model="routeForm.distance" placeholder="In meters" />
    </el-form-item>
    <el-form-item label="Vehicle" prop="vehicle">
      <el-select v-model="routeForm.vehicle" placeholder="Select vehicle">
        <el-option
          v-for="item in vehicleOptions"
          :key="item.value"
          :label="item.label"
          :value="item.value"
        />
      </el-select>
    </el-form-item>
    <el-form-item label="Departure Time" prop="departureTime">
      <el-time-picker
      v-model="value1"
      is-range
      range-separator="To"
      start-placeholder="Start time"
      end-placeholder="End time"
      format="HH:mm"
    />

    </el-form-item>
    <!-- <el-form-item label="Arrival Time" prop="arrivalTime">
      <el-date-picker
        v-model="routeForm.arrivalTime"
        type="datetime"
        placeholder="Select arrival time"
        format="HH:mm"
      />
    </el-form-item> -->
    <el-form-item label="Cost (￥)" prop="cost">
      <el-input v-model="routeForm.cost" placeholder="Cost" />
    </el-form-item>
    <el-form-item>
      <el-button type="primary" @click="submitForm(routeForm)">Create</el-button>
      <el-button @click="resetForm(routeForm)">Reset</el-button>
    </el-form-item>
  </el-form>

    <h2> Delete Route </h2>
    <el-table
    :data="filterTableData"
    style="width: 100%"
    @selection-change="handleSelectionChange"
  >
    <el-table-column
      type="selection"
      width="55">
    </el-table-column>
    <el-table-column label="Route ID" prop="routeId" />
    <el-table-column label="From City Code" prop="from" />
    <el-table-column label="To City Code" prop="to" />
    <el-table-column label="Distance (m)" prop="distance" />
    <el-table-column label="Duration (min)" prop="duration" />
    <el-table-column label="Vehicle" prop="vehicle" />
    <el-table-column label="Departure Time" prop="departureTime" />
    <el-table-column label="Arrival Time" prop="arrivalTime" />
    <el-table-column label="Cost (￥)" prop="cost" />
    <el-table-column align="right">
      <template #header>
        <el-input v-model="search" size="small" placeholder="Type to search" />
      </template>
      <template #default="scope">
        <el-button size="small" @click="handleEdit(scope.$index, scope.row)">
          Edit
        </el-button>
        <el-button
          size="small"
          type="danger"
          @click="handleDelete(scope.row)">
          Delete
        </el-button>
      </template>
    </el-table-column>
  </el-table>
    <h2> Edit Route </h2>
  </div>
</template>

<script setup lang="ts">
import { reactive, ref } from 'vue'
import type { FormInstance, FormRules } from 'element-plus'

interface RouteForm {
  routeId: string
  from: number
  to: number
  distance: number
  vehicle: string
  departureTime: Date
  arrivalTime: Date
  cost: number
}

const formSize = ref('default')
const routeForm = reactive<RouteForm>({
  routeId: '',
  from: 0,
  to: 0,
  distance: 0,
  vehicle: '',
  departureTime: new Date(),
  arrivalTime: new Date(),
  cost: 0,
})

const vehicleOptions = ref([
  { value: 'TRAIN', label: 'TRAIN' },
  { value: 'PLAIN', label: 'PLAIN' },
])

const rules = ref<FormRules<RouteForm>>({
  routeId: [
    { required: true, message: 'Please input the route ID', trigger: 'blur' },
  ],
  from: [
    { required: true, message: 'Please input the from city code', trigger: 'blur' },
  ],
  to: [
    { required: true, message: 'Please input the to city code', trigger: 'blur' },
  ],
  distance: [
    { required: true, message: 'Please input the distance', trigger: 'blur' },
  ],
  vehicle: [
    { required: true, message: 'Please select the vehicle', trigger: 'change' },
  ],
  departureTime: [
    { required: true, message: 'Please select the departure time', trigger: 'change' },
  ],
  arrivalTime: [
    { required: true, message: 'Please select the arrival time', trigger: 'change' },
  ],
  cost: [
    { required: true, message: 'Please input the cost', trigger: 'blur' },
  ],
})

const routeFormRef = ref<FormInstance>()

const submitForm = (form: RouteForm) => {
  // Handle form submission, e.g., send data to backend
  console.log('Form submitted:', form)
}

const resetForm = (form: RouteForm) => {
  // Reset form fields
  form.routeId = ''
  form.from = 0
  form.to = 0
  form.distance = 0
  // form.duration = 0
  form.vehicle = ''
  form.departureTime = new Date()
  form.arrivalTime = new Date()
  form.cost = 0
}


// interface Route {
//   routeId: number;
//   from: number;
//   to: number;
//   distance: number;
//   duration: number;
//   vehicle: string;
//   departureTime: string;
//   arrivalTime: string;
//   cost: number;
// }

// const search = ref('')
// const selectedRows = ref<Route[]>([])

// const filterTableData = computed(() =>
//   tableData.filter(
//     (data) =>
//       !search.value ||
//       data.routeId.toString().toLowerCase().includes(search.value.toLowerCase())
//   )
// )

// const handleSelectionChange = (val: Route[]) => {
//   selectedRows.value = val
// }

// const handleEdit = (index: number, row: Route) => {
//   console.log('Editing row:', index, row)
// }

// const handleDelete = (row: Route) => {
//   // Here you should implement the logic to delete the row from the backend
//   console.log('Deleting row:', row)
//   // After deletion, you might want to remove the row from the tableData
//   const index = tableData.indexOf(row)
//   if (index !== -1) {
//     tableData.splice(index, 1)
//   }
// }

// const tableData: Route[] = [
//   {
//     routeId: 1,
//     from: 1001,
//     to: 1002,
//     distance: 120000,
//     duration: 90,
//     vehicle: 'Train',
//     departureTime: '2024-06-01 08:00',
//     arrivalTime: '2024-06-01 09:30',
//     cost: 200,
//   },
//   {
//     routeId: 2,
//     from: 1003,
//     to: 1004,
//     distance: 80000,
//     duration: 60,
//     vehicle: 'Bus',
//     departureTime: '2024-06-02 10:00',
//     arrivalTime: '2024-06-02 11:00',
//     cost: 150,
//   },
//   {
//     routeId: 3,
//     from: 1005,
//     to: 1006,
//     distance: 50000,
//     duration: 45,
//     vehicle: 'Car',
//     departureTime: '2024-06-03 12:00',
//     arrivalTime: '2024-06-03 12:45',
//     cost: 100,
//   },
//   // Add more route examples as needed
// ]
</script>
