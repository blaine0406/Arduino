#include <Wire.h>
#include <Adafruit_MCP9808.h>
#include "ssd1306.h"

// Initialize MCP9808 Temperature Sensor
Adafruit_MCP9808 tempsensor;

void setup() {
  Serial.begin(9600);

  // Initialize MCP9808 Sensor
  if (!tempsensor.begin(0x18)) { // Default I2C address for MCP9808
    Serial.println("Couldn't find MCP9808!");
    while (1); 
  }
  Serial.println("MCP9808 Initialized.");

  // Initialize SSD1306 OLED Display
  ssd1306_128x64_i2c_init(); // Initialize OLED with I2C at 128x64 resolution
  ssd1306_clearScreen(); // Clear initial display

  // Set font for labels
  ssd1306_setFixedFont(ssd1306xled_font6x8);

  // Draw static title and labels
  ssd1306_printFixed(0, 0, "Chris's Temp Sensor", STYLE_BOLD); // Draw the title once
  ssd1306_printFixed(0, 16, "Temp:", STYLE_NORMAL); // Label for Celsius
  ssd1306_printFixed(64, 16, "C", STYLE_NORMAL);    // Unit for Celsius
  ssd1306_printFixed(0, 32, "Temp:", STYLE_NORMAL); // Label for Fahrenheit
  ssd1306_printFixed(64, 32, "F", STYLE_NORMAL);    // Unit for Fahrenheit
}

void loop() {
  // Read temperature in Celsius from MCP9808
  float tempC = tempsensor.readTempC();
  int tempCInt = (int)tempC; 
  int tempFInt = (int)(tempC * 9 / 5 + 32); 

  // Debugging: Print temperatures to Serial Monitor
  Serial.print("Temperature in Celsius: ");
  Serial.print(tempC);
  Serial.println(" °C");

  Serial.print("Temperature in Fahrenheit: ");
  Serial.print(tempFInt);
  Serial.println(" °F");

  // Clear and redraw only the number areas
  ssd1306_setColor(0); // Set drawing color to black (clear)
  ssd1306_fillRect(40, 16, 60, 23); // Clear the numeric area for Celsius
  ssd1306_fillRect(40, 32, 60, 39); // Clear the numeric area for Fahrenheit
  ssd1306_setColor(1); // Set drawing color back to white (text)

  // Display Celsius number
  char buffer[8];
  snprintf(buffer, sizeof(buffer), "%d", tempCInt);
  ssd1306_printFixed(40, 16, buffer, STYLE_NORMAL);

  // Display Fahrenheit number
  snprintf(buffer, sizeof(buffer), "%d", tempFInt);
  ssd1306_printFixed(40, 32, buffer, STYLE_NORMAL);

  delay(1000); // Update every second
}

