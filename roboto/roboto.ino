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

void drawHeartEyes() {
  carrier.display.fillScreen(ST77XX_WHITE);

  // Drawing the left heart flipped vertically
  carrier.display.fillCircle(60, 160, 20, ST77XX_RED);
  carrier.display.fillCircle(90, 160, 20, ST77XX_RED);
  carrier.display.fillTriangle(40, 165, 75, 120, 110, 165, ST77XX_RED);

  // Drawing the right heart flipped vertically
  carrier.display.fillCircle(170, 160, 20, ST77XX_RED);
  carrier.display.fillCircle(200, 160, 20, ST77XX_RED);
  carrier.display.fillTriangle(150, 165, 185, 120, 220, 165, ST77XX_RED);
}

void drawArc(int16_t x, int16_t y, int16_t r, int16_t startAngle, int16_t endAngle, uint16_t color) {
  for (int i = startAngle; i < endAngle; i++) {
    int16_t newX = x + r * cos(i * (PI / 180.0));
    int16_t newY = y + r * sin(i * (PI / 180.0));
    carrier.display.drawPixel(newX, newY, color);
  }
}

void drawHappyMouth() {
  // Parameters: x, y, radius, start angle, end angle, color
  drawArc(80, 50, 50, 0, 100, ST77XX_RED);
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
}

void drawHalfMoonEyes() {
  carrier.display.fillScreen(ST77XX_WHITE);

  // Base black circles for the eyes
  carrier.display.fillCircle(180, 140, 50, ST77XX_BLACK);
  carrier.display.fillCircle(70, 140, 50, ST77XX_BLACK);

  // White circles overlaying the top half of the black circles
  carrier.display.fillCircle(180, 110, 50, ST77XX_WHITE);  // The Y-coordinate is moved up
  carrier.display.fillCircle(70, 110, 50, ST77XX_WHITE);   // The Y-coordinate is moved up
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

void drawSadEyes() {
  carrier.display.fillScreen(ST77XX_WHITE);

  // Base black circles for the eyes
  carrier.display.fillCircle(70, 140, 50, ST77XX_BLACK);
  carrier.display.fillCircle(180, 140, 50, ST77XX_BLACK);

  // White overlay to make the upper part of the eye flat
  carrier.display.fillRect(20, 90, 100, 50, ST77XX_WHITE);   // For the left eye
  carrier.display.fillRect(130, 90, 100, 50, ST77XX_WHITE);  // For the right eye
}


void drawSleepyEyes() {
  carrier.display.fillScreen(ST77XX_WHITE);
  carrier.display.fillCircle(180, 130, 50, ST77XX_BLACK);  // Raised a bit to make eyes sleepy
  carrier.display.fillCircle(70, 130, 50, ST77XX_BLACK);
}

void loop() {
  // Update the carrier status
  carrier.Buttons.update();
  

  // Check if the Button 1 is being touched to show sad eyes
  if (carrier.Buttons.getTouch(TOUCH1)) {
    drawSadEyes();
    drawHappyMouth();
    lastActionTime = millis();  // Reset the last action time
    
  }

  // Check if button 0 is being touched
  if (carrier.Buttons.getTouch(TOUCH0)) {
    drawHeartEyes();
    delay(3000);                // Hold the heart eyes for 3 seconds
    drawNormalEyes();           // then revert back to normal eyes
    lastActionTime = millis();  // Reset the last action time
  }

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
  if (random(0, 100) > 95) {  // 5% chance every loop iteration
    drawNormalEyes();
    delay(300);  // Hold the position for a bit before next loop iteration
  }
  delay(50);
}
