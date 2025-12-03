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
int n = 0;
int motorAngles[3][7] = {
  {n, n, n, n, n, n, n},    // first two rows go to the shield, channels increase right to left, top to bottom
  {n, n, n, n, n, n, n},   
  {n, n, n, n, n, n, n},    // col 0, 1 from the right go to shield, col 2, 3, 4 from the right go to extra servos (need 180 not 150 for down)  
};

int angleToPulse(int angle) {
  return map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
}

// Sends the first 16 angles to the shield (channels 0–15)
void setShieldServos(int array[][7], int rows, int cols, Adafruit_PWMServoDriver &driver) {
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
void setExtraServos(int array[][7]) {
  delay(500);
  extra1.write(array[2][4]);
  delay(500);
  extra2.write(array[2][3]);
  delay(500);
  extra3.write(array[2][2]);
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
  setShieldServos(motorAngles, 3, 7, pwm1);

  delay(1000);

  // Last-row columns 0–2 → direct Arduino servos
  setExtraServos(motorAngles);

  delay(1000);
}
