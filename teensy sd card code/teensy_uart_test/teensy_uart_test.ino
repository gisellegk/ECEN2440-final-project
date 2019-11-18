#define HWSERIAL Serial1

uint8_t i;
void setup() {
  HWSERIAL.begin(9600);
  i = 0;
}

void loop() {
  HWSERIAL.write(i);
  i++;
  delay(50);
}
