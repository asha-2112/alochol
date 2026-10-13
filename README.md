<div align="center">

# 🍃 Alcohol-Based Engine Lock System

### An Arduino-powered IoT safety prototype

**MQ-3 Alcohol Sensor · Arduino Uno · Relay Module · Buzzer**

![Arduino](https://img.shields.io/badge/Controller-Arduino_Uno-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Language](https://img.shields.io/badge/Code-C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Domain](https://img.shields.io/badge/Domain-IoT-orange?style=for-the-badge)
![Status](https://img.shields.io/badge/Project-Educational_Demo-blueviolet?style=for-the-badge)

*A sensor-based prototype that demonstrates how alcohol-vapour readings can trigger an alert and disable a simulated engine output.*

</div>

---

## 📌 Overview

The **Alcohol-Based Engine Lock System** is an IoT mini-project built around an **MQ-3 alcohol sensor** and an **Arduino Uno**. The sensor provides an analog reading, which the Arduino compares with a configurable threshold. When the reading reaches the threshold, the system switches a relay-controlled **low-voltage demonstration output** to the locked state and activates visual and audible alerts.

The project demonstrates the basic principles of **sensor interfacing, embedded decision logic, output control, and real-time monitoring**.

> ⚠️ **Safety notice:** This is an educational prototype, not a certified breathalyser or automotive safety device. Do not connect it to a real vehicle's ignition, fuel system, or safety-critical wiring. Use the relay only with a low-voltage demonstration load. MQ-3 readings are relative sensor values and do not measure blood-alcohol concentration or determine whether someone is fit to drive.

## ✨ Features

| Feature | Description |
|---|---|
| 🧪 Alcohol-vapour sensing | Reads the analog output of an MQ-3 sensor module. |
| 🧠 Threshold-based logic | Compares averaged sensor readings against a configurable threshold. |
| 🔒 Simulated engine lock | Switches a relay output to represent enabled/locked states. |
| 🚨 Alert indicators | Uses a buzzer and red/green LEDs to indicate system status. |
| 📟 Live monitoring | Displays sensor values and status through the Arduino Serial Monitor. |
| ⏳ Startup warm-up | Keeps the demo output locked during the configured startup period. |

## 🧰 Hardware Required

- Arduino Uno or compatible 5 V board
- MQ-3 alcohol sensor module with analog output (AO)
- 5 V relay module
- Active buzzer
- Green LED and red LED
- 220–330 Ω current-limiting resistors for LEDs
- Breadboard and jumper wires
- USB cable
- Optional low-voltage demo LED or small DC demo load

## 🔌 Wiring Guide

| Component | Arduino pin | Connection |
|---|---:|---|
| MQ-3 VCC | 5V | Sensor power (check module requirements) |
| MQ-3 GND | GND | Common ground |
| MQ-3 AO | A0 | Analog sensor signal |
| Relay module IN | D8 | Controls demo output |
| Buzzer (+) | D7 | Use a driver if required by the buzzer's current |
| Green LED (+) | D5 | Connect through a 220–330 Ω resistor |
| Red LED (+) | D6 | Connect through a 220–330 Ω resistor |
| LED cathodes / module GND | GND | Common ground |

**Important:** Relay modules differ. Confirm whether yours is active-low or active-high before powering the circuit. Never connect mains voltage or a real vehicle circuit to this project.

## ⚙️ How It Works

<div align="center">

```text
       ┌────────────────────┐
       │  MQ-3 Alcohol      │
       │  Sensor Module     │
       └─────────┬──────────┘
                 │ Analog reading
                 ▼
       ┌────────────────────┐
       │    Arduino Uno     │
       │ Average + Compare  │
       └─────────┬──────────┘
                 │
          Threshold check
            ┌────┴────┐
            ▼         ▼
      Below limit   At/above limit
            │         │
            ▼         ▼
      Demo output   Demo output
        ENABLED       LOCKED
      Green LED ON   Red LED + buzzer
</div>
```

1. **Sense:** The MQ-3 module provides an analog reading.
2. **Stabilise:** The Arduino averages multiple readings and waits through a startup warm-up period.
3. **Compare:** The averaged value is checked against `ALCOHOL_THRESHOLD`.
4. **Respond:** Below the threshold, the demo output is enabled; at or above it, the output is locked and an alert is shown.
5. **Monitor:** The Serial Monitor prints the reading, threshold, and current state.

## 💻 Getting Started

### 1. Install the Arduino IDE

Download and install the [Arduino IDE](https://www.arduino.cc/en/software).

### 2. Open the sketch

Open this file from the repository:

```text
arduino/Alcohol_Based_Engine_Lock_System.ino
```

### 3. Select your board and port

In the Arduino IDE, select **Tools → Board → Arduino Uno**, then choose the correct serial port.

### 4. Upload and monitor

Upload the sketch and open **Tools → Serial Monitor**. Set the baud rate to **9600**.

### 5. Test safely

Allow the sensor to warm up and observe its baseline in clean air. Use only a ventilated, supervised classroom setup and safe test conditions. Keep flames and concentrated flammable vapours away from the sensor.

## 🎛️ Configuration

The main settings are near the top of the Arduino sketch:

| Setting | Purpose |
|---|---|
| `ALCOHOL_THRESHOLD` | Analog reading at which the demo enters the locked state |
| `WARMUP_TIME_MS` | Startup warm-up duration |
| `SAMPLE_COUNT` | Number of samples averaged per reading |
| `RELAY_ACTIVE_LOW` | Sets relay logic for active-low or active-high modules |

### Choosing a demo threshold

1. Let the sensor stabilise according to its module documentation.
2. Observe several clean-air readings in the Serial Monitor.
3. Select a threshold above ordinary baseline variation for a classroom demonstration.
4. Verify both output states under safe, controlled conditions.

The default threshold is only a starting value; it is **not a calibrated alcohol concentration** and should not be used for real-world driving decisions.

## 🗂️ Project Structure

```text
Alcohol_Based_Engine_Lock_System/
├── README.md
├── LICENSE
├── .gitignore
├── arduino/
│   └── Alcohol_Based_Engine_Lock_System.ino
└── docs/
    └── PROJECT_OVERVIEW.md
```

## 🧪 Demonstration Checklist

- [ ] Sensor readings appear in the Serial Monitor.
- [ ] The simulated output stays locked during warm-up.
- [ ] A reading below the threshold enables the demo output.
- [ ] A reading at or above the threshold locks the demo output and activates alerts.
- [ ] Relay logic matches the actual relay module.
- [ ] The circuit is connected only to a low-voltage demo load.

## 🛠️ Troubleshooting

<details>
<summary><strong>Sensor reading stays at 0 or 1023</strong></summary>

Check the sensor's power, AO wire to A0, and common ground. Confirm that you are using the analog output pin.
</details>

<details>
<summary><strong>Sensor readings fluctuate</strong></summary>

Allow more warm-up time, keep the test environment consistent, and use multiple samples rather than adjusting the threshold from one reading.
</details>

<details>
<summary><strong>Relay works in reverse</strong></summary>

Change `RELAY_ACTIVE_LOW` to match your relay module's trigger logic.
</details>

<details>
<summary><strong>Buzzer does not sound</strong></summary>

Check polarity and wiring. If the buzzer draws more current than an Arduino pin can safely supply, use an appropriate transistor driver.
</details>

<details>
<summary><strong>Arduino resets when the relay switches</strong></summary>

Check the relay module, power arrangement, and wiring. Do not drive inductive loads directly from an Arduino I/O pin.
</details>

## 🚀 Future Improvements

- Add an LCD/OLED for local status display.
- Store timestamped readings on an SD card or send them to a monitoring dashboard.
- Add sensor fault checks and a more systematic calibration workflow.
- Build a dashboard to visualise readings and event history.
- For any real automotive application, use certified equipment and professional automotive engineering; this prototype is not suitable for that use.

## 📄 Resume-Ready Description

**Alcohol-Based Engine Lock System | IoT, Arduino, MQ-3 Sensor**

- Developed an Arduino-based alcohol-vapour detection prototype using an MQ-3 sensor.
- Implemented threshold-based control logic with relay-operated demo output, LED indicators, and buzzer alerts.
- Monitored live sensor readings and system states through the Arduino Serial Monitor.

*Keep only the points that accurately reflect the features you personally implemented and tested.*

---

<div align="center">

**Built as an educational IoT project**  
*Arduino · Sensor Interfacing · Embedded Systems · Output Control*

</div>
