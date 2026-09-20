/*
 * UARTBuffer.hpp
 *
 *  Created on: Sep 20, 2026
 *      Author: mehdi
 */

#ifndef CUSTOMCLASSES_INC_UARTBUFFER_HPP_
#define CUSTOMCLASSES_INC_UARTBUFFER_HPP_
#include <cstdint>
class UARTBuffer {
public:
    static constexpr uint16_t SIZE = 128;   // power of two for cheap masking

    // ---- called from ISR ----
    void push(uint8_t b)
    {
        uint16_t next = (head + 1) & (SIZE - 1);
        if (next != tail) {          // drop on overflow
            buf[head] = b;
            head = next;
        }
    }

    // ---- called from main loop ----
    bool pop(uint8_t& b)
    {
        if (head == tail) return false;
        b = buf[tail];
        tail = (tail + 1) & (SIZE - 1);
        return true;
    }

    bool empty() const { return head == tail; }

private:
    volatile uint16_t head = 0;
    volatile uint16_t tail = 0;
    uint8_t buf[SIZE];
};

#endif /* CUSTOMCLASSES_INC_UARTBUFFER_HPP_ */
