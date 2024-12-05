import { createRouter, createWebHistory } from 'vue-router'
import HomeView from '../views/HomeView.vue'


const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      name: 'home',
      component: HomeView,
    },
    {
      path: '/about',
      name: 'about',
      component: () => import('../views/AboutView.vue'),
    },
    {
      path: '/user',
      name: 'user',
      component: () => import('../views/UserView.vue'),
    },
    {
      path: '/login',
      name: 'login',
      component: () => import('../views/AuthView.vue'),
    },
    {
      path: '/admin',
      name: 'admin',
      component: () => import('../views/AdminView.vue'),
    },
    {
      path: '/admin/city',
      name: 'adminCity',
      component: () => import('../views/CityView.vue'),
    },
    {
      path: '/admin/route',
      name: 'adminRoute',
      component: () => import('../views/RouteView.vue'),
    },
    {
      path: '/admin/city/edit/:cityCode',
      name: 'adminCityEdit',
      component: () => import('../views/CityUpdateView.vue'),
    },
    {
      path: '/admin/route/edit/:routeId',
      name: 'adminRouteEdit',
      component: () => import('../views/RouteUpdateView.vue'),
    }
  ],
})

export default router
