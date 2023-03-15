#include <Arduino.h>

char buf[16] = {0x87, 0xe2, 0xeb, 0xcf, 0x9d, 0xb7, 0xf4, 0x9f, 0x00};
char xor_buf[16] = {0xde, 0xad, 0xbe, 0xef, 0xca, 0xfe, 0xba, 0xbe, 0x00};
char res[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
char test[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void xor_func(char *ptr) {
  for (int i = 0; i < 8; i++) {
    ptr[i] = buf[i] ^ xor_buf[i];
  }
}

void win(char *ptr) {
  char tmp[128];
  sprintf(tmp, "If you want to win you must give me as input the address of res which is: %p", res);
  Serial.println(tmp);
  // Dangerous!
  xor_func(ptr);
  Serial.println(ptr);
}

void setup() {
  Serial.begin(115200);
  delay(5000);
  win(test);
  Serial.println("Well this doesn't count!");
}

void loop() {
  Serial.println("I'm useless, lol.");
  delay(5000);
}
