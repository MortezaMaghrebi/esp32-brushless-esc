#include <ESP32Servo.h>   // Make sure to install the library: ESP32Servo by Kevin Harrington

Servo esc;

void setup() {
  Serial.begin(115200);

  // Attach ESC signal to GPIO 2 with min/max pulse width (1000–2000 µs)
  esc.attach(2, 1000, 2000);

  Serial.println("Starting ESC Calibration & Arming...");

  // Step 1: Send maximum throttle (required by many ESCs for calibration)
  Serial.println("Sending MAX throttle (2000 µs)...");
  esc.writeMicroseconds(2000);
  delay(3000); // Wait 3 seconds

  // Step 2: Send minimum throttle to complete calibration
  Serial.println("Sending MIN throttle (1000 µs)...");
  esc.writeMicroseconds(1000);
  delay(3000); // Wait for ESC to arm

  Serial.println("ESC is ready! Send a value between 0–100 (throttle percentage).");
}

void loop() {
  if (Serial.available()) {

    // Read input from Serial as throttle percentage
    String input = Serial.readStringUntil('\n');
    int throttlePercent = input.toInt();

    // Clamp percentage between 0 and 100
    if (throttlePercent < 0) throttlePercent = 0;
    if (throttlePercent > 100) throttlePercent = 100;

    // Convert percentage (0–100%) to pulse width (1000–2000 µs)
    int pulseWidth = map(throttlePercent, 0, 100, 1000, 2000);

    // Send throttle pulse to ESC
    esc.writeMicroseconds(pulseWidth);

    Serial.print("Throttle set to: ");
    Serial.println(throttlePercent);
  }
}
