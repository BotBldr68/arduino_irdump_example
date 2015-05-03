// Copyright (c) 2014-2015 José Carlos Nieto, https://menteslibres.net/xiam
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <IRDump.h>

#define PIN_IR_INPUT 2

IRDump *irdumper;
unsigned int *signal;

void printSignal(unsigned int *signal) {
  unsigned int i;
  Serial.println("/* Begin signal. */");
  Serial.println("unsigned int signal[] = {");
  for (i = 0; signal[i] > 0; i++) {
    if (i%2 == 0) {
      Serial.print("\t");
      Serial.print(signal[i]);
      Serial.print(", ");
    } else {
      Serial.print(signal[i]);
      Serial.println(",");
    }
  }
  Serial.println("0\r\n};");
  Serial.print("/* End of signal (");
  Serial.print(i);
  Serial.println(" pulses) */");
}

void setup(void) {
  Serial.begin(115200);
  Serial.println("Point an infrared remote controller to your sensor and press any button.");

  signal = (unsigned int *)malloc(sizeof(unsigned int)*128);
  irdumper = new IRDump();

  pinMode(PIN_IR_INPUT, INPUT);
}

void loop(void) {

  bool captured;

  // Tuned to capture signals from the Apple TV Remote.
  captured = irdumper->Capture(PIN_IR_INPUT, &signal, 128, 9200);

  if (captured) {
    printSignal(signal);
  }

}
