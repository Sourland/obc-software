#include "FreeRTOSTasks/StatisticsReportingTask.hpp"

void StatisticsReportingTask::execute() {
    auto &parameterStatistics = Services.parameterStatistics;
//    todo: while (parameterStatistics.periodicStatisticsReportingStatus) {}

    while (true) {
        Message request = Message(ParameterStatisticsService::ServiceType,
                                  ParameterStatisticsService::MessageType::ReportParameterStatistics,
                                  Message::PacketType::TC, 1);
        request.appendBoolean(false);
        MessageParser::execute(request);
        vTaskDelay(pdMS_TO_TICKS(delayMs));
    }
}