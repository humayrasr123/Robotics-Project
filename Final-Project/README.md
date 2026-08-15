# Automatic Sensor-Triggered Claw

An Arduino-based robotic claw that opens automatically when an object (e.g. a hand) is detected within range, using an ultrasonic distance sensor for detection and an LED as a visual status indicator.

## How It Works

1. An **HC-SR04 ultrasonic sensor** continuously measures the distance to the nearest object in front of it.
2. If an object is detected within **15 cm**, the claw **opens** (servo moves to 60°) and the **LED turns on**.
3. If no object is within range, the claw **closes** (servo moves to 115°) and the **LED turns off**.
4. Distance readings are printed to the Serial Monitor at 9600 baud for debugging/monitoring.
5. The loop re-checks distance every 200 ms for near real-time responsiveness.

## Hardware Components

| Component | Pin | Purpose |
|---|---|---|
| Servo motor (claw) | Pin 9 | Opens/closes the claw |
| HC-SR04 Trig | Pin 10 | Sends ultrasonic pulse |
| HC-SR04 Echo | Pin 11 | Receives reflected pulse |
| LED | Pin 6 | Visual status indicator |

## Circuit Setup

- Connect the servo's signal wire to pin 9, and power/ground to the Arduino's 5V and GND (use an external power source if the servo draws significant current).
- Connect the HC-SR04's Trig to pin 10 and Echo to pin 11, with VCC to 5V and GND to ground.
- Connect the LED's anode (through a current-limiting resistor, ~220Ω) to pin 6, and cathode to GND.

## Code Overview

- `getDistance()` — Triggers the ultrasonic sensor, times the echo pulse (with a 30 ms timeout to prevent blocking indefinitely), and converts the pulse duration to distance in centimeters using the speed of sound (0.0343 cm/µs). Returns `-1` if no echo is received.
- `loop()` — Continuously polls distance, compares it against the detection threshold, and drives the servo and LED accordingly.

## Configuration

You can tune the following constants in the code:

```cpp
int openAngle = 60;       // Servo angle when claw is open
int closeAngle = 115;     // Servo angle when claw is closed
int detectDistance = 15;  // Detection threshold in cm
```

## Getting Started

1. Install the **Servo** library (bundled with the Arduino IDE by default).
2. Wire the components as described above.
3. Upload `final_project.ino` to your Arduino board.
4. Open the Serial Monitor (9600 baud) to view live distance readings.
5. Bring an object within 15 cm of the sensor to see the claw open and LED light up.

## Known Limitations / Possible Improvements

- No debouncing/smoothing on sensor readings — occasional noisy readings could cause the claw to flicker; a simple moving average could help.
- Fixed detection threshold — could be made adjustable via a potentiometer.
- No claw position feedback — the servo moves open-loop with no confirmation of actual claw position.
