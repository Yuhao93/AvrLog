#include "logger.h"

#define SET(p,i) ((p) |= (1 << (i)))
#define CLR(p,i) ((p) &= ~(1 << (i)))
#define GET(p,i) ((p) & (1 << (i)))

volatile uint8_t* _logger_port;
volatile uint8_t* _logger_pin;
char _logger_din;
char _logger_dout;
char _logger_dready;

void logger_init(
    volatile uint8_t* ddr, volatile uint8_t* port, volatile uint8_t* pin,
    char data_in, char data_out, char data_ready) {
  CLR(*ddr, data_in);
  SET(*ddr, data_out);
  SET(_logger_ddra, data_ready);
  _logger_port = port;
  _logger_pin = pin;
  _logger_din = data_in;
  _logger_dout = data_out;
  _logger_dready = data_ready;
}

void logger_msg(const char* message, unsigned int length) {
  // write every bit of every character
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < 8; j++) {
      logger_write_bit((message[i] & (1 << (7 - j))) != 0);
    }
  }
}

void logger_write_bit(bool bit) {
  // Signal that there is a bit to be written
  SET(*_logger_port, _logger_dready);
  // Wait until acknowledged
  while (GET(*_logger_pin, _logger_din) == 0);
  // Write the bit
  if (bit) {
    SET(*_logger_port, _logger_dout);
  } else {
    CLR(*_logger_port, _logger_dout);
  }
  // Signal that you're done writing
  CLR(*_logger_port, _logger_dout);
  // Wait until acknowledged that bit has been read
  while (GET(*_logger_pin, _logger_din) != 0);
}
