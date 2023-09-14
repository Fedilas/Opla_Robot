#include "Arduino_MKRIoTCarrier.h"
#include "EyeExpressions.h"
#include "MouthExpressions.h"

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

void loop() {
  // Update the carrier status
  carrier.Buttons.update();
  

  // Check if the Button 1 is being touched to show sad eyes
  if (carrier.Buttons.getTouch(TOUCH1)) {
    drawSadEyes();
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
