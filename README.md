# Alcohol-Based Engine Lock System

An Arduino-based system that uses an MQ-3 alcohol sensor to detect alcohol vapour. When the sensor reading reaches a configured threshold, the controller disables a motor-driven wheel setup used to represent the vehicle ignition/engine. LEDs and a buzzer indicate the system status.

## Features

- Detects alcohol vapour using an MQ-3 sensor module.
- Compares the sensor reading with a configurable threshold.
- Controls a motor demonstration setup through a relay or motor-driver input.
- Activates LED and buzzer alerts when the threshold is exceeded.
- Displays sensor readings and system status in the Serial Monitor.

## Components Required

- Arduino Uno
- MQ-3 alcohol sensor module
- Motor and wheel assembly for the demonstration
- Suitable motor driver module (recommended for controlling a DC motor)
- Active buzzer
- Red and green LEDs
- 220–330 Ω resistors for the LEDs
- Breadboard and jumper wires
- USB cable and suitable motor power supply

## Connections

| Component | Arduino connection | Notes |
|---|---|---|
| MQ-3 VCC | 5V | Confirm the voltage required by your sensor module |
| MQ-3 GND | GND | Common ground |
| MQ-3 AO | A0 | Analog sensor reading |
| Motor driver enable/control input | D8 | Use a motor driver; do not power a motor directly from an Arduino pin |
| Buzzer (+) | D7 | Use a driver transistor if the buzzer current requires it |
| Green LED (+) | D5 through a 220–330 Ω resistor | System allows motor operation |
| Red LED (+) | D6 through a 220–330 Ω resistor | Alcohol threshold detected |
| LED cathodes / module GND | GND | Common ground |

**Important:** The exact motor-driver wiring depends on the module and motor you have. Connect the motor to the motor driver's output terminals and use a suitable separate motor supply. Connect the driver's logic ground and Arduino GND together. Do not connect the motor directly to an Arduino I/O pin.

## Working Principle

1. The MQ-3 sensor produces an analog reading based on alcohol vapour around the sensor.
2. The Arduino samples and averages the sensor output.
3. If the reading is below the configured threshold, the controller allows the demonstration motor to run.
4. If the reading reaches or exceeds the threshold, the controller disables the motor output and activates the red LED and buzzer.
5. The current sensor value and system state are shown in the Serial Monitor.

The MQ-3 reading is a relative sensor value, not a calibrated alcohol concentration or blood-alcohol measurement. The threshold must be adjusted for the specific sensor module and test conditions.

## Software Setup

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Open `arduino/Alcohol_Based_Engine_Lock_System.ino`.
3. Select **Tools → Board → Arduino Uno** and choose the correct port.
4. Upload the sketch.
5. Open **Tools → Serial Monitor** and set the baud rate to **9600**.
6. Check the sensor reading and verify the motor, LEDs, and buzzer using a safe, low-voltage setup.

## Configuration

The following values are defined near the top of the sketch:

| Setting | Purpose |
|---|---|
| `ALCOHOL_THRESHOLD` | Sensor reading at which the motor is stopped |
| `WARMUP_TIME_MS` | Startup warm-up period |
| `SAMPLE_COUNT` | Number of readings averaged for each check |
| `MOTOR_ENABLE_ACTIVE_HIGH` | Selects whether the motor-driver enable input is active-high |

Start by observing the sensor's baseline reading in clean air. Set a threshold appropriate for your particular module and verify the system with controlled tests. Sensor readings can vary with warm-up time, airflow, temperature, humidity, and sensor condition.

## Project Structure

```text
Alcohol-Based-Engine-Lock-System/
├── README.md
└── arduino/
    └── Alcohol_Based_Engine_Lock_System.ino
```

## Troubleshooting

| Issue | What to check |
|---|---|
| Sensor reading remains at 0 or 1023 | Check VCC, GND, AO-to-A0 wiring, and the sensor module |
| Readings fluctuate | Allow the sensor to warm up and average multiple readings |
| Motor does not stop | Check the motor-driver enable wiring and active-high/active-low configuration |
| Motor does not run | Check the motor supply, driver wiring, and common ground |
| Buzzer does not sound | Check polarity and current requirements |
| Arduino resets when the motor starts | Use a suitable motor driver and separate motor supply; connect grounds appropriately |

## Safety

This setup is a prototype and should not be connected to a real vehicle's ignition, fuel system, or other safety-critical wiring. Use the motor-and-wheel assembly as the demonstration load. The MQ-3 sensor is not a certified breathalyser and cannot determine whether a person is fit to drive.
