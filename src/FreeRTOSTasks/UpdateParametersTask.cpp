#include "FreeRTOSTasks/UpdateParametersTask.hpp"

void UpdateParametersTask::execute() {
    TaskHandle_t reportParametersHandle = xTaskGetHandle(taskName);

    while (true) {
        PlatformParameters::reportParametersUnusedStack.setValue(
                uxTaskGetStackHighWaterMark(reportParametersHandle));
        PlatformParameters::availableHeap.setValue(
                static_cast<uint16_t>(xPortGetFreeHeapSize()));
        PlatformParameters::obcBootCounter.setValue(
                static_cast<uint16_t>(BootCounter::GPBRRead(BootCounter::BootCounterRegister)));
        PlatformParameters::obcSysTick.setValue(static_cast<uint64_t>(xTaskGetTickCount()));
        vTaskDelay(pdMS_TO_TICKS(delayMs));
    }
}
