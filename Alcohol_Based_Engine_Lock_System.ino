/*
  Alcohol-Based Engine Lock System
  Arduino Uno + MQ-3 alcohol sensor + relay + DC motor/wheels.

  Relay contacts switch the DC motor's separate power circuit.
  Never connect the motor directly to an Arduino I/O pin.
*/

const int ALCOHOL_SENSOR_PIN = A0;
const int RELAY_PIN          = 8;
const int BUZZER_PIN         = 7;
const int GREEN_LED_PIN      = 5;
const int RED_LED_PIN        = 6;

// Initial test value only. Tune using readings from your actual sensor.
const int ALCOHOL_THRESHOLD = 400;
const unsigned long WARMUP_TIME_MS = 30000UL;
const int SAMPLE_COUNT = 10;

// Set true for common active-low relay modules; false for active-high.
const bool RELAY_ACTIVE_LOW = true;

unsigned long startupTime = 0;
bool warmupComplete = false;

void setMotorEnabled(bool enabled) {
  // Relay energised = motor circuit connected when using COM + NO.
  // The relay module's input logic may be active-low or active-high.
  bool relayPinHigh;
  if (RELAY_ACTIVE_LOW) {
    relayPinHigh = !enabled;
  } else {
    relayPinHigh = enabled;
  }
  digitalWrite(RELAY_PIN, relayPinHigh ? HIGH : LOW);
}

int readAveragedSensor() {
  long total = 0;
  for (int i = 0; i < SAMPLE_COUNT; i++) {
    total += analogRead(ALCOHOL_SENSOR_PIN);
    delay(20);
  }
  return (int)(total / SAMPLE_COUNT);
}

void showMotorStopped() {
  setMotorEnabled(false);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(BUZZER_PIN, HIGH);
}

void showMotorAllowed() {
  setMotorEnabled(true);
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(ALCOHOL_SENSOR_PIN, INPUT);

  // Keep motor stopped during startup and sensor warm-up.
  setMotorEnabled(false);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, HIGH);

  Serial.begin(9600);
  startupTime = millis();

  Serial.println(F("Alcohol-Based Engine Lock System"));
  Serial.println(F("Relay + DC motor/wheels demonstration"));
  Serial.println(F("Sensor warming up; motor remains stopped."));
}

void loop() {
  int sensorValue = readAveragedSensor();

  if (!warmupComplete) {
    unsigned long elapsed = millis() - startupTime;

    if (elapsed < WARMUP_TIME_MS) {
      setMotorEnabled(false);
      digitalWrite(GREEN_LED_PIN, LOW);
      digitalWrite(RED_LED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, LOW);

      Serial.print(F("WARMING UP | elapsed_ms="));
      Serial.print(elapsed);
      Serial.print(F(" | sensor="));
      Serial.println(sensorValue);

      delay(200);
      return;
    }

    warmupComplete = true;
    Serial.println(F("Warm-up complete. Monitoring started."));
  }

  Serial.print(F("Sensor reading: "));
  Serial.print(sensorValue);
  Serial.print(F(" | Threshold: "));
  Serial.print(ALCOHOL_THRESHOLD);

  if (sensorValue >= ALCOHOL_THRESHOLD) {
    showMotorStopped();
    Serial.println(F(" | STATUS: MOTOR STOPPED - threshold reached"));
  } else {
    showMotorAllowed();
    Serial.println(F(" | STATUS: MOTOR RUNNING - below threshold"));
  }

  delay(100);
}
