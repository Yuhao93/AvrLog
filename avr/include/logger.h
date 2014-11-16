#ifndef LOGGER_H
#define LOGGER_H

// Initialize Logger with pins {data_in}, {data_out}, and {data_ready}
// Using {ddr}, {port}, and {pin}.
void logger_init(
    volatile uint8_t* ddr, volatile uint8_t* port, volatile, uint8_t* pin,
    char data_in, char data_out, char data_ready);

// Write the first {length} bytes of the string {message}, blocks until finshes
void logger_msg(const char* message, unsigned int length);

// Write a single bit
void logger_write_bit(bool bit);

#endif
