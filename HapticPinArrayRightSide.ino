#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create Servo Driver for the 16-channel shield
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);

#define SERVO_MIN 150
#define SERVO_MAX 600

// ANGLES FOR THE SERVOS 
int motorAngles2[5][4] = {
  {10, 20, 30, 40},        // [0][0] skipped
  {50, 60, 70, 80},        // [1][0] skipped
  {90, 100, 110, 120},     // [2][0] skipped
  {130, 140, 150, 160},    // [3][0] skipped
  {170, 180, 190, 200}     // full row used
};

int angleToPulse(int angle) {
  return map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
}

void setShield2Servos(int array[][4], Adafruit_PWMServoDriver &driver) {

  int channel = 0;

  for (int row = 0; row < 5; row++) {
    for (int col = 0; col < 4; col++) {

      // Skip [0..3][0] - covered by other arduino
      if (row < 4 && col == 0) {
        continue;
      }

      if (channel >= 16) {
        return; // shield is full
      }

      int angle = array[row][col];

      driver.setPWM(channel, 0, angleToPulse(angle));
      delay(40);

      channel++;
    }
  }
}

void setup() {
  Wire.begin();
  pwm2.begin();
  pwm2.setPWMFreq(50);
}

void loop() {

  // Send processed 16 values to shield #2
  setShield2Servos(motorAngles2, pwm2);

  delay(800);
}
