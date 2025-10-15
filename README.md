# Smart_Energy_Monitering_Meter
An IoT-based Smart Energy Monitoring Meter using ESP32, ZMPT101B voltage sensor, ACS712 current sensor, DHT11 temperature sensor, and an OLED display. The system measures voltage, current, power, temperature, and energy cost in real time, with cloud integration for remote monitoring and data visualization.

## 🧩 Features
- Real-time voltage and current measurement ⚙️  
- Power and energy consumption calculation 🔋  
- Temperature and humidity monitoring 🌡️  
- Energy cost estimation 💰  
- Cloud data visualization on ThingsBoard / Blynk / Firebase ☁️  
- Wi-Fi connectivity via ESP32 🌐  
- OLED display for instant on-device readings 📟  
- Overload and anomaly detection ⚡  



## 🛠️ Hardware Components
| Component | Description |
|------------|--------------|
| **ESP32** | Main microcontroller with Wi-Fi & Bluetooth |
| **ZMPT101B** | Voltage Sensor for AC voltage measurement |
| **ACS712 (30A)** | Current Sensor for load current measurement |
| **DHT11 / DHT22** | Temperature and Humidity Sensor |
| **0.96" OLED Display (I2C)** | For displaying real-time data |
| **Relay Module (5V)** | To control load automatically |
| **Power Supply (5V)** | To power the system |
| **Resistors, Jumpers, and PCB** | For circuit assembly |


## 🧠 Working Principle
1. The **ZMPT101B** and **ACS712** sensors measure voltage and current respectively.  
2. The **ESP32** calculates power and energy usage.  
3. **DHT11** adds environmental parameters for analysis.  
4. Data is displayed on the **OLED** and sent to the **cloud dashboard** for visualization.  
5. **Relay control** manages load based on thresholds.



## ☁️ Cloud & Connectivity
Supports:
- **ThingsBoard**
- **Blynk IoT**
- **Firebase Realtime Database**
- **MQTT-based custom dashboards**



## 📷 Images
![Smart_energy_meter](https://github.com/user-attachments/assets/5c1e82b8-dcbe-46f2-98bf-d9f5ce316b10)
![AAAABBB](https://github.com/user-attachments/assets/77c3b5f6-9157-4040-abad-1798b86df399)
![PIC223344](https://github.com/user-attachments/assets/2ab2cecd-87d6-40b7-bc8c-d335154b43e0)
![SMARTMETER](https://github.com/user-attachments/assets/ce542690-a1a5-42a5-aede-3f411ff9c987)





## 👨‍💻 Developed By
**Tushar Chand Gupta**  
Department of Electronics & Communication Engineering  
Institute of Engineering & Technology, Bundelkhand University, Jhansi
