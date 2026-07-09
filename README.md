# ESPod32 - ESP32 Wireless Media Controller

ESPod32 is a custom ESP32-based wireless media controller with a live OLED display.  
An external music controller that can control media playback on a computer while showing the currently playing track, artist, and progress in real time.

The project combines Bluetooth HID controls, WiFi communication, an OLED interface, and a Windows companion application.

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

### Live Display Updates

A Python companion app reads the currently playing media from Windows and sends the information back to ESP32.

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
            WiFi
              |
              v
            ESP32
              |
              v
          OLED Display
```

---

# Hardware Used

- ESP32 DevKit
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

One side of every button connects to ESP32 GND.

The opposite side connects to its GPIO pin.

| Button | Function | ESP32 GPIO |
|---|---|---|
| Left Red | Previous Track | GPIO19 |
| Left Green | Volume Down / Seek Back | GPIO18 |
| Black Center | Play / Pause | GPIO5 |
| Right Green | Volume Up / Seek Forward | GPIO17 |
| Right Red | Next Track | GPIO16 |

Button logic:

```
Not Pressed = HIGH
Pressed     = LOW
```

---

# Repository Structure

```
ESPod32/

├── firmware/
│   └── ESPod32_v1/
│       └── ESPod32_v1.ino
│
├── companion/
│   ├── main.py
│   └── requirements.txt
│
├── images/
│
├── README.md
│
└── .gitignore
```

---

# ESP32 Setup

## Required Arduino Libraries

Install these from Arduino IDE Library Manager:

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

Because Bluetooth + WiFi increases firmware size:

```
Tools
 |
 Partition Scheme
 |
 Huge APP (3MB No OTA)
```

---

## WiFi Configuration

Inside the ESP32 firmware:

Change:

```cpp
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";
```

to your WiFi details.

Example:

```cpp
const char* ssid = "HomeWiFi";
const char* password = "password123";
```

Upload the firmware.

After booting, the OLED/Serial Monitor will show the ESP32 IP address.

Example:

```
192.168.1.50
```

---

# Companion App Setup

The companion application runs on Windows.

It reads the currently playing media using Windows Media Session APIs.

---

## Create Python Environment

Go into the companion folder:

```bash
cd companion
```

Create virtual environment:

```bash
python -m venv .venv
```

Activate it:

Windows:

```bash
.venv\Scripts\activate
```

---

## Install Dependencies

```bash
pip install -r requirements.txt
```

or manually:

```bash
pip install winsdk requests
```

---

# Running

Start your music application:

Examples:

```
Spotify
Apple Music
YouTube
```

Run:

```bash
python main.py
```

The companion app will read:

```
Song Name
Artist
Current Time
Duration
Playback Status
```

and send it to ESP32.

The OLED updates automatically.

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

# Future Improvements

- Custom PCB design
- 3D printed enclosure
- Album art support
- Battery powered version
- Rotary encoder volume knob
- Touch controls

---

# Version History

## v0.1

Basic ESP32 GPIO button testing.

## v0.2

Bluetooth HID media controls.

## v0.3

Five-button hardware controller.

## v0.4

OLED interface added.

## v1.0

Live media information using WiFi and Windows companion app.
