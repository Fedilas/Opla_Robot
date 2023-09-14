#include <Arduino_MKRIoTCarrier.h>

MKRIoTCarrier carrier;
bool gestureDetected = false;
unsigned long lastGestureTime = 0;
unsigned long lastActionTime = 0;

void setup() {
  CARRIER_CASE = true;
  carrier.begin();
  carrier.display.fillScreen(ST77XX_WHITE);
  drawNormalEyes();

  // Initialize last action time
  lastActionTime = millis();
}

void drawNormalEyes() {
  carrier.display.fillScreen(ST77XX_WHITE);
  
  // Whites of the eyes
  carrier.display.fillCircle(180, 140, 50, ST77XX_BLACK);
  carrier.display.fillCircle(70, 140, 50, ST77XX_BLACK);
  
  // irises
  carrier.display.fillCircle(180 + random(-5, 5), 140 + random(-5, 5), 30, ST77XX_BLACK);  // Random movement for lifelike appearance
  carrier.display.fillCircle(70 + random(-5, 5), 140 + random(-5, 5), 30, ST77XX_BLACK);

  // Black pupils
  carrier.display.fillCircle(180 + random(-5, 5), 140 + random(-5, 5), 15, ST77XX_BLACK);
  carrier.display.fillCircle(70 + random(-5, 5), 140 + random(-5, 5), 15, ST77XX_BLACK);
  
//  // Shiny white reflections (jelly bean shaped)
//  carrier.display.fillRoundRect(193, 128, 12, 6, 3, ST77XX_WHITE);
//  carrier.display.fillRoundRect(83, 128, 12, 6, 3, ST77XX_WHITE);
}

void drawHalfMoonEyes() {
  carrier.display.fillScreen(ST77XX_WHITE);

  // Base black circles for the eyes
  carrier.display.fillCircle(180, 140, 50, ST77XX_BLACK);
  carrier.display.fillCircle(70, 140, 50, ST77XX_BLACK);

  // White circles overlaying the top half of the black circles
  carrier.display.fillCircle(180, 110, 50, ST77XX_WHITE); // The Y-coordinate is moved up
  carrier.display.fillCircle(70, 110, 50, ST77XX_WHITE);  // The Y-coordinate is moved up
}

void blinkEyes() {
  carrier.display.fillScreen(ST77XX_WHITE);
  delay(150);
  drawNormalEyes();
  delay(150);
  carrier.display.fillScreen(ST77XX_WHITE);
  delay(150);
  drawNormalEyes();
}

void drawSleepyEyes() {
  carrier.display.fillScreen(ST77XX_WHITE);
  carrier.display.fillCircle(180, 130, 50, ST77XX_BLACK);  // Raised a bit to make eyes sleepy
  carrier.display.fillCircle(70, 130, 50, ST77XX_BLACK);
}

void loop() {
  if (carrier.Light.gestureAvailable()) {
    uint8_t gesture = carrier.Light.readGesture();

    if (gesture == UP && !gestureDetected) {
      drawHalfMoonEyes();
      gestureDetected = true;
      lastGestureTime = millis();
      delay(1000);
    }
  }

  if (gestureDetected && (millis() - lastGestureTime > 5000)) {
    gestureDetected = false;
    drawNormalEyes();
  }

  // Randomly blink eyes twice at intervals between 5 to 15 seconds
  if (random(5000, 15000) < (millis() - lastActionTime)) {
    blinkEyes();
    lastActionTime = millis();
  }

  // If there's no action for more than 20 seconds, make eyes appear sleepy
  if (millis() - lastActionTime > 20000) {
    drawSleepyEyes();
    delay(3000);  // Hold the sleepy eyes for 3 seconds
    drawNormalEyes();
    lastActionTime = millis();
  }

  // Occasional lifelike movement of pupils
  if (random(0, 100) > 95) { // 5% chance every loop iteration
    drawNormalEyes();
    delay(300); // Hold the position for a bit before next loop iteration
  }
  delay(100);
}