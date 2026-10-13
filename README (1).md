# Alcohol-Based Engine Lock System

An Arduino-based system that uses an MQ-3 alcohol sensor to detect alcohol vapour. When the sensor reading reaches a configured threshold, the Arduino disables the relay-controlled DC motor used in the wheel demonstration, representing an engine/ignition lock. LEDs and a buzzer indicate the system status.

## Features

- Detects alcohol vapour using an MQ-3 sensor module.
- Compares the sensor reading with a configurable threshold.
- Uses a relay to switch the DC motor demonstration circuit ON or OFF.
- Activates LED and buzzer alerts when the threshold is exceeded.
- Displays sensor readings and system status in the Serial Monitor.

## Components Required

- Arduino Uno
- MQ-3 alcohol sensor module with analog output
- 5V relay module, rated for the DC motor's voltage and current
- DC motor with wheels for the demonstration
- External DC motor power supply matched to the motor's voltage and current
- Active buzzer
- Red and green LEDs
- 220–330 Ω resistors for the LEDs
- Breadboard and jumper wires
- USB cable

## Connections

| Component | Arduino / circuit connection | Notes |
|---|---|---|
| MQ-3 VCC | 5V | Confirm the voltage printed on your sensor module |
| MQ-3 GND | GND | Common ground |
| MQ-3 AO | A0 | Analog sensor reading |
| Relay module VCC | 5V | For a 5V relay module |
| Relay module GND | GND | Connect to Arduino GND |
| Relay module IN | D8 | Arduino relay-control signal |
| DC motor | Relay contacts and external motor supply | Route the motor's supply through the relay contacts; do not power the motor from an Arduino pin |
| Buzzer (+) | D7 | Use a transistor driver if the buzzer draws more current than an Arduino pin can provide |
| Green LED (+) | D5 through a 220–330 Ω resistor | Motor permitted to run |
| Red LED (+) | D6 through a 220–330 Ω resistor | Alcohol threshold detected |
| LED cathodes | GND | Connect through the circuit's common ground |

### Relay and DC motor wiring

Use the relay's **COM** and **NO** contacts so the motor is normally disconnected when the relay is not energised. Connect the motor and external supply only within the relay's DC voltage and current ratings. A DC motor can draw a high starting current, so check its stall/start current against the relay rating. Add appropriate suppression for motor-generated electrical noise, following the relay and motor module specifications.

Do not connect the motor directly to an Arduino I/O pin. Keep the motor on its own correctly rated supply. The Arduino and relay module should share ground on the control side as required by the module. Relay contact wiring is separate from the relay module's low-voltage control pins.

## Working Principle

1. The MQ-3 sensor provides an analog reading based on alcohol vapour around the sensor.
2. The Arduino samples and averages the sensor output.
3. If the reading is below the configured threshold, the relay energises and the DC motor runs.
4. If the reading reaches or exceeds the threshold, the relay de-energises, disconnecting the motor circuit; the red LED and buzzer turn on.
5. Sensor readings and the current system status appear in the Serial Monitor.

The MQ-3 reading is a relative sensor value, not a calibrated alcohol concentration or blood-alcohol measurement. Readings vary with warm-up time, airflow, temperature, humidity, and sensor condition.

## Software Setup

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Open `arduino/Alcohol_Based_Engine_Lock_System.ino`.
3. Select **Tools → Board → Arduino Uno** and choose the correct port.
4. Upload the sketch.
5. Open **Tools → Serial Monitor** and set the baud rate to **9600**.
6. Check the sensor readings and verify the relay, DC motor, LEDs, and buzzer using a low-voltage setup.

## Configuration

The following values are defined near the top of the sketch:

| Setting | Purpose |
|---|---|
| `ALCOHOL_THRESHOLD` | Sensor reading at which the motor is stopped |
| `WARMUP_TIME_MS` | Startup warm-up period |
| `SAMPLE_COUNT` | Number of readings averaged for each check |
| `RELAY_ACTIVE_LOW` | Set to `true` for an active-low relay module or `false` for an active-high module |

Start by observing the sensor's baseline reading in clean air. The code's default threshold of `400` is an initial test value only; adjust it after observing readings from your actual sensor module. It is not a calibrated alcohol concentration.

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
| Relay operates in reverse | Change `RELAY_ACTIVE_LOW` to match the relay module |
| DC motor does not run | Check the external motor supply, relay COM/NO wiring, motor condition, and relay ratings |
| DC motor does not stop | Check the relay-control signal and COM/NO contacts |
| Buzzer does not sound | Check polarity and current requirements |
| Arduino resets when the motor switches | Check power wiring and motor suppression; keep the motor on its own correctly rated supply |

## Safety

This system should not be connected to a real vehicle's ignition, fuel system, or other safety-critical wiring. Use the DC motor and wheels as the demonstration load. The MQ-3 sensor is not a certified breathalyser and cannot determine whether a person is fit to drive.
