// sender.ino
#define TX_PIN 17
#define RX_PIN 16
#define BAUD_RATE 115200

const char pattern[] = "10101\n";

void setup() {
  Serial.begin(115200);
  Serial2.begin(BAUD_RATE, SERIAL_8N1, RX_PIN, TX_PIN);
}

void loop() {
  Serial2.print(pattern);
  delay(500);
}