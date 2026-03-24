---

# 🌡️ Smart HVAC Control System using ATmega32

A microcontroller-based **HVAC monitoring system** that performs real-time sensing of temperature and humidity, with automated control of cooling and alerts. Gas sensing using MQ-2 was implemented and validated **independently**.

---

## 📌 Overview

This project demonstrates a **smart HVAC control system** using the ATmega32 microcontroller. It monitors environmental conditions and responds automatically to maintain comfort and safety.

### ✅ Core Functionalities

* 🌡️ Temperature monitoring & fan control
* 💧 Humidity monitoring & alert system
* 🔥 Gas detection (tested separately using MQ-2)
* 📟 Real-time LCD display

---

## 🎯 Control Logic

* **Temperature ≥ 27°C → Fan ON**

* **Temperature < 27°C → Fan OFF**

* **Humidity ≥ 70% → Alert LED ON**

* **Humidity < 70% → LED OFF**

---

## 🧠 System Architecture

```text
Main System:
DHT11 → ATmega32 → LCD + Fan + LED

Independent Testing:
MQ-2 → ATmega32 (ADC Validation Only)
```

---

## 🔧 Hardware Components

* ATmega32 Microcontroller
* DHT11 Temperature & Humidity Sensor
* MQ-2 Gas Sensor *(independent testing)*
* 16×2 LCD Display
* DC Fan / Motor
* LEDs (Alert Indicators)
* L7805 Voltage Regulator
* Breadboard & Jumper Wires
* ISP Programmer (USBasp)
* 12V Power Supply

---

## ⚙️ Working Principle

### 🌡️ Temperature Monitoring

The DHT11 sensor continuously measures temperature.

* Fan activates automatically when temperature reaches **27°C or higher**

### 💧 Humidity Monitoring

* LED turns ON when humidity exceeds **70%**
* Ensures quick visual indication of high humidity levels

### 📟 LCD Display

* Displays real-time:

  * Temperature
  * Humidity

---

## 🔥 MQ-2 Gas Sensor (Independent Module)

The MQ-2 sensor was **implemented and tested separately** and is **not included in the final circuit diagram**.

### 🧪 Testing Summary

* Clean air → Low output
* Gas exposure → High ADC values
* Fast response observed

### 📌 Notes

* Requires calibration for accurate thresholds
* Needs warm-up time before stable readings
* Suitable for future integration into HVAC system

---

## 🔌 Pin Configuration

| Component | Pin        |
| --------- | ---------- |
| DHT11     | PB0        |
| MQ-2      | PA0 (ADC0) |
| LCD       | PORTD      |
| Fan       | PC0        |
| LED       | PC1        |

---

## 🧪 Testing & Results

* ✔️ Stable temperature readings
* ✔️ Accurate humidity alert at 70%
* ✔️ Reliable fan switching at 27°C
* ✔️ Smooth LCD operation
* ✔️ MQ-2 showed clear gas sensitivity (independent test)

  <img width="900" height="595" alt="image" src="https://github.com/user-attachments/assets/d7b52918-c902-4105-90c0-9d8a492b12bc" />
  <img width="900" height="462" alt="image" src="https://github.com/user-attachments/assets/afba1655-d0f3-4a81-95ce-0ee98fc88972" />

  


---

## 🚀 Future Improvements

* Integrate MQ-2 into main system for air quality control
* Add PID-based smart HVAC control
* IoT-based remote monitoring
* Multi-zone HVAC expansion

---

## 👩‍💻 Authors

* Muzna Kamal (23K-6002)
FAST National University, Karachi
