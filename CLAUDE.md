# CLAUDE.md — STM32F103C8T6 PWM输入捕获测频

## 技术栈

- **MCU**: STM32F103C8T6（Cortex-M3, 64KB Flash, 20KB SRAM, 72MHz）
- **库**: ST 标准外设库 v3.5.0
- **构建工具**: Keil MDK uVision5 + EIDE (VSCode 插件 `cl.eide`)
- **调试器**: ST-Link (SWD)

## 目录结构

```
├── Start/           CMSIS 启动 + system_stm32f10x
├── Library/         ST 标准外设库 v3.5.0
├── System/          Delay.c/h — SysTick 延时
├── Hardwera/        自定义硬件驱动
│   ├── IC.c/h       ← TIM3 CH1 输入捕获 (PA6)
│   ├── PWM.c/h      ← TIM2 CH1 PWM 输出 (PA0)
│   └── OLED.c/h     ← OLED 显示驱动
├── User/            main.c, stm32f10x_conf.h, stm32f10x_it.c/h
└── build/Objects/Listings/
```

## 硬件引脚映射

| 引脚 | 功能 | 连接目标 |
|------|------|----------|
| PA6 | TIM3_CH1 IPU | PWM 信号输入 (捕获) |
| PA0 | TIM2_CH1 AF PP | PWM 信号输出 (1kHz) |
| PB5 | GPIO Out OD | OLED SCL |
| PB6 | GPIO Out OD | OLED SDA |

## 驱动模块

### IC (Hardwera/IC.c/h) — 输入捕获
- `IC_Init()` — TIM3 CH1 输入捕获, PSC=71, ARR=65535
  - 从模式: Reset Mode (每次上升沿复位计数器)
  - 滤波器: 0xF
- `IC_GetFreq()` — 频率 = 1,000,000 / CCR1 (Hz)

### PWM (Hardwera/PWM.c/h)
- `PWM_Init()` — TIM2 CH1 PWM 输出, Freq=1kHz
- `PWM_SetCompare1(val)` — 设置占空比

## 功能说明

PA0 输出 PWM → PA6 输入捕获测量频率。TIM3 从模式复位，每次上升沿捕获并清零计数器，通过 CCR1 计算频率。OLED 实时显示频率值。

## 编码规范
- 编码: UTF-8，注释用中文
- 禁止魔法数字

## Git 规范
```
main              ← 稳定分支
提交: feat:/fix:/docs: 格式
```

## 构建命令
```
Keil:  打开 Project.uvprojx → F7 编译 → F8 烧录
EIDE:  Ctrl+Shift+P → "EIDE: Build"
```

## 注意事项
- `USE_STDPERIPH_DRIVER` + `STM32F10X_MD` 必须定义
- 启动文件 `startup_stm32f10x_md.s`
- PWM 输出和捕获输入需飞线连接 PA0↔PA6
