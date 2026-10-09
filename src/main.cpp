#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define VOLTAGE_PIN A0

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const float REFERENCE_VOLTAGE = 5.0;
const float DIVIDER_RATIO = 2.8;

void setup() {
  analogReference(DEFAULT);
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true) {
    }
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.display();
}

void loop() {
  const int samples = 20;
  long adcSum = 0;

  for (int i = 0; i < samples; i++) {
    adcSum += analogRead(VOLTAGE_PIN);
    delay(2);
  }

  float adcAverage = adcSum / (float)samples;
  float pinVoltage = adcAverage * REFERENCE_VOLTAGE / 1023.0;
  float inputVoltage = pinVoltage * DIVIDER_RATIO;

  if (inputVoltage < 0.03) {
    inputVoltage = 0.0;
  }

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("DIY DIGITAL VOLTMETER");

  display.drawLine(0, 12, 127, 12, SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(0, 25);
  display.print(inputVoltage, 2);
  display.println(" V");

  display.setTextSize(1);
  display.setCursor(0, 52);
  display.println("DC Voltage");

  display.display();

  delay(100);
}