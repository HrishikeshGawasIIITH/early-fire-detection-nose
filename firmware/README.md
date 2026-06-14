# Firmware

All sketches target an **ESP32 Dev Module** (Arduino core for ESP32) and talk to the MLX90640 IR array over I2C using the bundled SparkFun/Melexis driver (`MLX90640_API.*`, `MLX90640_I2C_Driver.*` — see [`../THIRD_PARTY_NOTICES.md`](../THIRD_PARTY_NOTICES.md)).

## Sketches, in development order

### 1. `mlx_test`
Minimal bring-up sketch: initializes the MLX90640, reads frames, and prints the hottest pixel's temperature over Serial. Used to verify wiring and sensor communication.

### 2. `hr_wifi`
Early prototype that connects to WiFi and hosts a small web dashboard (live chart of MiniPID2 voltage and temperature readings via `ESPAsyncWebServer` + Highcharts). Also drives an OLED display.

> **Before flashing**: set your own network credentials — replace `YOUR_WIFI_SSID` / `YOUR_WIFI_PASSWORD` near the top of `hr_wifi.ino`.

### 3. `efd_nose_main`
Final integrated firmware. Reads the MLX90640 thermal array and a MiniPID2 PID gas sensor (30-sample average), shows peak temperature and PID-derived values on an SSD1306 OLED, and drives a buzzer + LED alarm when the peak temperature exceeds ~42°C or the PID reading exceeds its threshold — the core early-fire-detection logic.

## Required Arduino libraries

- `Adafruit GFX Library`
- `Adafruit SSD1306`
- `ESPAsyncWebServer` + `AsyncTCP` (for `hr_wifi` only)
- `Wire` (built-in)

The MLX90640 driver files are included directly in each sketch folder, so the SparkFun Qwiic MLX90640 library does not need to be installed separately.

## Hardware connections

- MLX90640 IR array — I2C (default address `0x33`)
- SSD1306 OLED — I2C (address `0x3C`)
- MiniPID2 — analog output on GPIO 34
- Buzzer — GPIO 32
- LED — GPIO 25
