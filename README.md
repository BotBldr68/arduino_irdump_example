# irdebug.h

The irdebug library for the Arduino attempts to provide simple functions to
play with raw infrared signals, like those emitted by remote controls in your
living room.

By default, the IR sensor's data (like a TSOP 18xx) is expected to be wired to
the Arduino's pin #2; while an IR led is expected to be attached to the pin #3.

Please note that this library focuses on raw signals only, if you're looking
for a library with better understanding of many different protocols, you should
take a look at the [Arduino IRremote][1] project.

## Code example

Let's suppose we have the following chunk of code that makes use of the
`irdebug.h` library.

```c
#include <irdebug.h>

void setup(void) {
  Serial.begin(9600);
  Serial.println("Point an infrared remote controller to your sensor and press any button.");
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

If we press the center button of an Apple Remote controller, we'll see a read
like this in our serial console:

```
Point an infrared remote controller to your sensor and press any button.
A wild signal appeared!
unsigned int signal[] = {
  9140, 4440,
  600, 520,
  616, 1628,
  596, 1628,
  596, 1648,
  600, 496,
  620, 1624,
  620, 1632,
  592, 1632,
  596, 1628,
  596, 1648,
  600, 1624,
  600, 536,
  600, 516,
  600, 520,
  616, 520,
  596, 1628,
  616, 520,
  600, 1624,
  600, 536,
  600, 516,
  600, 536,
  600, 520,
  616, 520,
  596, 520,
  616, 1628,
  600, 1624,
  600, 1624,
  620, 1624,
  604, 500,
  616, 540,
  592, 1632,
  596, 1648,
  600, 0};
Waiting 5s.
Replaying captured signal.
Done.
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

