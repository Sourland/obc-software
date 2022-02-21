#include "FreeRTOSTasks.hpp"
#include "FreeRTOS.h"
#include "task.h"
#include "PlatformParameters.hpp"
#include "ServicePool.hpp"
#include "BootCounter.hpp"
#include "definitions.h"
#include "Logger.hpp"

namespace FreeRTOSTasks {
    void reportParameters(void *) {
        Message request = Message(ParameterService::ServiceType,
                                  ParameterService::MessageType::ReportParameterValues,
                                  Message::TC, 1);
        const uint16_t numberOfIDs = 10;
        request.appendUint16(numberOfIDs);
        request.appendUint16(PlatformParameters::OnBoardYear);
        request.appendUint16(PlatformParameters::OnBoardMonth);
        request.appendUint16(PlatformParameters::OnBoardDay);
        request.appendUint16(PlatformParameters::OnBoardHour);
        request.appendUint16(PlatformParameters::OnBoardMinute);
        request.appendUint16(PlatformParameters::OnBoardSecond);
        request.appendUint16(PlatformParameters::ReportParametersUnusedStack);
        request.appendUint16(PlatformParameters::AvailableHeap);
        request.appendUint16(PlatformParameters::OBCBootCounter);
        request.appendUint16(PlatformParameters::OBCSystick);

        while (true) {
            MessageParser::execute(request);
            request.resetRead();
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }

    void updateParameters(void *taskName) {
        TaskHandle_t reportParametersHandle = xTaskGetHandle(*static_cast<const char **>(taskName));

        while (true) {
            PlatformParameters::reportParametersUnusedStack.setValue(
                    uxTaskGetStackHighWaterMark(reportParametersHandle));
            PlatformParameters::availableHeap.setValue(
                    static_cast<uint16_t>(xPortGetFreeHeapSize()));
            PlatformParameters::obcBootCounter.setValue(
                    static_cast<uint16_t>(BootCounter::GPBRRead(BootCounter::BootCounterRegister)));
            PlatformParameters::obcSysTick.setValue(static_cast<uint64_t>(xTaskGetTickCount()));
            PlatformParameters::onBoardSecond.setValue(static_cast<uint64_t>(xTaskGetTickCount() / 1000));
            vTaskDelay(pdMS_TO_TICKS(300));
        }
    }

    void xUartDMA(void *pvParameters) {
        etl::string<17> usartData = "testing";
        while (true) {
            LOG_DEBUG << usartData.data();
            vTaskDelay(pdMS_TO_TICKS(3000));
        }
    }

    void Housekeeping(void *pvParameters) {
        auto &housekeeping = Services.housekeeping;

        uint8_t numOfStructIds = 1;
        uint8_t structId = 0;
        for (int i = 0; i < numOfStructIds; i++) {
            structId = i;

            Message createStructure = Message(HousekeepingService::ServiceType,
                                              HousekeepingService::MessageType::CreateHousekeepingReportStructure,
                                              Message::TC, 1);
            createStructure.appendUint8(structId);
            uint32_t collectionInterval = 500;
            createStructure.appendUint32(collectionInterval);
            uint16_t numOfSimplyCommutatedParams = 2;
            createStructure.appendUint16(numOfSimplyCommutatedParams);
            createStructure.appendUint16(PlatformParameters::OnBoardSecond);
            createStructure.appendUint16(PlatformParameters::AvailableHeap);
            MessageParser::execute(createStructure);
            createStructure.resetRead();

            Message enablePeriodicReports = Message(HousekeepingService::ServiceType,
                                                    HousekeepingService::EnablePeriodicHousekeepingParametersReport,
                                                    Message::TC, 1);
            enablePeriodicReports.appendUint8(numOfStructIds);
            enablePeriodicReports.appendUint8(structId);
            MessageParser::execute(enablePeriodicReports);
            enablePeriodicReports.resetRead();
        }


        while (true) {
            for (int i = 0; i < numOfStructIds; i++) {
                structId = i;
                housekeeping.housekeepingParametersReport(structId);
            }
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
}
