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
│   ├── Display/
│   │   ├── Oled.h
│   │   └── Oled.cpp
│   ├── BLE/
│   │   ├── BLE.h
│   │   └── BLE.cpp
│   └── Sensor/
│       └── Dummy/
│           ├── Dummy.h
│           └── Dummy.cpp
├── Task/
│   ├── OTA/
│   │   ├── OTA.h
│   │   └── OTA.cpp
│   └── SendData/
│       ├── SendData.h
│       └── SendData.cpp
├── Config/
└── README
```

## Creating New Files

When adding new functionality to the project, follow these guidelines for creating and organizing your files:

### Step 1: Directory Creation

Identify the appropriate category for your component:

- Hardware/peripheral interfaces → `lib/Modules/`
- Task-based components → `lib/Task/`
- Configuration files → `lib/Config/`

### Step 2: Header File (.h) Creation

1. Create the header file with the following structure:

```cpp
#ifndef MY_COMPONENT_H
#define MY_COMPONENT_H

#include <Arduino.h>
// Add other necessary includes here

class MyComponent {
public:
    // Constructor & Destructor
    MyComponent();
    ~MyComponent();

    // Initialization method (if needed)
    void begin();

    // Core functionality methods
    void doSomething();
    void handleEvent();

    // Getters & Setters
    void setValue(int value);
    int getValue() const;

private:
    // Private helper methods
    void helperFunction();

    // Member variables (use underscore prefix)
    int _value;
    bool _isInitialized;
};

#endif // MY_COMPONENT_H
```

### Step 3: Implementation File (.cpp) Creation

1. Create the implementation file with the following structure:

```cpp
#include "MyComponent.h"

// Constructor implementation
MyComponent::MyComponent() :
    _value(0),
    _isInitialized(false)
{
}

// Destructor implementation
MyComponent::~MyComponent() {
    // Cleanup code here
}

// Initialization method
void MyComponent::begin() {
    if (_isInitialized) return;

    // Initialization code here
    _isInitialized = true;
}

// Core functionality methods
void MyComponent::doSomething() {
    if (!_isInitialized) {
        Serial.println("Error: Component not initialized");
        return;
    }

    // Implementation code here
}

// Getter & Setter implementations
void MyComponent::setValue(int value) {
    _value = value;
}

int MyComponent::getValue() const {
    return _value;
}

// Private helper method implementations
void MyComponent::helperFunction() {
    // Helper code here
}
```

## Coding Style Guidelines

### Header File Guidelines

1. **Include Guards**:

   - Use `#ifndef` and `#define` guards
   - Name should match component name in uppercase
   - End with `_H` suffix

2. **Dependencies**:

   - Include only necessary headers
   - Use angle brackets for external libraries
   - Use quotes for project files

3. **Class Declaration**:
   - Start with public members
   - Group related methods together
   - Document complex functionality
   - Use const where appropriate

### Implementation File Guidelines

1. **File Organization**:

   - Include corresponding header first
   - Group method implementations logically
   - Implement methods in same order as declared

2. **Constructor Implementation**:

   - Initialize all member variables
   - Use initialization lists
   - Check for valid parameters

3. **Error Handling**:
   - Check initialization state
   - Validate parameters
   - Report errors via Serial for debugging

### Method Implementation

1. **Method Structure**:

```cpp
ReturnType ClassName::methodName(ParamType param) {
    // 1. Parameter validation
    if (!isValid(param)) {
        Serial.println("Invalid parameter");
        return errorValue;
    }

    // 2. State checking
    if (!_isInitialized) {
        Serial.println("Not initialized");
        return errorValue;
    }

    // 3. Main logic
    // Implementation code here

    // 4. Return result
    return result;
}
```

2. **Common Patterns**:
   - Begin with parameter validation
   - Check object state
   - Implement main logic
   - Return results

## Naming Conventions

1. **Classes**:

   - PascalCase (e.g., `MyComponent`)
   - Descriptive of functionality

2. **Methods**:

   - camelCase (e.g., `doSomething`)
   - Verb-based names
   - Use `get`/`set` for accessors

3. **Variables**:

   - camelCase
   - Private members with underscore prefix
   - Descriptive names

4. **Constants**:
   - UPPERCASE with underscores
   - Descriptive names

## Documentation

1. **Class Documentation**:

```cpp
/**
 * @brief Brief description of the class
 *
 * Detailed description of the class functionality,
 * usage, and any important notes.
 */
class MyComponent {
    // Class implementation
};
```

2. **Method Documentation**:

```cpp
/**
 * @brief Brief description of method
 * @param param Description of parameter
 * @return Description of return value
 */
ReturnType methodName(ParamType param);
```

## Conclusion

Following these guidelines will maintain code consistency and improve project maintainability. These conventions are based on existing code patterns in the SeiZen project, and they should be adhered to when adding new C++ modules or modifying existing ones.

For RTOS-specific implementation guidelines, please refer to the [RTOS Guidelines](RTOS_Guideline/README.md) documentation.
