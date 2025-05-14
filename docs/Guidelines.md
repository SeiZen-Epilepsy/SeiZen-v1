# C++ Programming Guidelines for SeiZen Project

## Introduction

This guide provides standards and best practices for writing C++ code in the SeiZen project. It focuses specifically on how to structure and organize code within the `lib` directory. Following these guidelines will help maintain consistency, improve code readability, and make collaboration easier for all developers working on the project.

## Directory Structure

The `lib` directory is organized into the following main subdirectories:

- **Modules/** - Contains hardware-related modules and interfaces
- **Task/** - Contains task management and event-driven components
- **Config/** - Contains configuration-related files

```
lib/
├── Modules/
│   └── Display/
│       ├── Oled.h
│       └── Oled.cpp
├── Task/
│   └── OTA/
│       ├── OTA.h
│       └── OTA.cpp
├── Config/
└── README
```

## File Organization

When adding new functionality to the project, follow these guidelines:

1. Place your files in the appropriate subdirectory based on their purpose:

   - Hardware-related components go in `lib/Modules/`
   - Task-related components go in `lib/Task/`
   - Configuration components go in `lib/Config/`

2. Create a new subdirectory for your component when appropriate (e.g., `lib/Modules/MyComponent/`)

3. Keep related `.h` and `.cpp` files together in the same directory

4. Use descriptive names for your directories and files that clearly indicate their functionality

## Header File (.h) Guidelines

### Include Guards

Always use include guards to prevent multiple inclusions. The naming convention follows the pattern:

```cpp
#ifndef FILENAME_H
#define FILENAME_H

// Header content goes here

#endif
```

Example from the codebase (`Oled.h`):

```cpp
#ifndef OLED_H
#define OLED_H

#include <Arduino.h>

class OLED {
    // Class content
};

#endif
```

### Dependencies

- Include `Arduino.h` when Arduino-specific functionality is required
- Keep includes to a minimum, including only what's necessary
- Use angle brackets (`<>`) for standard or external libraries
- Use quotes (`""`) for project-specific includes

### Class Structure

Organize your class in a clear, logical structure:

1. Start with public methods
2. Follow with protected methods (if any)
3. End with private methods and member variables

Example from `OTA.h`:

```cpp
class OTA {
    public:
        OTA();
        void begin();
        void handle();
        void end();
        void setHostname(const char* hostname);
        void setPassword(const char* password);
        void setPort(int port);
        void setCertificate(const char* certificate);
        void setPrivateKey(const char* privateKey);
    private:
        const char* _hostname;
        const char* _password;
        int _port;
        const char* _certificate;
        const char* _privateKey;
};
```

### Documentation

Consider using Doxygen-style comments for documenting classes, methods, and member variables:

```cpp
/**
 * @brief Class for handling OLED display operations
 */
class OLED {
    public:
        /**
         * @brief Constructor for OLED class
         */
        OLED();

        /**
         * @brief Initialize the OLED display
         */
        void begin();

        // Other methods...
};
```

## Implementation File (.cpp) Guidelines

### Header Inclusion

- Always include the corresponding header file as the first include
- Use relative paths for project-specific includes

Example from `Oled.cpp`:

```cpp
#include <Display/Oled.h>

OLED::OLED() {
    // Constructor
}
```

### Method Implementation

- Implement methods in the same order they are declared in the header file
- Use the scope resolution operator (`::`) to define class methods

Example:

```cpp
OLED::OLED() {
    // Constructor implementation
}

void OLED::begin() {
    // Implementation of begin method
}
```

### Constructor Implementation

For constructors with member initialization:

```cpp
OTA::OTA() :
    _hostname(nullptr),
    _password(nullptr),
    _port(0),
    _certificate(nullptr),
    _privateKey(nullptr) {
    // Any additional initialization
}
```

## Project-Specific Conventions

### Class Naming

- Use PascalCase for class names (e.g., `OLED`, `OTA`)
- Name classes after their functionality (e.g., `WiFiManager`, `SensorReader`)

### Method Naming

Common method names in this project include:

- `begin()` - For initialization
- `handle()` - For periodic processing
- `end()` - For cleanup or deinitialization
- Getters/setters should use `get`/`set` prefix (e.g., `setHostname()`, `getTemperature()`)

### Member Variable Naming

- Use an underscore prefix for private member variables (e.g., `_hostname`, `_password`)
- Use camelCase for member variable names

Example from `OTA.h`:

```cpp
private:
    const char* _hostname;
    const char* _password;
    int _port;
    const char* _certificate;
    const char* _privateKey;
```

## Examples from Existing Modules

### OLED Module Example

**Oled.h**:

```cpp
#ifndef OLED_H
#define OLED_H

#include <Arduino.h>

class OLED {
    public:
        OLED();
        void begin();
        void clear();
        void display();
        void printTest();
    private:
    // no private
};

#endif
```

**Oled.cpp**:

```cpp
#include <Display/Oled.h>

OLED::OLED() {
    // Constructor
}
```

### OTA Module Example

**OTA.h**:

```cpp
#ifndef OTA_H
#define OTA_H

#include <Arduino.h>
#include <ArduinoOTA.h>

class OTA {
    public:
        OTA();
        void begin();
        void handle();
        void end();
        void setHostname(const char* hostname);
        void setPassword(const char* password);
        void setPort(int port);
        void setCertificate(const char* certificate);
        void setPrivateKey(const char* privateKey);
    private:
        const char* _hostname;
        const char* _password;
        int _port;
        const char* _certificate;
        const char* _privateKey;
};

#endif
```

## Conclusion

Following these guidelines will maintain code consistency and improve project maintainability. These conventions are based on existing code patterns in the SeiZen project, and they should be adhered to when adding new C++ modules or modifying existing ones.

If you have questions or suggestions for improving these guidelines, please discuss them with the team before implementing significant deviations from these standards.
