/*
 * Obstacle Detection & Warning System (ESP32)
 * -------------------------------------------
 * An IR obstacle sensor detects nearby objects. When an obstacle is
 * detected, the system reacts with:
 *   - LED on    (visual warning)
 *   - Buzzer    (audible alarm, passive buzzer via tone())
 *   - OLED      (shows "OBSTACLE!" / "CLEAR")
 *
 * Wiring:
 *   IR sensor OUT   -> GPIO 15
 *   LED (+220R)     -> GPIO 2   (long leg via resistor to GPIO2, short leg to GND)
 *   Passive buzzer  -> GPIO 4   (other leg to GND)
 *   OLED SDA        -> GPIO 21
 *   OLED SCL        -> GPIO 22
 *   OLED VCC        -> 3V3       OLED GND -> GND
 *
 * Libraries needed (install via Library Manager):
 *   - Adafruit GFX Library   (by Adafruit)
 *   - Adafruit SSD1306       (by Adafruit)
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---- Pin definitions ----
#define OBSTACLE_PIN 15   // IR sensor OUT
#define LED_PIN 2         // warning LED
#define BUZZER_PIN 4      // passive buzzer

// ---- OLED settings ----
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C    // OLED I2C address (usually 0x3C)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  pinMode(OBSTACLE_PIN, INPUT);   // sensor = input (we read it)
  pinMode(LED_PIN, OUTPUT);       // LED = output (we control it)
  // passive buzzer needs no pinMode; tone() handles it

  // Start the OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED not found! Check wiring / I2C address.");
    while (true);   // stop here if OLED is missing
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.display();

  Serial.println("Obstacle detection system started.");
}

void loop() {
  int value = digitalRead(OBSTACLE_PIN);   // read the sensor
  bool obstacle = (value == LOW);          // LOW = obstacle detected

  // Prepare the OLED
  display.clearDisplay();
  display.setCursor(0, 20);
  display.setTextSize(2);

  if (obstacle) {
    // --- Obstacle detected ---
    digitalWrite(LED_PIN, HIGH);   // LED on
    tone(BUZZER_PIN, 1000);        // buzzer alarm at 1000 Hz
    display.println("OBSTACLE!");
    Serial.println("OBSTACLE DETECTED!");
  } else {
    // --- Clear ---
    digitalWrite(LED_PIN, LOW);    // LED off
    noTone(BUZZER_PIN);            // buzzer silent
    display.println("CLEAR");
    Serial.println("clear");
  }

  display.display();   // push text to the screen
  delay(200);          // small delay between readings
}
