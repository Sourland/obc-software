#include "main.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "list.h"
#include "task.h"
#include "definitions.h"
#include "OBC_Definitions.hpp"
#include "FreeRTOSTasks.hpp"
#include "BootCounter.hpp"

extern "C" void main_cpp() {
    SYS_Initialize(NULL);

    BootCounter::incrementBootCounter();

    const char * taskName = "Task1";
    xTaskCreate(FreeRTOSTasks::reportParameters, taskName, FreeRTOSTaskStackDepth,
                NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(FreeRTOSTasks::updateParameters, "Task2", FreeRTOSTaskStackDepth,
                &taskName, tskIDLE_PRIORITY + 1, NULL);

    vTaskStartScheduler();

    while (true) {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks();
    }

    return;
}
