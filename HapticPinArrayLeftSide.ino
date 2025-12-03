#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>

// Create Servo Driver for the 16-channel shield
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);

#define SERVO_MIN 150
#define SERVO_MAX 600

// EXTRA ARDUINO DIRECT SERVOS 
Servo extra1;
Servo extra2;
Servo extra3;

// Arduino pins
const int EXTRA_PIN_1 = 9;
const int EXTRA_PIN_2 = 10;
const int EXTRA_PIN_3 = 11;

// ANGLES FOR THE SERVOS 
int n = 150;
int motorAngles[5][4] = {
  {n,  n, n, n},    
  {n,  n, n, n},   
  {n, n, n, n},    
  {n, n, n, n},    // first four rows go to the shield, channels increase left to right, top to bottom
  {180, 180, 180, n}      // col 0–2 go to extra servos, col 3 ignored
};

int angleToPulse(int angle) {
  return map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
}

// Sends the first 16 angles to the shield (channels 0–15)
void setShieldServos(int array[][4], int rows, int cols, Adafruit_PWMServoDriver &driver) {
  int channel = 0;

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {

      if (channel >= 16)
        return;  // only fill the 16 shield channels

      driver.setPWM(channel, 0, angleToPulse(array[row][col]));
      delay(300);
      channel++;
    }
  }
}

// sends the last row, columns 0–2 to the 3 extra servos
void setExtraServos(int array[][4]) {
  delay(500);
  extra1.write(array[4][0]);
  delay(500);
  extra2.write(array[4][1]);
  delay(500);
  extra3.write(array[4][2]);
  delay(500);
}

void setup() {
  Wire.begin();
  pwm1.begin();
  pwm1.setPWMFreq(50);

  // Add 3 extra servos
  extra1.attach(EXTRA_PIN_1);
  extra2.attach(EXTRA_PIN_2);
  extra3.attach(EXTRA_PIN_3);
}

void loop() {

  // First 16 values → shield
  setShieldServos(motorAngles, 5, 4, pwm1);

  delay(1000);

  // Last-row columns 0–2 → direct Arduino servos
  setExtraServos(motorAngles);

  delay(1000);
}

