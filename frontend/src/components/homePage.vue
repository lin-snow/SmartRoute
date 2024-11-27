<template>
  <div>
    <h1>Welcome to SmartRoute! </h1>
    <p>Click on the buttons below to navigate to the user or admin page.</p>
    <button @click="goToUser">User</button>

    <button @click="goToAdmin">Admin</button>
  </div>
</template>

<script setup lang="ts">
import { useRouter } from 'vue-router';

const router = useRouter();

const goToUser = () => {
  router.push('/user');
};

const goToAdmin = () => {
  router.push('/admin');
};
</script>
