#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>

// Create Servo Driver for the 16-channel shield
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);

#define SERVO_MIN 150
#define SERVO_MAX 600

// ANGLES FOR THE SERVOS 
int n = 45; // GO TO 160 !!!! max 
int motorAnglesZero[3][7] = {
  {n, n, n, n, n, n, n},   
  {n, n, n, n, n, n, n},   
  {n, n, n, n, n, n, n},     // 0 40 65 99 highest to lowest
};

int white = 99;
int blue = 65;
int yellow = 0;
int red = 40;

// Japan -> Denmark -> Sweden
int motorAnglesJapan[3][7] = {
  {white, white, red, red, red, white, white},   
  {white, white, white, red - 10, white, white, white},   
  {white, white, white, white, white, white, white},     // 0 40 65 99 highest to lowest
};

int motorAnglesDenmark[3][7] = {
  {white, white, white, white, white, white, white},   
  {red + 10, red, white, red, red - 10, red, red - 10},   
  {red - 20, red - 10, white, red, red, red, red},       // 0 40 65 99 highest to lowest
};

int motorAnglesSweden[3][7] = {
  {yellow, yellow, yellow, yellow, yellow, yellow, yellow},   
  {blue, blue, yellow, blue, blue, blue, blue},   
  {blue, blue, yellow, blue, blue, blue, blue},       // 0 40 65 99 highest to lowest
}; 


int angleToPulse(int angle) {
  return map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
}

void setShieldServos(int array[][7], int rows, int cols, Adafruit_PWMServoDriver &driver) {

  int channel = 0;

  for (int row = 0; row < rows; row++) {

    // If we are on row 0, skip the first 5 motors → start at col = 5
    int colStart = (row == 0) ? 5 : 0;

    for (int col = colStart; col < cols; col++) {

      if (channel >= 16)
        return;

      driver.setPWM(channel, 0, angleToPulse(array[row][col]));
      delay(300);

      channel++;
    }
  }
}

void setup() {
  Wire.begin();
  pwm1.begin();
  pwm1.setPWMFreq(50);
}

void loop() {

  setShieldServos(motorAnglesZero, 3, 7, pwm1);

  delay(1000);
}
