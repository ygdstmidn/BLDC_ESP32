#include <Arduino.h>
#include <ESP32Servo.h>

// 使用可能ピン→13, 12, 14, 27, 26, 25, 33, 32, 15, 2, 0, 4, 5, 18, 19, 21, 22, 23
#define ESC1_PIN 4
Servo esc1; // 一つのescにつき一つ必要です Servo name;(nameは任意の名前)

#define ESC_MAX 2000
#define ESC_MIN 1000
void escSetup(Servo *esc, int pin);      // this take 6s .please wait
void escMove(Servo *esc, int speed = 0); // speed = 0-100

void setup()
{
    Serial.begin(115200);
    Serial.println("ESC Test");
    Serial.println("Press any key to start...");
    while (!Serial.available()) // 何かしらのキーが押されるまで待機します→シリアルモニターから文字を送ることでescがセットアップされます
        ;
    Serial.read();
    Serial.println("Starting...");

    escSetup(&esc1, ESC1_PIN); // escのセットアップ．escSetup(&esc~~, pinName);と書き，pinNameにはescの信号線がつながっているピン番号を入れます．&が必要なので注意
}

void loop()
{
    escMove(&esc1, 50); // escのスピードを変更します．escMove(&esc~~, speed);と書き，speedには0-100の値を入れます．&が必要なので注意
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