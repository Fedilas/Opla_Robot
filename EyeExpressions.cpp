#include "EyeExpressions.h"

extern MKRIoTCarrier carrier;

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
