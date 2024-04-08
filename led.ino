#include <Adafruit_NeoPixel.h>

#define LED_PIN 6
#define NUM_LEDS 30

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(80);
}

void loop() {
  colorWipe(strip.Color(255, 0, 0), 50);  // 红色呼吸灯效果
  colorWipe(strip.Color(0, 255, 0), 50);  // 绿色呼吸灯效果
  theaterChase(strip.Color(0, 0, 255), 50);  // 彩虹色跑马灯效果
  rainbow(20);  // 彩虹渐变效果
  theaterChaseRainbow(50);  // 彩虹色跑马灯效果
}

// 线性渐变效果
void colorWipe(uint32_t color, int delayTime) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(delayTime);
  }
}

// 跑马灯效果
void theaterChase(uint32_t color, int delayTime) {
  for (int j = 0; j < 10; j++) {
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, color);
      }
      strip.show();

      delay(delayTime);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);
      }
    }
  }
}

// 彩虹渐变效果
void rainbow(int delayTime) {
  int numPixels = strip.numPixels();
  for (int j = 0; j < 256; j++) {
    for (int i = 0; i < numPixels; i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(delayTime);
  }
}

// 彩虹色跑马灯效果
void theaterChaseRainbow(int delayTime) {
  for (int j = 0; j < 256; j++) {
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel((i + j) % 255));
      }
      strip.show();

      delay(delayTime);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);
      }
    }
  }
}

// 将颜色值映射到彩虹色
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}