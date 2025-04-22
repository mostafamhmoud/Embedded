#ifndef BASETASK_HPP
#define BASETASK_HPP

#include "FreeRTOS.h"
#include "task.h"

// BaseTask class definition
class BaseTask
{
public:
    // Constructor for the base class
    BaseTask(const char* name, uint16_t stackSize, UBaseType_t priority)
        : _taskName(name), _stackSize(stackSize), _priority(priority), TaskHandle(nullptr) {}

    // Start the task
    void start()
    {
        if (TaskHandle == nullptr)
        {
            xTaskCreate(BaseTask::TaskEntry, _taskName, _stackSize, this, _priority, &TaskHandle);
        }
    }

    // Task entry function (static, required for FreeRTOS)
    static void TaskEntry(void* pvParams)
    {
        BaseTask* task = static_cast<BaseTask*>(pvParams);
        task->run(); // Calls the run method of the derived class
    }

    // Get the task handle
    TaskHandle_t GetTaskHandle() { return TaskHandle; }

protected:
    // Pure virtual function - must be implemented by child classes
    virtual void run() = 0;

    const char* _taskName;   // Task name
    uint16_t _stackSize;     // Stack size for the task
    UBaseType_t _priority;   // Task priority


private:
    TaskHandle_t TaskHandle; // Handle for the task instance
};

#endif // BASETASK_HPP
