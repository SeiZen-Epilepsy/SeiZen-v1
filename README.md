# SeiZen-v1

## Project Overview

SeiZen-v1 is an ESP32-based IoT project leveraging the ESP32 DOIT DevKit V1 development board. The project integrates display capabilities through the ST7789 display module and utilizes various Adafruit libraries for graphics rendering and I/O operations.

This project is structured as a PlatformIO project, making it easy to develop, build, and upload firmware to ESP32 devices within Visual Studio Code or other compatible IDEs.

## Project Structure

```
SeiZen-v1/
├── .pio/                   # PlatformIO build files and dependencies
├── .vscode/                # VS Code configuration
├── docs/                   # Project documentation
├── include/                # Header files
├── lib/                    # Project-specific libraries
│   ├── Config/             # Configuration settings
│   ├── Modules/            # Hardware module implementations
│   │   └── Display/        # Display module code
│   └── Task/               # Task-specific implementations
│       └── OTA/            # Over-the-Air update functionality
├── src/                    # Source code
│   └── main.cpp            # Main application entry point
├── test/                   # Unit tests
└── platformio.ini          # PlatformIO configuration
```

## Dependencies

This project relies on the following libraries and dependencies:

- **Platform**: ESP32 (Espressif32)
- **Board**: ESP32 DOIT DevKit V1
- **Framework**: Arduino

### Libraries

- **Adafruit ST7789**: Display driver for the ST7789 TFT display
- **Adafruit GFX Library**: Graphics library for drawing shapes, text, and images
- **Adafruit BusIO**: Abstraction layer for I2C and SPI communications

## Setup and Installation

### Prerequisites

1. Install [Visual Studio Code](https://code.visualstudio.com/)
2. Install [PlatformIO Extension](https://platformio.org/install/ide?install=vscode) for VS Code
3. Install necessary USB drivers for ESP32 (if not already installed)

### Hardware Setup

1. Connect the ESP32 DOIT DevKit V1 to your computer via USB
2. Wire the ST7789 display to the ESP32 according to your pin configuration
   - Common connections include:
     - VCC to 3.3V
     - GND to GND
     - SCL/CLK to GPIO pin (defined in your configuration)
     - SDA/MOSI to GPIO pin (defined in your configuration)
     - RES/RST to GPIO pin (defined in your configuration)
     - DC to GPIO pin (defined in your configuration)
     - BLK to GPIO pin or 3.3V (for backlight)

### Software Setup

1. Clone this repository:
   ```
   git clone https://github.com/SeiZen-Epilepsy/SeiZen-v1.git
   cd SeiZen-v1
   ```
2. Open the project in VS Code with PlatformIO
3. PlatformIO will automatically install the required dependencies specified in `platformio.ini`

## Building and Running

### Build the Project

```
pio run
```

### Upload to ESP32

```
pio run -t upload
```

### Monitor Serial Output

```
pio device monitor
```

### Combined Build and Upload

```
pio run -t upload && pio device monitor
```

## Development

### Project Configuration

The main project configuration is defined in `platformio.ini`. This file specifies the target platform, board, framework, and library dependencies.

### Adding New Dependencies

To add new libraries, modify the `lib_deps` section in `platformio.ini`:

```
lib_deps =
    adafruit/Adafruit ST7789
    adafruit/Adafruit GFX Library
    adafruit/Adafruit BusIO
    ; Add your new dependency here
```

### Custom Libraries

Place custom libraries in the `lib/` directory. Each library should have its own folder containing header (.h) and implementation (.cpp) files.

### Main Application

The main application code is in `src/main.cpp`. Modify this file to implement your application logic.

### OTA Updates

The project includes Over-the-Air (OTA) update capabilities in the `lib/Task/OTA` directory. Configure this according to your network settings to enable wireless firmware updates.

### Display Configuration

Display module settings and implementations are located in `lib/Modules/Display`. Adjust these files to configure your ST7789 display according to your hardware setup.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

MIT License is a permissive license that allows for reuse with minimal restrictions. It permits commercial use, modification, distribution, and private use while providing only the conditions that the license and copyright notice must be included with the software.
