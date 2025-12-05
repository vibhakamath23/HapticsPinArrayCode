#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>

// Create Servo Driver for the 16-channel shield
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);

#define SERVO_MIN 150
#define SERVO_MAX 600

#define ZERO 0
#define JAP 1
#define DEN 2
#define SWE 3
//Choose
#define FLAG_NAME 1


// ANGLES FOR THE SERVOS 
int n = 0; // GO TO 160 !!!! max 
int motorAnglesZero[3][7] = {
  {n, n, n, n, n, n, n},   
  {n, n, n, n, n, n, n},   
  {n, n, n, n, n, n, n},
};

int white = 99;
int blue = 65;
int yellow = 0;
int red = 40;

// Japan -> Denmark -> Sweden
int motorAnglesJapan[3][7] = {
  {white, white, red, red, red, white, white},   
  {white, white, white, red - 10, white, white, white},   
  {white, white, white, white, white, white, white},
};

int motorAnglesDenmark[3][7] = {
  {white, white, white, white, white, white, white},   
  {red + 10, red, white, red, red - 10, red, red - 10},   
  {red - 20, red - 10, white, red, red, red, red},
};

int motorAnglesSweden[3][7] = {
  {yellow, yellow, yellow, yellow, yellow, yellow, yellow},   
  {blue, blue, yellow, blue, blue, blue, blue},   
  {blue, blue, yellow, blue, blue, blue, blue},
}; 

int angleToPulse(int angle) {
  return map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
}

void setShieldServos(int array[][7], int rows, int cols, Adafruit_PWMServoDriver &driver) {
  int channel = 0;

  for (int row = 0; row < rows; row++) {

    int colStart = (row == 0) ? 5 : 0;

    for (int col = colStart; col < cols; col++) {

      if (channel >= 16)
        return;

      driver.setPWM(channel, 0, angleToPulse(array[row][col]));
      delay(400);

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

  // Pointer to the matrix we want to use
  int (*selectedMatrix)[7];

  // Pick based on FLAG_NAME
  switch (FLAG_NAME) {
    case ZERO:
      selectedMatrix = motorAnglesZero;
      break;
    case JAP:
      selectedMatrix = motorAnglesJapan;
      break;
    case DEN:
      selectedMatrix = motorAnglesDenmark;
      break;
    case SWE:
      selectedMatrix = motorAnglesSweden;
      break;
    default:
      selectedMatrix = motorAnglesZero; // fallback
  }

  // Use selected matrix
  setShieldServos(selectedMatrix, 3, 7, pwm1);

  delay(1000);
}

