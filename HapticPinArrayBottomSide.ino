#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>

// Create Servo Driver for the 16-channel shield
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);

#define SERVO_MIN 150
#define SERVO_MAX 600

// ANGLES FOR THE SERVOS 
int n = 0;
int motorAngles[3][7] = {
  {n, n, n, n, n, n, n},   
  {n, n, n, n, n, n, n},   
  {n, n, n, n, n, n, n},    
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

  setShieldServos(motorAngles, 3, 7, pwm1);

  delay(1000);
}
