/*
  Using the Qwiic 5-way Navigation switch
  By: Nathan Seidle
  SparkFun Electronics
  Date: October 8th, 2024

  License: This code is public domain but you buy me a drink if you use this and we meet someday (Drinkware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/27576 - Navigation Switch

  This example demonstrates how to use pinMode and digitalRead/Write to read the 5-way navigation switch and turn
  on/off the RGB LED channels.

  Hardware Connections:
  Plug the Qwiic board to your Arduino/ESP32 or other
  Push the joystick-like switch toward a direction
  Watch each LED turn on one-at-a-time
*/

#include <SparkFun_I2C_Expander_Arduino_Library.h> // Click here to get the library: http://librarymanager/All#SparkFun_I2C_Expander_Arduino_Library

SFE_PCA95XX io(PCA95XX_PCA9554); // Create an instance with the PCA9554 IC

int buttonUp = 0;
int buttonDown = 1;
int buttonRight = 2;
int buttonLeft = 3;
int buttonCenter = 4;
int ledBlue = 5;
int ledGreen = 6;
int ledRed = 7;

void setup()
{
  Serial.begin(115200);
  delay(250);
  Serial.println("Qwiic 5-Way Navigation Switch Example");

  Wire.begin();

  // Initialize the PCA95xx, default address = 0x20
  if (io.begin() == false)
  {
    Serial.println("PCA9554 not detected. Please check wiring. Freezing...");
    while (1)
      ;
  }

  io.pinMode(buttonUp, INPUT);
  io.pinMode(buttonDown, INPUT);
  io.pinMode(buttonLeft, INPUT);
  io.pinMode(buttonRight, INPUT);
  io.pinMode(buttonCenter, INPUT);
  io.pinMode(ledRed, OUTPUT);
  io.pinMode(ledGreen, OUTPUT);
  io.pinMode(ledBlue, OUTPUT);

  redOff();
  greenOff();
  blueOff();

  Serial.println("Qwiic 5-Way Navigation Switch online!");
}

void loop()
{
  Serial.print("Button: ");

  if (io.digitalRead(buttonUp) == LOW)
  {
    Serial.print("Up");
    redOn();
    greenOff();
    blueOff();
  }
  else if (io.digitalRead(buttonDown) == LOW)
  {
    Serial.print("Down");
    redOff();
    greenOn();
    blueOff();
  }
  else if (io.digitalRead(buttonLeft) == LOW)
  {
    Serial.print("Left");
    redOn();
    greenOff();
    blueOn();
  }
  else if (io.digitalRead(buttonRight) == LOW)
  {
    Serial.print("Right");
    redOff();
    greenOn();
    blueOn();
  }
  else if (io.digitalRead(buttonCenter) == LOW)
  {
    Serial.print("Center");
    redOn();
    greenOn();
    blueOn();
  }
  else
  {
    Serial.print("None");
    redOff();
    greenOff();
    blueOff();
  }
  Serial.println();

  delay(100);
}

void redOn()
{
  io.digitalWrite(ledRed, LOW);
}
void redOff()
{
  io.digitalWrite(ledRed, HIGH);
}
void greenOn()
{
  io.digitalWrite(ledGreen, LOW);
}
void greenOff()
{
  io.digitalWrite(ledGreen, HIGH);
}
void blueOn()
{
  io.digitalWrite(ledBlue, LOW);
}
void blueOff()
{
  io.digitalWrite(ledBlue, HIGH);
}
