# 🌱 Smart Farming using IoT

In IoT-based smart farming, a system is built for monitoring the crop field with the help of sensors (light, humidity, temperature, soil moisture, etc.) and automating the irrigation system. The farmers can monitor the field conditions from anywhere.

---

## 🚀 Project Overview
- **Board:** ESP32 DevKit V1 (can also work with NodeMCU ESP8266)
- **Sensors Used:**
  - DHT11 (temperature & humidity)
  - Soil Moisture sensor
  - Optional UV/light sensor
- **Actuators:**
  - Buzzer for alerts
  - LED indicator
- **Connectivity:**
  - Wi-Fi (ESP32/NodeMCU)
  - MQTT (cloud data logging & alerts)
- **Power Saving:**
  - Deep Sleep between sensor reads to extend lifetime

---

## 📂 Repository Structure
Smart-Farming-using-IoT/
│── 18BCE2199_IoT_PROJECT.pdf # Original project documentation
│── IoT.png # Project diagram / image
│── README.md # Project description (this file)
│── diagram.json # Wokwi simulator circuit connections
│── libraries.txt # Required Arduino libraries
│── main.cpp # Main C++ source code (NodeMCU/ESP)
│── sketch.ino # Arduino sketch for ESP32
│── wokwi-project.txt # Notes for simulation setup


---

## 🛠️ Setup Instructions

### 1️⃣ Install Arduino IDE
Download and install [Arduino IDE](https://www.arduino.cc/en/software).

### 2️⃣ Install ESP Boards
Go to **File → Preferences → Additional Board Manager URLs** and add:
https://dl.espressif.com/dl/package_esp32_index.json
https://arduino.esp8266.com/stable/package_esp8266com_index.json


Then, in **Tools → Board → Boards Manager**, search for `ESP32` or `ESP8266` and install.

### 3️⃣ Install Required Libraries
In Arduino IDE:
- Go to **Sketch → Include Library → Manage Libraries**
- Install:
  - **DHT sensor library**
  - **Adafruit Unified Sensor**
  - **PubSubClient (MQTT)**

Or copy from `libraries.txt`.

### 4️⃣ Upload Code
- Open `sketch.ino` (ESP32) or `main.cpp` (NodeMCU).
- Select the correct board and COM port.
- Upload the code.

---

## 🧪 Simulate Online (No Hardware Required)
This project can be simulated in **[Wokwi](https://wokwi.com/)**.  

1. Open [https://wokwi.com](https://wokwi.com).  
2. Create a **New ESP32 Project**.  
3. Copy contents of `sketch.ino` into editor.  
4. Use `diagram.json` to add virtual DHT11, soil moisture (potentiometer), and buzzer.  
5. Run simulation (green ▶ button).  

---

## 📊 Example Output
Adafruit_MQTT.h

To program NodeMCU with Arduino IDE go to File–>Perferences–>Settings.

![a](https://github.com/Kartikay77/Resume/blob/main/Smart%20Farming%20using%20IoT/media/IoT1.png?raw=true)



 

Enter https:// arduino.esp8266.com/stable/package_esp8266com_index.json into the ‘Additional Board Manager URL’ field and click ‘Ok’.

![b](https://github.com/Kartikay77/Resume/blob/main/Smart%20Farming%20using%20IoT/media/IoT2.png?raw=true)

 

Now go to Tools > Board > Boards Manager.

![c](https://github.com/Kartikay77/Resume/blob/main/Smart%20Farming%20using%20IoT/media/IoT3.png?raw=true)


 

In Boards Manager window, Type esp in the search box, esp8266 will be listed there below. Now select the latest version of the board and click on install.

![d](https://github.com/Kartikay77/Resume/blob/main/Smart%20Farming%20using%20IoT/media/IoT4.png?raw=true)

![e](https://github.com/Kartikay77/Smart-Farming-using-IoT/blob/main/IoT.png)

When running, the ESP32 will:
- Print values to **Serial Monitor**
- Send MQTT JSON payloads like:
```json
{
  "temp_c": 27.5,
  "humidity": 62,
  "soil_pct": 48,
  "rssi": -52
}
Trigger buzzer + LED alerts if:
Soil moisture is below threshold
Temperature is too high
Humidity is too low
