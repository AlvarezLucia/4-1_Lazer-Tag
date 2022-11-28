#include <SPI.h>
#include <Wire.h>
#include <FastLED.h>
#include <avr/power.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#define PIN 10
#define NUMPIXELS 3
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

int ldr1;
int ldr2;
int ldr3;
int ldr4;
int ldr5;
int ldr6;
byte button;

unsigned long minutes;
unsigned long prevMinutes;

int ran;
int points;
int timeLeft = 60;
int timeLeft2 = 10;
int state = 0;
int a;

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(9, INPUT);
  pixels.begin();
  pixels.clear();
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.clearDisplay();

}

void loop() {

  minutes = millis();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  button = digitalRead(9);

  if (state == 0)
  {
    pixels.clear();
    pixels.show();
    timeLeft = 60;
    display.setCursor(30, 16);
    display.setTextSize(1);
    display.println(F("PRESS BUTTON"));
    display.display();
  }

  if (button == LOW)
  {
    delay(50);
    pixels.clear();
    pixels.show();
    display.clearDisplay();
    display.display();
    timeLeft = 60;
    points = 0;

    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 10);
    display.println(F("GET READY"));
    display.display();
    delay(3000);
    display.clearDisplay();

    for (a = 10; a > 0; a--)
    {
      display.clearDisplay();
      display.setCursor(60, 10);
      display.println(timeLeft2);
      display.display();
      timeLeft2--;
      delay(1000);
    }
    timeLeft2 = 10;
    display.setTextSize(1);
    state = 1;
  }

  if (state == 1)
  {
    game();
  }

  if (timeLeft == 0)
  {
    pixels.clear();
    pixels.show();
    display.clearDisplay();
    display.setCursor(40, 10);
    display.println(F("GAME OVER"));
    display.display();
    delay(3000);
    display.clearDisplay();
    display.setCursor(40, 10);
    display.println(F("POINTS:    "));
    display.setCursor(100, 10);
    display.println(points);
    display.display();
    delay(3000);
    display.clearDisplay();
    state = 0;
  }
  delay(20);
}

void game()
{
  if (minutes - prevMinutes >= 1000)
  {
    ran = random(1, 4);
    display.clearDisplay();
    display.setCursor(10, 0);
    display.println(F("points:"));
    display.setCursor(100, 0);
    display.println(points);
    display.setCursor(10, 20);
    display.println(F("time:"));
    display.setCursor(100, 20);
    display.println(timeLeft);
    display.display();
    timeLeft--;
    prevMinutes = minutes;
  }

  if (ran == 1)
  {
    pixels.setPixelColor(0, pixels.Color(30, 0, 0));
    pixels.show();
    reading();
    LDR12();
  }

  if (ran == 2)
  {
    pixels.setPixelColor(1, pixels.Color(30, 0, 0));
    pixels.show();
    reading();
    LDR34();
  }

  if (ran == 3)
  {
    pixels.setPixelColor(2, pixels.Color(30, 0, 0));
    pixels.show();
    reading();
    LDR56;
  }
  display.clearDisplay();
  pixels.clear();

}

void reading()
{
  ldr1 = analogRead(A0);
  ldr2 = analogRead(A1);
  ldr3 = analogRead(A2);
  ldr4 = analogRead(A3);
  ldr5 = analogRead(A6);
  ldr6 = analogRead(A7);
  delay(50);
}

void LDR12()
{
  if (ldr1 > 800)
  {
    points = points + 30;
  }

  if (ldr2 > 800)
  {
    points = points + 30;
  }

  if (ldr3 > 800)
  {
    points = points + 10;
  }
  if (ldr4 > 800)
  {
    points = points + 10;
  }

  if (ldr5 > 800)
  {
    points = points + 5;
  }

  if (ldr6 > 800)
  {
    points = points + 5;
  }
}

void LDR34()
{
  if (ldr1 > 800)
  {
    points = points + 5;
  }

  if (ldr2 > 800)
  {
    points = points + 10;
  }

  if (ldr3 > 800)
  {
    points = points + 30;
  }
  if (ldr4 > 800)
  {
    points = points + 30;
  }

  if (ldr5 > 800)
  {
    points = points + 10;
  }

  if (ldr6 > 800)
  {
    points = points + 5;
  }
}

void LDR56()
{
  if (ldr1 > 800)
  {
    points = points + 5;
  }

  if (ldr2 > 800)
  {
    points = points + 5;
  }

  if (ldr3 > 800)
  {
    points = points + 10;
  }
  if (ldr4 > 800)
  {
    points = points + 10;
  }

  if (ldr5 > 800)
  {
    points = points + 30;
  }

  if (ldr6 > 800)
  {
    points = points + 30;
  }
}

void serial()
{
  Serial.print("S1: ");
  Serial.println(ldr1);
  Serial.print("S2: ");
  Serial.println(ldr2);
  Serial.print("S3: ");
  Serial.println(ldr3);
  Serial.print("S4: ");
  Serial.println(ldr4);
  Serial.print("S5: ");
  Serial.println(ldr5);
  Serial.print("S6: ");
  Serial.println(ldr6);
  Serial.print("button: ");
  Serial.println(button);

  delay(500);
}
