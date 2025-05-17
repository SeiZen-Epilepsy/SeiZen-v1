# RTOS Implementation in SeiZen-v1

## Overview

The SeiZen-v1 project uses FreeRTOS to manage multiple concurrent tasks efficiently. FreeRTOS provides task scheduling, inter-task communication, and resource management capabilities that help organize the code and improve system responsiveness.

## Task Architecture

The project implements the following FreeRTOS tasks:

### 1. SendData Task

**Location**: `lib/Task/SendData/`
**Purpose**: Handles periodic transmission of sensor data over BLE
**Key Features**:

- Monitors sensor data update intervals
- Manages BLE data transmission
- Handles connection status
- Implements error handling for BLE communication

**Implementation Details**:

```cpp
class SendData {
    bool startTask(uint32_t stackSize = 2048, UBaseType_t priority = 1);
    void stopTask();
    bool isRunning() const;
}
```

### 2. LED Blink Task

**Location**: `lib/Task/LEDBlink/`
**Purpose**: Manages LED indication for BLE connection status
**Key Features**:

- Solid LED when BLE is connected
- Blinking LED when disconnected
- Configurable blink intervals

**Implementation Details**:

```cpp
class LEDBlink {
    bool startTask(uint32_t stackSize = 1024, UBaseType_t priority = 1);
    void stopTask();
    bool isRunning() const;
}
```

## RTOS Task Implementation Guidelines

### Task Class Structure Pattern

When implementing a new FreeRTOS task, follow this standard structure:

```cpp
#ifndef TASK_NAME_H
#define TASK_NAME_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

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

#endif // TASK_NAME_H
```

### Task Implementation Pattern

1. **Constructor Implementation**:

```cpp
TaskName::TaskName(dependency1* dep1, dependency2* dep2) :
    _dep1(dep1),
    _dep2(dep2),
    taskHandle(NULL),
    running(false),
    _interval(1000) {
    // Additional initialization if needed
}

TaskName::~TaskName() {
    stopTask();
}
```

2. **Task Management Methods**:

```cpp
bool TaskName::startTask(uint32_t stackSize, UBaseType_t priority) {
    // Check if already running
    if (running) return true;

    // Validate dependencies
    if (!_dep1 || !_dep2) {
        Serial.println("Invalid dependencies");
        return false;
    }

    // Create the task
    BaseType_t result = xTaskCreate(
        taskFunction,    // Task function
        "TaskName",      // Task name
        stackSize,       // Stack size
        this,            // Task parameters
        priority,        // Task priority
        &taskHandle      // Task handle
    );

    if (result != pdPASS) {
        Serial.println("Failed to create task");
        return false;
    }

    running = true;
    return true;
}

void TaskName::stopTask() {
    if (!running || taskHandle == NULL) return;

    vTaskDelete(taskHandle);
    taskHandle = NULL;
    running = false;
}

bool TaskName::isRunning() const {
    return running;
}
```

3. **Task Function Implementation**:

```cpp
void TaskName::taskFunction(void* pvParameters) {
    // Get task instance
    TaskName* task = static_cast<TaskName*>(pvParameters);

    // Validate instance
    if (!task) {
        Serial.println("Invalid task parameters");
        vTaskDelete(NULL);
        return;
    }

    // Task loop
    for (;;) {
        // Task logic here

        // Use configured interval for delay
        vTaskDelay(task->_interval / portTICK_PERIOD_MS);
    }

    // Should never reach here
    vTaskDelete(NULL);
}
```

## Task Priority Guidelines

Standardized priority levels for different types of tasks:

1. **Low Priority (1)**

   - Visual feedback tasks (LED indicators)
   - Status update tasks
   - Non-critical monitoring tasks

2. **Medium Priority (2)**

   - Communication tasks (BLE, WiFi)
   - Regular data processing
   - Sensor reading tasks

3. **High Priority (3)**
   - Critical system tasks
   - Real-time response tasks
   - Safety-critical operations

## Memory Management Guidelines

Stack size allocation guidelines:

1. **Small Tasks (1024 words)**

   - Simple LED control
   - Basic status monitoring
   - Simple calculations

2. **Medium Tasks (2048 words)**

   - Communication protocols (BLE, WiFi)
   - Data processing
   - Sensor operations

3. **Large Tasks (4096 words)**
   - Complex calculations
   - File operations
   - Multiple dependent operations

## Resource Sharing and Synchronization

1. **Mutex Usage**:

```cpp
// Declare mutex
static SemaphoreHandle_t resourceMutex = NULL;

// Create mutex in setup
resourceMutex = xSemaphoreCreateMutex();

// Use mutex in task
if (xSemaphoreTake(resourceMutex, portMAX_DELAY) == pdTRUE) {
    // Access shared resource
    xSemaphoreGive(resourceMutex);
}
```

2. **Queue Usage**:

```cpp
// Declare queue
static QueueHandle_t dataQueue = NULL;

// Create queue in setup
dataQueue = xQueueCreate(10, sizeof(DataType));

// Send data
if (xQueueSend(dataQueue, &data, portMAX_DELAY) != pdPASS) {
    Serial.println("Queue send failed");
}

// Receive data
if (xQueueReceive(dataQueue, &data, portMAX_DELAY) != pdPASS) {
    Serial.println("Queue receive failed");
}
```

## Best Practices

1. **Task Creation**

   - Always check task creation success
   - Use appropriate stack sizes
   - Set meaningful task priorities
   - Clean up resources in destructors

2. **Task Management**

   - Implement proper start/stop methods
   - Handle edge cases (already running, not initialized)
   - Clean up resources when stopping

3. **Resource Usage**

   - Use FreeRTOS primitives for synchronization
   - Avoid blocking operations in tasks
   - Use appropriate delays

4. **Error Handling**
   - Check for NULL pointers
   - Validate task parameters
   - Handle creation failures
   - Log errors for debugging

## Debugging Tips

1. **Task Monitoring**:

```cpp
void printTaskStats() {
    char* taskListBuffer = (char*)malloc(2048);
    if (taskListBuffer) {
        vTaskList(taskListBuffer);
        Serial.println("Task Stats:");
        Serial.println(taskListBuffer);
        free(taskListBuffer);
    }
}
```

2. **Memory Monitoring**:

```cpp
void printMemoryStats() {
    Serial.printf("Free Heap: %d bytes\n", ESP.getFreeHeap());
    Serial.printf("Min Free Heap: %d bytes\n", ESP.getMinFreeHeap());
}
```

## Future Considerations

1. **Performance Optimization**

   - Monitor task execution times
   - Adjust priorities based on profiling
   - Optimize memory usage

2. **Feature Extensions**
   - Task notification system
   - Advanced error handling
   - Task statistics collection

## Conclusion

This RTOS implementation provides a robust foundation for real-time operations in the SeiZen-v1 project. Following these guidelines ensures consistent and maintainable task implementations across the project.

For general C++ coding guidelines, please refer to the [Guidelines.md](Guidelines.md) documentation.
