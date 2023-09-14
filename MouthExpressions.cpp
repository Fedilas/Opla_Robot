#include "MouthExpressions.h"

extern MKRIoTCarrier carrier;

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