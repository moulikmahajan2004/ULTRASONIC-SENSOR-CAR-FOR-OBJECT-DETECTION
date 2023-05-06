#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// I2C LCD ADDRESS  , CHRACTERS AND THE LINES
LiquidCrystal_I2C lcd(0x27, 16, 2);

// INTIALIZING THE MOTOR WITH THE GIVEN PINS
int m1 = 4;
int m2 = 5;
int m3 = 6;
int m4 = 7;

// ULTRASONIC SENSOR TRIGGERING AND ECHO PIN
int trigPin = 8;
int echoPin = 9;
// A VARIABLE INPUT CHAR TYPE
char input;

void setup() {
  // DEFINING THE MOTOR PIN AND THE OUTPUT
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);

  //THE ENA AND ENB
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  //ECHO AND TRIGGERING PIN
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
  lcd.begin();
}

void loop() {
  //DEFINGIN THE POTENTIOMETER PIN AS ANALOG READ
  int potentiometer = analogRead(A0);
  // A INT TYPE VARIABLE WHICH DIVIDE THE POTENTIOMETER ANALOG VALUE BY 4
  int potent = potentiometer / 4;

  // INPUT THE POTENT VALUE TO MOTORDRIVER ENA AND ENB
  analogWrite(10, potent);
  analogWrite(11, potent);

  // HERE INTYPE VARIBALE IS CREATED WHICH IS DISTANCE WHOSE VALUE IS FROM THE GET DISTANCE FUNCTION
  int distance = getDistance();
  // IF THE VALUE OF OB OBJECT IS 25 FROM THE CAR OR PROTOTYPE IT WILL TRIGGER STOP, BACKWARD, STOP AND IT ALSO PRINT THE OBSTACLE DETECTED
  if (distance <= 25) {
    stop();
    lcd.clear();
    lcd.print("Obstacle detected");
    backward();
    delay(500);
    stop();
  } 
  // IF THE BLUETOOTH AVAILABLE THEN INPUT WILL READ THE CHRACTER VALUE FROM THE BLUETOOTHE WHEN A PARTICULAR BUTTON IS PRESSED AND PERFORM THE SUITABLE FUNCTION 
  else if (Serial.available()) {
    // wait a bit for the entire message to arrive
    input = Serial.read();
    // clear the screen
    lcd.clear();
    switch (input) {
      case 'F':
        forward();
        lcd.print("Forward");
        break;
      case 'R':
        right();
        lcd.print("right");
        break;
      case 'L':
        left();
        lcd.print("Left");
        break;
      case 'G':
        backward();
        lcd.print("Backward");
        break;
      case 'S':
        stop();
        lcd.print("Stop");
        break;
    }
  }
}

// RIGHT FUNCTION
void right() {
  digitalWrite(m2, LOW);
  digitalWrite(m1, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, HIGH);
}
//STOP FUNCTION
void stop() {
  digitalWrite(m2, LOW);
  digitalWrite(m1, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
}
//LEFT FUNCTION
void left() {
  digitalWrite(m2, LOW);
  digitalWrite(m1, HIGH);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
}
//FORWARD FUNCTION
void forward() {
  digitalWrite(m2, HIGH);
  digitalWrite(m1, LOW);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);
}
//BACKWARD FUNCTION
void backward() {
  digitalWrite(m2, LOW);
  digitalWrite(m1, HIGH);
  digitalWrite(m3, LOW);
  digitalWrite(m4, HIGH);
}


// This is a function in Arduino code for measuring distance using an ultrasonic sensor. Here's how it works:
// ----->  The function starts by setting the "trigPin" to LOW and delaying for 2 microseconds. This is done to ensure that the sensor is in a stable state before sending the trigger signal.
// ----->Then the "trigPin" is set to HIGH for 10 microseconds and then back to LOW. This sends a trigger signal to the ultrasonic sensor.
// ----->The "pulseIn" function is used to measure the duration of the echo signal, which is the time it takes for the ultrasonic wave to bounce off an object and return to the sensor.
// ----->The duration is then multiplied by 0.034 and divided by 2 to convert it to distance in centimeters. The factor of 0.034 is used because the speed of sound in air is about 340 meters per second, which is equivalent to 0.034 centimeters per microsecond.
// ----->The calculated distance is returned as an integer.
// ----->It's worth noting that the accuracy of the distance measurement depends on various factors such as the speed of sound, temperature, and humidity. Additionally, the maximum distance that can be measured with this method is typically around 4-5 meters, beyond which the sensor may not receive a strong enough echo signal to detect.


int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}
