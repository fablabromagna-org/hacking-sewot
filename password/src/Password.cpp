#include <Arduino.h>

#define BUF_SIZE 16
#define CHARS_SIZE 25
#define DELAY 100

//#define DBG

char password[BUF_SIZE];
char buf[BUF_SIZE] = {0};
char chars[] = {"QWERTYUIOPASDFGHJKLZXCVBNM"};
String input_password;
char buffer[64];

void init_password() {
  for (int i = 0; i < BUF_SIZE - 1; i++) {
    password[i] = chars[random(0, CHARS_SIZE)];
    delay(random(0, DELAY));
  }
  password[BUF_SIZE] = '\0';
}

void setup()
{
  Serial.begin(115200);
  randomSeed(analogRead(0));
  init_password();
}

void loop()
{
#ifdef DBG
  sprintf(buffer, "Password: %p\n", &password);
  Serial.print(buffer);
  sprintf(buffer, "Buf: %p\n", &buf);
  Serial.print(buffer);
  Serial.println(password);
#endif

  Serial.print("\nEnter the password: ");

  while(!Serial.available()) {
    delay(1000);
  }

  input_password = Serial.readStringUntil('\n');

  // Correct: input_password.toCharArray(buf, BUF_SIZE);
  for (int x = 0; x < input_password.length() && x < BUF_SIZE; x++) {
    buf[x] = input_password[x];
  }

  Serial.print("\nINPUT: ");
  Serial.println(buf);

  if(strncmp(buf, password, BUF_SIZE - 1)) {
    Serial.println("\nWrong Password");
  }
  else {
    Serial.println("\nCorrect Password, YOU WIN!");
  }
}
