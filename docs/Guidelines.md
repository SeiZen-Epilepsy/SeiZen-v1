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
│   ├── SendData/
│   │   ├── SendData.h
│   │   └── SendData.cpp
│   └── LEDBlink/
│       ├── LEDBlink.h
│       └── LEDBlink.cpp
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

## RTOS Task Implementation Guidelines

### Task Class Structure

When implementing a new FreeRTOS task, follow this standard structure:

```cpp
class TaskName {
public:
    // Constructor with dependencies
    TaskName(dependency1* dep1, dependency2* dep2);
    ~TaskName();

    // Task management methods
    bool startTask(uint32_t stackSize = defaultStackSize,
                  UBaseType_t priority = defaultPriority);
    void stopTask();
    bool isRunning() const;

private:
    // Static task function
    static void taskFunction(void* pvParameters);

    // Task control variables
    TaskHandle_t taskHandle;
    bool running;

    // Dependencies
    dependency1* _dep1;
    dependency2* _dep2;

    // Task parameters
    uint32_t _interval;
};
```

### Task Implementation Pattern

1. **Constructor**:
   - Initialize member variables
   - Set default values
   - Store dependencies

```cpp
TaskName::TaskName(dependency1* dep1, dependency2* dep2) :
    _dep1(dep1),
    _dep2(dep2),
    taskHandle(NULL),
    running(false),
    _interval(1000) {
}
```

2. **Task Management**:
   - Implement start/stop methods
   - Handle task creation/deletion
   - Check for errors

```cpp
bool TaskName::startTask(uint32_t stackSize, UBaseType_t priority) {
    if (running) return true;

    BaseType_t result = xTaskCreate(
        taskFunction,
        "TaskName",
        stackSize,
        this,
        priority,
        &taskHandle
    );

    if (result != pdPASS) {
        Serial.println("Failed to create task");
        return false;
    }

    running = true;
    return true;
}
```

3. **Task Function**:
   - Implement the main task loop
   - Handle errors and edge cases
   - Use appropriate delays

```cpp
void TaskName::taskFunction(void* pvParameters) {
    TaskName* task = static_cast<TaskName*>(pvParameters);

    for (;;) {
        // Task logic here
        vTaskDelay(task->_interval / portTICK_PERIOD_MS);
    }
}
```

### Task Priority Guidelines

- Use consistent priority levels across tasks:
  - Priority 1: Background tasks (LED indicators, status updates)
  - Priority 2: Communication tasks (BLE, WiFi)
  - Priority 3: Critical tasks (Sensor reading, data processing)

### Memory Management

- Use appropriate stack sizes based on task complexity:
  - Simple tasks (LED control): 1024 words
  - Communication tasks: 2048 words
  - Complex tasks: 4096 words

### Error Handling

Implement comprehensive error checking:

```cpp
bool TaskName::startTask(uint32_t stackSize, UBaseType_t priority) {
    // Check dependencies
    if (!_dep1 || !_dep2) {
        Serial.println("Invalid dependencies");
        return false;
    }

    // Create task
    BaseType_t result = xTaskCreate(...);
    if (result != pdPASS) {
        Serial.println("Task creation failed");
        return false;
    }

    return true;
}
```

## Examples from Existing Modules

[Previous examples remain unchanged...]

### SendData Task Example

**SendData.h**:

```cpp
#ifndef SEND_DATA_H
#define SEND_DATA_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <BLE/BLE.h>

class SendData {
public:
    SendData(BLE* ble, Dummy* sensor);
    ~SendData();

    bool startTask(uint32_t stackSize = 2048, UBaseType_t priority = 1);
    void stopTask();
    bool isRunning() const;

private:
    static void taskFunction(void* pvParameters);
    TaskHandle_t taskHandle;
    bool running;

    BLE* bleServer;
    Dummy* dummySensor;
};

#endif
```

## Best Practices for RTOS Tasks

1. **Task Creation**

   - Create tasks in setup() or when dependencies are ready
   - Use appropriate stack sizes and priorities
   - Check task creation success

2. **Task Management**

   - Implement proper cleanup in destructors
   - Handle task deletion safely
   - Monitor task status

3. **Resource Sharing**
   - Use FreeRTOS primitives for synchronization
   - Avoid long critical sections
   - Handle shared resource access carefully

## Conclusion

Following these guidelines will maintain code consistency and improve project maintainability. These conventions are based on existing code patterns in the SeiZen project, and they should be adhered to when adding new C++ modules or modifying existing ones.

If you have questions or suggestions for improving these guidelines, please discuss them with the team before implementing significant deviations from these standards.
