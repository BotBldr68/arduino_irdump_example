#define IR_RECV_PIN 2
#define SIGNAL_MAX_LENGTH 9500
#define SIGNAL_MIN_LENGTH 400

unsigned int signal[128];
unsigned int signal_i;
unsigned int signal_l;

unsigned long time;
unsigned long curr;
unsigned long diff;
bool capturing;
bool signal_on;

void setup(void) {
  pinMode(IR_RECV_PIN, INPUT);

  Serial.begin(9600);
  Serial.println("Go and test your IR controller.");

  stop_capture();
}

void next_slot() {
  if (signal_l > SIGNAL_MIN_LENGTH) {
    signal[signal_i] = signal_l;
    signal_l = 0;
    signal_i++;
  }
}

void start_capture() {
  capturing = true;
  signal_l  = 0;
  signal_i  = 0;
}

void stop_capture() {
  capturing = false;
  time = 0;
}

void print_signal() {
  int i;
  Serial.println("int signal[] = {");
  for (i = 0; i < signal_i; i++) {
    if (i%2 == 0) {
      Serial.print("\t");
      Serial.print(signal[i]);
      Serial.print(", ");
    } else {
      Serial.println(signal[i]);
    }
  }
  Serial.println("0}");
}

void loop(void) {
  curr = micros();

  if (time > 0) {
    //signal_on = (!(PIND & (1 << IR_RECV_PIN))); // Fast.
    signal_on = (digitalRead(IR_RECV_PIN) == LOW); // Good enough (and portable).

    diff = curr - time;

    if (capturing == false) {
      // Not capturing.
      if (signal_on) {
        start_capture();
      }
    } else {
      // On capture.
      if (signal_on) {
        if (signal_i%2 != 0) {
          next_slot();
        }
      } else {
        if (signal_i%2 == 0) {
          next_slot();
        }
      }
      signal_l = signal_l + diff;
      if (signal_l > SIGNAL_MAX_LENGTH) {
        stop_capture();
        print_signal();
      }
    }
  }

  time = curr;
}
