#include "FreeRTOSTasks/XUartDMATask.hpp"

void XUartDMATask::execute() {
    etl::string<17> usartData = "testing";
    while (true) {
        LOG_DEBUG << usartData.data();
        vTaskDelay(pdMS_TO_TICKS(delayMs));
    }
}