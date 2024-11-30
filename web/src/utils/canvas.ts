
import confetti from 'canvas-confetti';

const duration = 3 * 1000; // 持续 3 秒
const end = Date.now() + duration;

export function frame() {
  // 在屏幕左上角喷发
  confetti({
    particleCount: 10, // 增加每次喷发的礼花粒子数量
    angle: 45, // 从左上角水平喷发
    spread: 180, // 扩散范围
    origin: { x: 0.05, y: 0.15 }, // 左上角位置
  });

  // 在屏幕右上角喷发
  confetti({
    particleCount: 10, // 增加每次喷发的礼花粒子数量
    angle: 135, // 从右上角水平喷发
    spread: 180, // 扩散范围
    origin: { x: 1, y: 0.15 }, // 右上角位置
  });

  // 控制喷发的时间
  if (Date.now() < end) {
    requestAnimationFrame(frame);
  }
};
