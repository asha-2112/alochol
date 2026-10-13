# Alcohol-Based Engine Lock System
### IoT Mini Project | Arduino Uno + MQ-3 Alcohol Sensor

An educational prototype that detects alcohol vapour near an MQ-3 sensor and blocks a **simulated engine/ load** when the sensor reading exceeds a configurable threshold. It demonstrates how an alcohol-sensing input can control an output, provide an alert, and display system status.

> **Safety note:** This is a classroom prototype, not a certified breathalyser or vehicle safety device. **Do not connect this circuit to a real vehicle's ignition, fuel system, or other safety-critical wiring.** Use the relay only with a low-voltage demonstration load (for example, an LED or small DC demo motor within the module's ratings). Sensor readings are affected by warm-up, calibration, temperature, humidity, and vapour concentration; this project cannot determine a person's blood-alcohol concentration or driving fitness.

## Features
- Reads alcohol-sensor output from the MQ-3 module.
- Compares the reading against a configurable threshold.
- Simulates an engine lock using a relay output.
- Sounds a buzzer when the reading is above the threshold.
- Uses serial-monitor output for live readings and status.
- Includes a startup warm-up period and simple averaging to reduce noisy readings.

## Hardware
- Arduino Uno (or compatible 5 V board)
- MQ-3 alcohol sensor module with analog output (AO)
- 5 V relay module (for low-voltage demo load only)
- Active buzzer
- Green LED and red LED, each with a suitable current-limiting resistor (typically 220–330 Ω)
- Breadboard and jumper wires
- USB cable
- Optional: low-voltage demo LED/load to represent the “engine”

## Wiring

| Component | Arduino connection | Notes |
|---|---|---|
| MQ-3 VCC | 5V | Confirm your module's voltage requirements |
| MQ-3 GND | GND | Common ground |
| MQ-3 AO | A0 | Analog sensor output |
| Relay module IN | D8 | Relay controls only a low-voltage demo load |
| Buzzer (+) | D7 | Use a driver transistor if required by your buzzer's current |
| Green LED (+) | D5 through 220–330 Ω resistor | “Demo engine enabled” indicator |
| Red LED (+) | D6 through 220–330 Ω resistor | “Alcohol threshold exceeded” indicator |
| LEDs / buzzer / relay GND | GND | Common ground |

Connect each LED's cathode to GND. Follow the pin labels on your specific modules. Never connect mains voltage or vehicle ignition wiring to this prototype.

## How it works
1. The sensor is powered and allowed to warm up.
2. The Arduino takes several analog readings and averages them.
3. If the averaged value is below the configured threshold, the green LED turns on and the relay is placed in the demo “enabled” state.
4. If the value reaches or exceeds the threshold, the relay is placed in the demo “locked” state, the red LED turns on, and the buzzer sounds.
5. Sensor values and status are printed to the Serial Monitor.

The MQ-3 output is an **uncalibrated relative reading**, not a BAC value. The default threshold is only a starting point for a controlled classroom demonstration.

## Software setup
1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Open `arduino/Alcohol_Based_Engine_Lock_System.ino`.
3. Select **Tools → Board → Arduino Uno** (or your compatible board) and the correct port.
4. Upload the sketch.
5. Open **Tools → Serial Monitor** and set the baud rate to **9600**.
6. Allow the sensor to warm up and observe readings in clean air before testing. Use only a safe, supervised demonstration setup and never expose the sensor to open flames or concentrated flammable vapours.

## Configuration
At the top of the sketch:
- `ALCOHOL_THRESHOLD`: the analog reading at which the demo locks.
- `WARMUP_TIME_MS`: startup warm-up time.
- `SAMPLE_COUNT`: number of samples averaged per reading.
- `RELAY_ACTIVE_LOW`: set `true` for common active-low relay modules, or `false` for active-high modules.

### Calibrating the demo threshold
1. Power the sensor in a ventilated area and let it stabilise according to the module documentation.
2. Record the clean-air readings in the Serial Monitor.
3. Choose a threshold above normal baseline variation for a **demonstration only**.
4. Verify both states using safe, controlled test conditions. Do not use this procedure to certify a device for driving or to infer alcohol concentration.

## Repository structure
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

## Troubleshooting
- **Reading stays at 0 or 1023:** check AO wiring, module power, common ground, and whether the selected pin is analog output.
- **Reading drifts:** allow more warm-up time, keep airflow consistent, and avoid changing the threshold based on a single sample.
- **Relay state is reversed:** change `RELAY_ACTIVE_LOW` to match your relay module.
- **Buzzer does not sound:** check polarity and current requirements; use a transistor driver for a buzzer that draws more current than an Arduino pin can safely provide.
- **Board resets when relay switches:** use a suitable relay module and power arrangement; avoid powering inductive loads directly from the Arduino.

## Limitations and future improvements
- Add an LCD/OLED for local status display.
- Log timestamped readings to an SD card or a dashboard.
- Add a calibration procedure and sensor fault detection.
- Use a certified automotive-grade system and professional integration for any real vehicle application; this hobby prototype is not suitable for that role.

## Resume description
**Alcohol-Based Engine Lock System | IoT, Arduino, MQ-3 Sensor**
- Built an Arduino-based alcohol-vapour detection prototype using an MQ-3 sensor.
- Implemented threshold-based decision logic with relay-controlled demo output, LED indicators, and buzzer alerts.
- Monitored sensor readings through the Serial Monitor and tuned the threshold for a controlled demonstration.

Only include features you actually built or tested when describing the project on your resume.
