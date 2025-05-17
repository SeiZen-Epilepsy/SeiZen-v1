# RTOS Implementation in SeiZen-v1

This document describes the Real-Time Operating System (RTOS) implementation in the SeiZen-v1 project using FreeRTOS on the ESP32 platform.

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

## Task Priority Levels

Tasks are assigned different priority levels based on their importance:

1. LED Blink Task: Priority 1 (Lower)

   - Less critical, visual feedback only
   - Stack Size: 1024 words

2. SendData Task: Priority 2 (Higher)
   - More critical, handles data communication
   - Stack Size: 2048 words

## Memory Management

Each task is allocated a specific stack size:

- Smaller stack (1024 words) for simple tasks like LED control
- Larger stack (2048 words) for complex tasks involving BLE communication
- Dynamic memory allocation for task objects using `new` operator

## Task Communication

Tasks communicate through the following mechanisms:

1. **Shared Resources**:

   - BLE server instance shared between tasks
   - Protected through FreeRTOS synchronization primitives

2. **Status Monitoring**:
   - Tasks monitor BLE connection status
   - LED task responds to connection state changes

## Implementation Pattern

Each task follows a consistent implementation pattern:

1. **Header File (.h)**:

   - Class declaration
   - Public interface methods
   - Private member variables
   - Task function declaration

2. **Source File (.cpp)**:
   - Constructor/destructor implementation
   - Task management methods
   - Static task function implementation
   - Error handling

Example Task Structure:

```cpp
class TaskName {
public:
    // Constructor/Destructor
    TaskName(dependencies...);
    ~TaskName();

    // Task Management
    bool startTask(uint32_t stackSize, UBaseType_t priority);
    void stopTask();
    bool isRunning() const;

private:
    static void taskFunction(void* pvParameters);
    TaskHandle_t taskHandle;
    bool running;
};
```

## Error Handling

Tasks implement the following error handling mechanisms:

1. **Task Creation**:

   - Verification of successful task creation
   - Error reporting through Serial interface
   - Status return values for error checking

2. **Runtime Errors**:
   - Null pointer checks for dependencies
   - Connection status verification
   - Resource availability checks

## Best Practices

1. **Task Independence**:

   - Each task has a single, well-defined responsibility
   - Minimal dependencies between tasks
   - Clear separation of concerns

2. **Resource Management**:

   - Proper cleanup in destructors
   - Memory deallocation for dynamic objects
   - Task deletion when stopping

3. **Code Organization**:
   - Tasks grouped in the `lib/Task` directory
   - Consistent file naming and structure
   - Clear separation of interface and implementation

## Future Considerations

1. **Scalability**:

   - Easy addition of new tasks
   - Consistent task implementation pattern
   - Modular architecture

2. **Potential Improvements**:

   - Implementation of task queues for data passing
   - Addition of mutex for shared resource protection
   - Implementation of event groups for synchronization

3. **Monitoring and Debugging**:
   - Task statistics collection
   - Performance monitoring
   - Debug logging capabilities

## Conclusion

The RTOS implementation in SeiZen-v1 provides a robust foundation for real-time task management. The modular architecture and consistent implementation patterns make it easy to maintain and extend the system with new functionality.
