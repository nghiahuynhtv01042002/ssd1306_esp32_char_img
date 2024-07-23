## Introduction

The SSD1306 OLED display is a compact and versatile display module used in various projects to display text and graphics. This guide explains how to interface an SSD1306 OLED display with a ESP32 WITH ESP- IDF.

## Requirements

- **Hardware:**
  - Raspberry Pi 4
  - SSD1306 OLED display module
- **Software:**
  - ESP IDF
  - PYTHON (TO CREATE BITMAP)

## Hardware Setup

- **Connect the SSD1306 to the Raspberry Pi:**

   | SSD1306 Pin | ESP 32 Pin       |
   |-------------|------------------|
   | VCC         | 3.3V (Pin 1)     |
   | GND         | Ground (Pin 6)   |
   | SDA         | SDA1 (Pin 21)     |
   | SCL         | SCL1 (Pin 22)     |

## Demo
- Display char:
    - ![](char.jpg)
- Display image:
    - ![](img.jpg)





