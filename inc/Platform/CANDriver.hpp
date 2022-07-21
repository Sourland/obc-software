#ifndef OBC_SOFTWARE_CANDRIVER_H
#define OBC_SOFTWARE_CANDRIVER_H

#include <cstdint>
#include "ECSS_Definitions.hpp"
#include "peripheral/mcan/plib_mcan1.h"

class CANDriver{
public:
    static inline uint8_t mcan1MessageRAM[MCAN1_MESSAGE_RAM_CONFIG_SIZE] __attribute__((aligned (32)));

    /**
     * Array that stores a message that is buffered to be sent
     */
    static inline MCAN_TX_BUFFER txFifo;

    /**
     * Array that stores a received message that is buffered to be processed.
     */
    static inline MCAN_RX_BUFFER rxFifo0;

    /**
     * Possible states for the peripheral, to be used as arguments in the callback functions.
     */
    typedef enum {
        MCANReceive, MCANTransmit,
    } APPStates;

    /**
     * This function logs a successful CAN Bus transmission.
     * It is registered as a callback to be automatically called by Microchip's HAL whenever
     * there is a message transmission on TX FIFO.
     *
     * @param context The state of the peripheral when the function is called.
     */
    static void txFifoCallback(uintptr_t context);

    /**
     * This function initiates a message receipt from the peripheral to the processor.
     * It is registered as a callback to be automatically called by Microchip's HAL whenever
     * there is a message receipt on RX FIFO 0.
     *
     * @param numberOfMessages The number of messages to be received from the peripheral
     * @param context The state of the peripheral when the function is called.
     */
    static void rxFifo0Callback(uint8_t numberOfMessages, uintptr_t context);

    /**
     * This function logs messages that are in the Rx buffer
     * @param numberOfMessages Number of messages to be logged
     * @param rxBuf The RX Buffer that the messages are stored
     * @param rxBufLen The length of the above buffer
     */
    static void printMessage(MCAN_RX_BUFFER rxBuf);

    /**
     * This function decodes the data length code to get the largest expected size of the message.
     *
     * @param dlc The data length code
     * @return The length of the message in bytes
     */
    static uint8_t convertDlcToLength(uint8_t dlc);

    /**
     * This function encodes the body of the message to the smallest data length code that it fits in.
     *
     * @param length The length of the message in bytes
     * @return The data length code
     */
    static uint8_t convertLengthToDlc(uint8_t length);

};

#endif //OBC_SOFTWARE_CANDRIVER_H