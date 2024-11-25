import axios from 'axios'

const apiClient = axios.create({
  baseURL: 'http://0.0.0.0:23333/',
  timeout: 10000, // 10 seconds
})

apiClient.interceptors.request.use(
  (config) => {
    // Dynamically set the Content-Type header
    if (config.data) {
      if (config.data instanceof FormData) {
        config.headers['Content-Type'] = 'multipart/form-data'
      } else if (typeof config.data === 'string') {
        config.headers['Content-Type'] = 'application/x-www-form-urlencoded'
      } else {
        config.headers['Content-Type'] = 'application/json'
      }
    }

    return config
  },
  (error) => Promise.reject(error)
)

// Response interceptor for API calls
apiClient.interceptors.response.use(
  (Response) => Response,
  (error) => {
    // handler the error
    console.log('Response error:', error)
    return Promise.reject(error)
  }
)

// Export the API client
export { apiClient }
