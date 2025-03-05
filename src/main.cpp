#include <Arduino.h>
#include <ESP32Servo.h>

#define ESC1_PIN 4
Servo esc1;

#define ESC_MAX 2000
#define ESC_MIN 1000
void escSetup(Servo *esc, int pin);      // this take 3s .please wait
void escMove(Servo *esc, int speed = 0); // speed = 0-100

void setup()
{
    Serial.begin(115200);
    Serial.println("ESC Test");
    Serial.println("Press any key to start...");
    while (!Serial.available())
        ;
    Serial.read();
    Serial.println("Starting...");

    escSetup(&esc1,ESC1_PIN);
}

void loop()
{
    escMove(&esc1, 50);
}

void escSetup(Servo *esc, int pin)
{
    esc->attach(pin);
    esc->setPeriodHertz(50); // 20ms
    esc->writeMicroseconds(ESC_MAX);
    delay(3000);
    esc->writeMicroseconds(ESC_MIN);
    delay(3000);
}

void escMove(Servo *esc, int speed)
{
    int speedValue = map(speed, 0, 100, ESC_MIN, ESC_MAX);
    esc->writeMicroseconds(speedValue);
}