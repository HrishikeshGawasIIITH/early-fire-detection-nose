# EFD-Nose — Early Fire Detection Nose for Human Space Capsules

An ESP32-based electronic "nose" that combines a thermal infrared array (MLX90640) with a PID gas sensor (MiniPID2) to detect the earliest signatures of an overheat/fire event inside a sealed crew cabin — before it becomes a visible flame. This work was developed for human spaceflight applications and published in *IEEE Aerospace and Electronic Systems Magazine* (2025).

## Overview

- **Thermal sensing**: a SparkFun Qwiic MLX90640 32x24 IR array continuously scans the cabin for hotspots.
- **Gas sensing**: a MiniPID2 photoionization detector (PID) provides an aggregate VOC reading, used to flag pyrolysis off-gassing (benzene, ammonia, toluene, NO2, ethylene, PTFE byproducts, etc.) that typically precedes open flame.
- **Local alerting**: an onboard buzzer + LED trigger immediately when either the hottest pixel or the PID reading crosses a threshold.
- **OLED display**: live readout of peak temperature and PID values.
- **Enclosure**: custom 3D-printed housing designed for the sensor stack.

## Repository structure

| Path | Contents |
|---|---|
| [`firmware/`](firmware/) | ESP32 (Arduino) sketches — sensor bring-up, WiFi dashboard prototype, and the final integrated detector |
| [`hardware/enclosure/`](hardware/enclosure/) | 3D-printable enclosure (STL models + sliced gcode for a Creality Ender 3 S1) |
| [`hardware/label/`](hardware/label/) | Device label artwork |
| [`docs/`](docs/) | State-of-the-art comparison spreadsheet and conference presentation materials |

## Firmware

See [`firmware/README.md`](firmware/README.md) for details on each sketch and required Arduino libraries.

- `mlx_test` — bring-up/test sketch for the MLX90640 IR array
- `hr_wifi` — early prototype that streams sensor data to a live web dashboard over WiFi
- `efd_nose_main` — final integrated firmware: thermal + PID sensing, OLED display, buzzer/LED alarm

## Hardware

The [`hardware/enclosure/`](hardware/enclosure/) folder contains the STL files and a Creality Ender 3 S1 (CE3S1) sliced gcode for the two-part enclosure used to house the sensor stack.

## Results

A state-of-the-art comparison against other electronic-nose / fire-detection approaches is in [`docs/sota_comparison.xlsx`](docs/sota_comparison.xlsx).

## Presentations

- [`docs/presentation/ieeespace2024_slides.pptx`](docs/presentation/ieeespace2024_slides.pptx) — slides presented at IEEE Aerospace Conference 2024
- [`docs/presentation/speaker_notes_ieee_space.pdf`](docs/presentation/speaker_notes_ieee_space.pdf) — accompanying speaker notes

## Publication

This work is published as:

> S. Kumar, H. M. Gawas, A. Gupta, P. Sharma and M. J, "Design and Development of an Early Fire Detection Nose (EFD-Nose) for Human Space Capsule," in *IEEE Aerospace and Electronic Systems Magazine*, vol. 40, no. 11, pp. 58-69, 2025, doi: [10.1109/MAES.2025.3580516](https://doi.org/10.1109/MAES.2025.3580516).

```bibtex
@ARTICLE{11045157,
  author={Kumar, Sanchit and Gawas, Hrishikesh M and Gupta, Akash and Sharma, Payal and J, Manikandan},
  journal={IEEE Aerospace and Electronic Systems Magazine},
  title={Design and Development of an Early Fire Detection Nose (EFD-Nose) for Human Space Capsule},
  year={2025},
  volume={40},
  number={11},
  pages={58-69},
  keywords={Sensors;Gases;Aerospace electronics;Sensor systems;Prototypes;Monitoring;Temperature sensors;Space vehicles;Detection algorithms;Fires;Aerospace materials;Electronic Nose;Electronic Eye;Embedded System Design;Fire Detection;Human Space Capsule},
  doi={10.1109/MAES.2025.3580516}}
```

See [`CITATION.cff`](CITATION.cff) for GitHub's citation widget.

## License

This project's code, hardware designs, and documentation are licensed under the [MIT License](LICENSE). The bundled MLX90640 driver retains its original Apache-2.0 license — see [`THIRD_PARTY_NOTICES.md`](THIRD_PARTY_NOTICES.md).
