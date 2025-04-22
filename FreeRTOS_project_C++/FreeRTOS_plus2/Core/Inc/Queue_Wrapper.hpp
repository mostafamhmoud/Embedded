
// Queue.hpp
#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "FreeRTOS.h"
#include "queue.h"
#include "main.h" // if needed for Error_Handler

template <typename T>
class Queue
{
public:
    Queue(size_t queueSize)
    {
        // The queue will store pointers to type T, hence we need sizeof(T*) not sizeof(void*)
        queueHandle = xQueueCreate(queueSize, sizeof(T));
        if (queueHandle == nullptr)
        {
            Error_Handler();
        }
    }

    // Send data to the queue
    bool send(T& item, TickType_t waitTime = portMAX_DELAY)
    {
        return xQueueSend(queueHandle, &item, waitTime) == pdPASS;
    }

    // Send data from ISR
    bool sendFromISR(T& item, BaseType_t* pxHigherPriorityTaskWoken = NULL)
    {
        return xQueueSendFromISR(queueHandle, (void*)&item, pxHigherPriorityTaskWoken) == pdPASS;
    }

    // Receive data from the queue
    bool receive(T& item, TickType_t waitTime = portMAX_DELAY)
    {
        return xQueueReceive(queueHandle, static_cast<void*>(&item), waitTime) == pdTRUE;
    }

    // Receive data from ISR
    bool receiveFromISR(T& item, BaseType_t* pxHigherPriorityTaskWoken = NULL)
    {
        return xQueueReceiveFromISR(queueHandle, static_cast<void*>(&item), pxHigherPriorityTaskWoken) == pdTRUE;
    }

    UBaseType_t getQueueSize()
    {
        return uxQueueMessagesWaiting(queueHandle);
    }

    // Overwrite the item in the queue from an ISR (only for queues of size 1)
    bool overwriteFromISR(T& item, BaseType_t* pxHigherPriorityTaskWoken = NULL)
    {
    	return xQueueOverwriteFromISR(queueHandle, static_cast<const void*>(&item), pxHigherPriorityTaskWoken) == pdPASS;
    }

    // Peek data from the queue
    bool peek(T& item)
    {
        return xQueuePeek(queueHandle, &item, 0) == pdPASS;
    }

    // Check if queue is empty
    bool isEmpty()
    {
        return uxQueueMessagesWaiting(queueHandle) == 0;
    }

    // Check if queue is empty from ISR
    bool isEmptyFromISR()
    {
        return xQueueIsQueueEmptyFromISR(queueHandle) == pdTRUE;
    }

    // Check if queue is full
    bool isFull()
    {
        return uxQueueSpacesAvailable(queueHandle) == 0;
    }

    // Check if queue is full from ISR
    bool isFullFromISR()
    {
        return xQueueIsQueueFullFromISR(queueHandle) == pdTRUE;
    }

    // Return the handle of the queue
    QueueHandle_t getHandle() const
    {
        return queueHandle;
    }

private:
    QueueHandle_t queueHandle;
};

#endif
