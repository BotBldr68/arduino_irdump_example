# irdebug.h

The irdebug library for the Arduino attempts to provide simple functions to
play with raw infrared signals, like those emitted by remote controls in your
living room.

Please note that this library focuses on raw signals only, if you're looking
for a library with better understanding of many different protocols, you should
take a look at the [Arduino IRremote][1] project.

## Code example

```ino
#include <irdebug.h>

void setup(void) {
  Serial.begin(9600);
  Serial.println("Point a infrared remote controller to your sensor and test it.");
}

unsigned int signal[128];

void loop(void) {
  bool captured;
  captured = irdebug_capture_signal(signal);

  if (captured) {
    Serial.println("A wild signal appeared!");

    irdebug_print_signal(signal);

    Serial.println("Waiting 5s.");
    delay(5000);

    Serial.println("Replaying captured signal.");
    irdebug_send(signal, 38);

    Serial.println("Done.");
  }

}
```

## How to install

1. Copy the `lib/irdebug/` directory to your Arduino's library path, for
	 example: `sudo cp -r lib/irdebug /usr/share/arduino/libraries/`.
2. Include the `irdebug.h` file into your main Arduino code, for example
	 `#include <irdebug.h>`.

## License

> Copyright (c) 2014 José Carlos Nieto, https://menteslibres.net/xiam
>
> Permission is hereby granted, free of charge, to any person obtaining
> a copy of this software and associated documentation files (the
> "Software"), to deal in the Software without restriction, including
> without limitation the rights to use, copy, modify, merge, publish,
> distribute, sublicense, and/or sell copies of the Software, and to
> permit persons to whom the Software is furnished to do so, subject to
> the following conditions:
>
> The above copyright notice and this permission notice shall be
> included in all copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
> EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
> MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
> NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
> LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
> OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
> WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

[1]: https://github.com/shirriff/Arduino-IRremote/

