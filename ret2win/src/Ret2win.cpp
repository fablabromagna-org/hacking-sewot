#include <Arduino.h>

#define BUF_SIZE 2048
#define PARROT_SIZE 64

char buf[BUF_SIZE] = {0};
String input;

void win()
{
  Serial.println("YOU WIN!");
}

void setup()
{
  Serial.begin(115200);
  win();
}

void parrot_3()
{
  char parrot[PARROT_SIZE] = {0};

  input = Serial.readStringUntil('\n');

  // Correct: input_password.toCharArray(buf, BUF_SIZE);
  for (int x = 0; x < input.length(); x++) {
    buf[x] = input[x];
  }

  Serial.print("\n*CRA CRA* ");
  sprintf(parrot, buf);
  Serial.print(parrot);
  for (int x = 0; x < input.length(); x++) {
    parrot[x] = input[x];
  }
  Serial.println(" *CRA CRA*");
}

void parrot_2()
{
  while(!Serial.available()) {
    delay(1000);
  }
  parrot_3();
}

void parrot_1()
{
  Serial.print("\nI'm a parrot! *CRA CRA*! I repeat things!\nTell me something: ");
  parrot_2();
}

void loop()
{
  parrot_1();
}
