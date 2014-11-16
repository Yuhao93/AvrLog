#include <wiringPi.h>
#include <stdio.h>

// Rpi gpio ports
#define DOUT 1
#define DIN 2
#define READY 3

// Acts as the STDIO for a microcontroller
// 1-way receiver protocol that uses 3 pins
int main() {
  // Initialize
  wiringPiSetup();

  // Pin used to tell the microcontroller that it is ready for data
  pinMode(DOUT, OUTPUT);
  // Input data
  pinMode(DIN, INPUT);
  // Signal that is fired when the input data is ready to be read
  pinMode(READY, INPUT);

  // Initialize to low
  digitalWrite(DOUT, LOW);

  // Prevent stdout from buffering data
  setbuf(stdout, NULL);
  char ch = 0;

  while (true) {
    // Read a byte
    for (int i = 0; i < 8; i++) {
      // Wait for the data ready flag
      while (digitalRead(READY) != HIGH);
      // Acknowledge that data is ready, ready to read
      digitalWrite(DOUT, HIGH);
      // Wait until the data is written
      while (digitalRead(READY) != LOW);
      // Read data
      char d = digitalRead(DIN) == HIGH ? 1 : 0;
      ch = (ch << 1) | d;
      // Signal that data has been read
      digitalWrite(DOUT, LOW);
    }
    // Print out the byte
    printf("%c", ch);
    ch = 0;
  }
}
