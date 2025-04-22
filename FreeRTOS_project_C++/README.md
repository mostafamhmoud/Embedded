# STM32 FreeRTOS Embedded System (C++)

This project demonstrates how to build a modular and scalable embedded system for STM32 microcontrollers using **FreeRTOS** and **modern C++ concepts**.

The application includes:
- A UART command-line interface (CLI)
- LED effects controlled via FreeRTOS software timers
- Real-Time Clock (RTC) configuration and display
- Task-based architecture using object-oriented design

---

## 📦 Project Structure

| File / Folder         | Description                                                 |
|-----------------------|-------------------------------------------------------------|
| `main.cpp`            | Entry point; initializes hardware and starts tasks          |
| `TaskHandler.cpp`     | Contains C++ classes for FreeRTOS tasks (Menu, LED, RTC, etc.) |
| `FreeRTOS_Timer.cpp`  | C++ wrapper class around FreeRTOS software timers           |
| `Queue_Wrapper.hpp`   | Queue abstraction                      |
| `shared_resources.hpp`| Shared global state between tasks (e.g., system state enum) |

---

## 🧠 Key Concepts Demonstrated

### ✅ Modern C++ in Embedded Systems
- **Encapsulation** via task classes (e.g., `LedTask`, `MenuTask`, `RTCTask`)
- **Dynamic and static task allocation**
- Use of `reinterpret_cast` and proper type-safety for FreeRTOS API
- Object-oriented wrapper over C-style FreeRTOS constructs (timers, tasks)

### ✅ FreeRTOS Concepts
- Task creation and scheduling
- Task notification (`xTaskNotifyWait`, `xTaskNotifyFromISR`)
- Software timers (`xTimerCreate`, `xTimerStart`, and callback handlers)
- Message queues for UART communication

---

## ⚙️ Features

### 🧭 UART Command Parser
- Handles user input and routes commands to the right task
- Commands:
  - `'0'` → LED effect menu
  - `'1'` → RTC menu
  - `'2'` → (Exit)

### 💡 LED Effect System
- Effects triggered by typed commands: `e1`, `e2`, `e3`, `e4`
- `none` command stops all effects
- Uses **FreeRTOS software timers** to toggle LEDs periodically

### 🕰️ RTC Configuration
- User can configure:
  - Time (`Hour`, `Minute`, `Second`)
  - Date (`Day`, `Month`, `Year`)
- Time and Date are displayed using UART
- Input is parsed and validated before applying

---

## 🚀 Getting Started

### 🛠️ Requirements
- STM32F4 or compatible MCU
- STM32CubeIDE or compatible toolchain
- FreeRTOS included via STM32CubeMX
- UART (USART2) and RTC initialized in `main.cpp`

### 🧪 How to Use
1. Flash the project to your board
2. Open a serial terminal (115200 baud)
3. Interact using the command-line menu

---

## 💻 Example Serial Interaction

