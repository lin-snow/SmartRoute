import { ref } from 'vue'
import { useCityStore } from './cityStore'
import { useRoutesStore } from './routeStore'
import { DataSet, Network } from 'vis-network/standalone/umd/vis-network.min.js'
import { defineStore } from 'pinia'

export const useMapStore = defineStore('mapStore', () => {
  // 数据存储
  const nodes = ref(new DataSet<{ id: string; label: string }>())
  const edges = ref(
    new DataSet<{
      id: string
      from: string
      to: string
      vehicleType?: string
      vehicleCode?: string
      departureTime?: string
      arrivalTime?: string
      price?: string
      label?: string
      font?: { size: number; color: string; align: string }
      color?: { color: string }
    }>(),
  )
  const container = ref<HTMLElement | null>(null)
  // 配置选项
  const options = {
    autoResize: true, // 自动调整大小
    nodes: {
      shape: 'circle', // 更圆形的节点
      size: 110, // 节点大小
      font: {
        size: 28,
        color: '#ffffff',
        face: 'arial',
      },
      borderWidth: 1, // 边框宽度
      borderWidthSelected: 1, // 被选中时的边框宽度
      color: {
        background: '#9bc3ee', // 节点背景色
        border: 'rgb(102.2, 177.4, 255)', // 边框颜色
        highlight: {
          background: 'rgb(50.8, 116.6, 184.5)', // 被高亮时的背景色
          border: 'rgb(42, 89, 137.5)', // 被高亮时的边框色
        },
      },
      shadow: true, // 启用阴影
    },
    edges: {
      width: 2,
      color: {
        color: '#848484', // 默认边颜色
        highlight: 'rgb(247, 137.4, 137.4)', // 被高亮时的边颜色
        hover: 'rgb(247, 137.4, 137.4)', // 鼠标悬停时的边颜色
      },
      arrows: {
        to: { scaleFactor: 1.5, enabled: true, type: 'arrow' },
      },
      smooth: {
        enabled: true,
        type: 'dynamic',
        forceDirection: 'none',
        roundness: 0.2,
      },
    },
    physics: {
      enabled: true, // 启用物理引擎
      solver: 'forceAtlas2Based', // 使用基于力的布局
      forceAtlas2Based: {
        gravitationalConstant: -400, // 设置节点之间的吸引力，负值使节点靠近
        centralGravity: 0.01, // 中心引力的强度
        springLength: 260, // 节点之间的默认距离
        springConstant: 0.02, // 弹簧常数
      },
    },
    interaction: {
      hover: true, // 启用 hover 交互
      tooltipDelay: 200, // 工具提示延迟
    },
    layout: {
      randomSeed: 2, // 随机布局种子
    },
  }

  const network = ref<Network | null>(null)
  const loading = ref(true)

  // 地图生成函数
  const genMap = async (networkContainerId: string) => {
    try {


        const cityStore = useCityStore()
        const routeStore = useRoutesStore()

        // 等待城市和路线数据加载完成
        await cityStore.fetchCities()
        await routeStore.fetchRoutes()

        // 添加城市到节点
        cityStore.allCities.forEach((city) => {
          nodes.value.add({
            id: city.cityCode,
            label: city.name,
          })
        })

        if (routeStore.allRoutes.length > 0) {
          // 添加路线到边
          routeStore.allRoutes.forEach((route) => {
            const edgeColor =
              route.vehicleType === 0
                ? 'rgb(235, 180.6, 99)'
                : route.vehicleType === 1
                  ? '#0088cc'
                  : 'rgb(24.4, 33.8, 43.5)' // 根据 vehicleType 设置边的颜色

            edges.value.add({
              id: `${route.routeId.toString()}`,
              from: route.from.toString(),
              to: route.to.toString(),
              vehicleType: route.vehicleType.toString(),
              vehicleCode: route.vehicleCode.toString(),
              departureTime: route.departureTime.toString(),
              arrivalTime: route.arrivalTime.toString(),
              price: route.cost.toString(),

              label: `${route.vehicleCode} (${route.vehicleType})`, // 显示动车号和交通方式
              font: {
                size: 24,
                color: '#333', // 标签颜色
                align: 'top',
              },
              color: {
                color: edgeColor, // 根据 vehicleType 设置边的颜色
              },
            })
          })
        }

        // console.log("Nodes:", nodes.value);
        // console.log("Edges:", edges.value);

        // 获取容器
        container.value = document.getElementById(networkContainerId) as HTMLElement

        // 确保容器存在
        if (!container.value) {
          throw new Error(`Container with ID "${networkContainerId}" not found.`)
        }

        // 初始化网络
        network.value = new Network(
          container.value,
          { nodes: nodes.value, edges: edges.value },
          options,
        )
        loading.value = false

        console.log('Map generated successfully')

    } catch (error) {
      console.error('Failed to generate map:', error)
      loading.value = false
    }
  }


  return {
    nodes,
    edges,
    network,
    loading,
    genMap,
  }
})
