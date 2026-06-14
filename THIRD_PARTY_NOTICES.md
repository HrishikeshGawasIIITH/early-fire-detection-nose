# Third-Party Notices

This repository bundles the following third-party files so that each firmware
sketch builds standalone in the Arduino IDE.

## MLX90640 driver

- **Files**: `MLX90640_API.cpp`, `MLX90640_API.h`, `MLX90640_I2C_Driver.cpp`, `MLX90640_I2C_Driver.h`
  (present in `firmware/mlx_test/`, `firmware/hr_wifi/`, and `firmware/efd_nose_main/`)
- **Source**: [SparkFun Qwiic_IR_Array_MLX90640](https://github.com/sparkfun/Qwiic_IR_Array_MLX90640)
- **Copyright**: (c) 2017 Melexis N.V.
- **License**: Apache License, Version 2.0 — http://www.apache.org/licenses/LICENSE-2.0

## ESP32 debug configuration files

- **Files**: `esp32.svd`, `debug.cfg`, `debug_custom.json`
  (present in `firmware/hr_wifi/` and `firmware/efd_nose_main/`)
- **Source**: Espressif / Arduino-ESP32 toolchain — used for hardware register debugging (e.g. with OpenOCD / Cortex-Debug)
