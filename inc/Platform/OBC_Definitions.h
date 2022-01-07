#ifndef OBC_SOFTWARE_OBC_DEFINITIONS_H
#define OBC_SOFTWARE_OBC_DEFINITIONS_H

#include <cstdint>

/**
 * @defgroup Definitions of OBC_SOFTWARE Defined Constants
 *
 * This file contains constant definitions that are used in the OBC_SOFTWARE configuration.
 *
 */

/**
 * @brief A switch to control whether the Logger sends its messages over RTT or over UART0
 * 1 is set for RTT, 0 for UART0
 */
inline const bool PreferRTT = 1;

/**
 * @brief Maximum string size for a LogLevel is 9 characters long
 */
inline const uint8_t MaxLogNameSize = 9;

/**
 * @brief TickType_t is a uint32_t number. Its string representation is at most 10 digits long.
 */
inline const uint8_t MaxTickCountStringSize = 10;

/**
 * Stack depth of FreeRTOS tasks.
 * @note in the future after detailed analysis,
 * optimized task stack depths will be evaluated for each task.
 */
inline const uint16_t FreeRTOSTaskStackDepth = 2000;

#endif //OBC_SOFTWARE_OBC_DEFINITIONS_H
