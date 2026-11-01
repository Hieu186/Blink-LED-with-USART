# 💡 Blink LED with USART Communication

A embedded C project for controlling LED blinking using USART communication protocol on STM32 / Microcontroller.

---

##  Project Overview
This project demonstrates how to transmit and receive data over USART to control an onboard or external LED. When specific commands are sent via Serial Terminal, the microcontroller updates the LED status accordingly.

---

##  Hardware Requirements
- **Microcontroller**: STM32F103C8T6 (Blue Pill)
- **USB-to-UART Converter**: CH340
- **Output Device**: 5mm LED
- **Resistor**: 220Ω (Current limiting)
- **Breadboard & Jumper Wires**

---

##  Software & Tools
- **IDE / Toolchain**: Keil uVision v5 
- **Serial Monitor**: Hercules 

---

*Note: LED is connected to GPIO pin with a 220Ω resistor to GND.*

---

##  How to Run
1. Clone this repository:
   ```bash
   git clone [https://github.com/Hieu186/Blink-LED-with-USART.git](https://github.com/Hieu186/Blink-LED-with-USART.git)
