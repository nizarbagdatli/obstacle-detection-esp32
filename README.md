[README_obstacle.md](https://github.com/user-attachments/files/31261811/README_obstacle.md)
# Obstacle Detection & Warning System (ESP32)

An ESP32-based obstacle detection system built on a breadboard. An infrared
obstacle sensor detects nearby objects, and the system responds with a visual
alert (LED), an audible alarm (buzzer) and a live status message on an OLED
display. I built and wired the whole system myself and worked through the
debugging step by step.

---

## What It Does

When an object comes close to the sensor, the system reacts instantly:

- **OLED display** shows `OBSTACLE!` (or `CLEAR` when nothing is detected)
- **LED** turns on as a visual warning
- **Buzzer** sounds an alarm tone

This is the detection-and-warning layer of the kind of system used in car
parking sensors and automatic emergency braking: a sensor detects an obstacle,
and the system warns through light, sound and a display. (A full auto-brake
system would also add an action layer — e.g. stopping a motor — which is a
natural next step.)

---

## Hardware

| Component | Connected to (ESP32) |
|-----------|----------------------|
| IR Obstacle Avoidance Module — OUT | GPIO 15 |
| LED (+ 220 R resistor) | GPIO 2 |
| Passive Buzzer | GPIO 4 |
| OLED 0.96" (I2C) — SDA | GPIO 21 |
| OLED 0.96" (I2C) — SCL | GPIO 22 |
| Shared power / ground | 3V3 / GND rails |

Built on a breadboard using a common ground rail so all components share the
same GND. The LED uses a current-limiting resistor. The OLED communicates over
I2C.

---

## How It Works

- The **IR obstacle sensor** emits infrared light and detects its reflection.
  When an object is close, the light bounces back and the sensor's output pin
  goes LOW ("obstacle"); otherwise it stays HIGH ("clear"). A small trim
  potentiometer on the module sets the detection range.
- The **ESP32** reads this signal on GPIO 15 every loop.
- Based on the reading, it drives the **LED** (GPIO 2), sounds the **passive
  buzzer** using `tone()` (GPIO 4), and updates the **OLED** over I2C.

---

## Software

- **Arduino / C++**
- Libraries: `Adafruit_GFX`, `Adafruit_SSD1306` (for the OLED), `Wire` (I2C)
- Sensor read with `digitalRead()`, buzzer driven with `tone()` / `noTone()`,
  display updated with the Adafruit SSD1306 library

The main sketch is in this repository.

---

## What I Learned

- Wiring a multi-component circuit on a breadboard, including a shared ground rail
- Why a current-limiting resistor is needed for an LED, and how to read resistor
  color codes
- How an IR obstacle sensor works and how to calibrate its range with the trim pot
- Driving a passive buzzer with `tone()` to generate an alarm sound
- Using I2C and the Adafruit SSD1306 library to write to an OLED display
- Debugging real hardware and software issues (sensor calibration, power,
  missing libraries) methodically until the system worked end to end

---

## Author

**Ahmet Nizar Bagdatli**
Applied Mechatronic Systems student — SRH Berlin University of Applied Sciences
GitHub: [github.com/nizarbagdatli](https://github.com/nizarbagdatli)
