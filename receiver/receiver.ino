// receiver.ino
#define TX_PIN 17
#define RX_PIN 16
#define BAUD_RATE 115200

char expected[] = "10101";
int indexPos = 0;
bool testFail = false;

void setup() {
  Serial.begin(115200);
  Serial2.begin(BAUD_RATE, SERIAL_8N1, RX_PIN, TX_PIN);
}

void loop() {
  while (Serial2.available()) {
    char c = Serial2.read();

    if (c == '\n') {
      if (!testFail && indexPos == 5) {
        Serial.println("uart toggle test pass");
      } else {
        Serial.println("uart toggle test fail");
      }

      // reset for next cycle
      indexPos = 0;
      testFail = false;
      return;
    }

    if (c != '0' && c != '1') {
      testFail = true;
      continue;
    }

    if (c != expected[indexPos]) {
      testFail = true;
    }

    indexPos++;
  }
}