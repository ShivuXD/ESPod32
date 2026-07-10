# ESPod32 - ESP32 Wireless Media Controller

ESPod32 is a custom ESP32-based wireless media controller with a live OLED display.  
An external music controller that can control media playback on a computer while showing the currently playing track, artist, and progress in real time.

The project combines Bluetooth HID controls, Wi-Fi communication, an OLED interface, and a Windows companion application.

---

## Features

- Play / Pause control
- Next and previous track buttons
- Volume control (on hold)
- Forward and backward controls
- Song title display
- Artist Name display
- Playback Progress Bar
- Works with media sources supported by Windows Media Session:
  - Apple Music
  - Spotify
  - YouTube
  - Browser players
  - Other supported media applications
---

## Working

ESPod32 uses 2 communication channels.

### Media Control

The ESP32 behaves like a Bluetooth keyboard.

```
Physical Buttons
       |
       v
     ESP32
       |
       v
 Bluetooth HID
       |
       v
 Windows Media Controls
```

### Live Display 

A Python application reads the currently playing media from Windows and sends the information back to ESP32.

```
Spotify / Apple Music / YouTube
              |
              v
 Windows Media Session API
              |
              v
 Python Companion App
              |
              v
            Wi-Fi
              |
              v
            ESP32
              |
              v
          OLED Display
```

---

# Hardware 

- ESP32 
- SSD1306 128x64 OLED Display (I2C)
- 5 Push Buttons
- Breadboard
- Jumper wires

---

# Circuit Connections

## OLED Display

| OLED Pin | ESP32 Pin |
|---|---|
| GND | GND |
| VCC | 3.3V |
| SCL | GPIO22 |
| SDA | GPIO21 |

---

## Button Connections

All buttons use:

```
INPUT_PULLUP
```

My Configuration:

| Button | Function | ESP32 GPIO |
|---|---|---|
| Left Red | Previous Track | GPIO19 |
| Left Green | Volume Down / Seek Back | GPIO18 |
| Black Center | Play / Pause | GPIO5 |
| Right Green | Volume Up / Seek Forward | GPIO17 |
| Right Red | Next Track | GPIO16 |

---

# ESP32 Setup

## Required Arduino Libraries

Install following libraries from Arduino IDE Library Manager:

```
ESP32 BLE Keyboard

Adafruit SSD1306

Adafruit GFX Library

ArduinoJson
```

---

## Board Settings

Arduino IDE:

```
Board:
ESP32 Dev Module
```

And:

```
Tools
 |
 Partition Scheme
 |
 Huge APP (3MB No OTA)
```

---

## WiFi Configuration

Inside ESPod_V2.ino:

Edit:

```cpp
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";
```

to your WiFi details.

---

## Create Python Environment

Open main.py

```bash
cd ESPod32-main
```

Create the virtual environment:

```bash
python -m venv .venv
```

Windows:

```bash
.venv\Scripts\activate
```

---

## Install Dependencies

```bash
pip install winsdk requests
```

---

# Final System

```
          ESPod32

       OLED Display
            ^
            |
           WiFi

Windows Companion App

            ^

Spotify / Apple Music


ESP32 Buttons

            |

       Bluetooth HID

            |

       Windows Controls
```

---

Live media information using WiFi and Windows companion app.
