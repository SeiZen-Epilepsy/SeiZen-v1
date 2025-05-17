# SeiZen-v1

## Project Overview

SeiZen-v1 is an ESP32-based IoT project leveraging the ESP32 DOIT DevKit V1 development board. The project integrates display capabilities through the ST7789 display module, implements BLE communication, and utilizes FreeRTOS for efficient task management and real-time operations.

This project is structured as a PlatformIO project, making it easy to develop, build, and upload firmware to ESP32 devices within Visual Studio Code or other compatible IDEs.

## Project Structure

```
SeiZen-v1/
├── .pio/                   # PlatformIO build files and dependencies
├── .vscode/                # VS Code configuration
├── docs/                   # Project documentation
│   ├── Guidelines.md       # Coding guidelines and standards
│   └── RTOS.md             # RTOS implementation details
├── include/                # Header files
├── lib/                    # Project-specific libraries
│   ├── Config/             # Configuration settings
│   ├── Modules/            # Hardware module implementations
│   │   ├── Display/        # Display module code
│   │   ├── BLE/            # Bluetooth Low Energy implementation
│   │   └── Sensor/         # Sensor modules
│   └── Task/               # Task-specific implementations
│       ├── OTA/            # Over-the-Air update functionality
│       ├── SendData/       # BLE data transmission task
│       └── LEDBlink/       # LED indication task
├── src/                    # Source code
│   └── main.cpp            # Main application entry point
├── test/                   # Unit tests
└── platformio.ini          # PlatformIO configuration
```

## Dependencies

This project relies on the following libraries and dependencies:

- **Platform**: ESP32 (Espressif32)
- **Board**: ESP32 DOIT DevKit V1
- **Framework**: Arduino with FreeRTOS
- **Core Features**:
  - FreeRTOS Task Management
  - BLE Communication
  - Over-the-Air Updates

### Libraries

- **Adafruit ST7789**: Display driver for the ST7789 TFT display
- **Adafruit GFX Library**: Graphics library for drawing shapes, text, and images
- **Adafruit BusIO**: Abstraction layer for I2C and SPI communications
- **ESP32 BLE**: Built-in BLE functionality

[Previous sections about Setup and Installation remain unchanged...]

## Development

### RTOS Implementation

The project uses FreeRTOS for task management and real-time operations. Key components include:

1. **SendData Task**:

   - Handles periodic BLE data transmission
   - Manages sensor data collection
   - Located in `lib/Task/SendData/`

2. **LEDBlink Task**:

   - Manages LED status indication
   - Reflects BLE connection state
   - Located in `lib/Task/LEDBlink/`

3. **OTA Task**:
   - Handles firmware updates over WiFi
   - Located in `lib/Task/OTA/`

For detailed information about the RTOS implementation, refer to `docs/RTOS.md`.

### Task Development Guidelines

When developing new tasks:

1. Follow the established pattern in `lib/Task/`
2. Implement proper task management (creation, deletion)
3. Use appropriate stack sizes and priorities
4. Handle resource sharing correctly
5. Follow the project's coding guidelines in `docs/Guidelines.md`

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

### Documentation

- **Guidelines.md**: Contains coding standards and best practices
- **RTOS.md**: Details about RTOS implementation and task management
- Additional documentation can be found in the `docs/` directory

### Main Application

The main application code is in `src/main.cpp`. This file initializes the system and starts the necessary RTOS tasks.

### BLE Communication

The project implements BLE communication for data transmission:

- BLE server implementation in `lib/Modules/BLE/`
- Data transmission handled by SendData task
- LED indication for connection status

### OTA Updates

The project includes Over-the-Air (OTA) update capabilities in the `lib/Task/OTA` directory. Configure this according to your network settings to enable wireless firmware updates.

### Display Configuration

Display module settings and implementations are located in `lib/Modules/Display`. Adjust these files to configure your ST7789 display according to your hardware setup.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

MIT License is a permissive license that allows for reuse with minimal restrictions. It permits commercial use, modification, distribution, and private use while providing only the conditions that the license and copyright notice must be included with the software.
