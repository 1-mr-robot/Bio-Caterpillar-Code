
// Include the required Wire library for I2C
#include <Wire.h>
#include <Servo.h>

// defines pins numbers
const int stepPin = 4;
const int dirPin = 3;

int dc11 = 7;
int dc12 = 11;
int dc21 = 12;
int dc22 = 13;

Servo servoLeft, servoRight; // create servo objects to control a servo
int vall = 45; //120
int valr = 135; //60
int x;
int a;


void setup() {
  // Start the I2C Bus as Master
  Wire.begin(); //include no input arguments to start arduino as master on i2c line
  Serial.begin(9600);

  // Sets the two pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  servoLeft.attach(8);
  servoRight.attach(9);

  servoLeft.write(vall);                  // sets the servo position
  servoRight.write(valr);

}

void loop() {

  Wire.requestFrom(9, 1);
  if (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);

    if (c == '6')//left
    {
      //      x = Wire.requestFrom(9, 1);
      //      if (x < 300 || x > 500){
      digitalWrite(dc11, LOW);
      digitalWrite(dc12, HIGH);
      digitalWrite(dc21, HIGH);
      digitalWrite(dc22, LOW);
      //      }
    }

    if (c == '8')//back
    {
      //      x = Wire.requestFrom(9, 1);
      //      if (x < 300 || x > 500){
      digitalWrite(dc11, HIGH);
      digitalWrite(dc12, LOW);
      digitalWrite(dc21, HIGH);
      digitalWrite(dc22, LOW);
      delay (1000);
      //      }
      //      c = '2';
    }

    if (c == '2')//forward
    {
      //      x = Wire.requestFrom(9, 1);
      //      if (x < 300 || x > 500){
      digitalWrite(dc11, LOW); // sets pin 3 HIGH
      digitalWrite(dc12, HIGH);
      digitalWrite(dc21, LOW); // sets pin 3 HIGH
      digitalWrite(dc22, HIGH);

      delay (1000);
      //      }
      c = '2';
    }

    if (c == '4')//right
    {
      //      x = Wire.requestFrom(9, 1);
      //      if (x < 300 || x > 500){
      digitalWrite(dc11, HIGH);
      digitalWrite(dc12, LOW);
      digitalWrite(dc21, LOW);
      digitalWrite(dc22, HIGH);
      //      }
    }

    else if (c == '5')
    {
      //      x = Wire.requestFrom(9, 1);
      //      if (x < 300 || x > 500){
      digitalWrite(dc11, LOW); // sets pin 3 HIGH
      digitalWrite(dc12, LOW);
      digitalWrite(dc21, LOW); // sets pin 3 HIGH
      digitalWrite(dc22, LOW);
      //      }
    }
    else if (c =='n'){
    //starting position for walking
     vall = 45; //120
     valr = 135;//60
     servoRight.write(valr);
     servoLeft.write(vall);
    }
    else if(c =='l'){
    //starting position for climbing
     vall = 120; 
     valr = 60;
     servoRight.write(valr);
     servoLeft.write(vall);
  }
    else if (c == 'u') //function to MOVE positively
    {
      //      Wire.beginTransmission(9);
      //      Wire.write(1);
      //      //Wire.requestFrom(9,4);
      //      if (Wire.available())
      //      {
      //        a = Wire.read();
      //        Wire.endTransmission();
      //        Serial.print(a);
      //      }
      //      if (a < 100)
      {
        digitalWrite(dirPin, LOW); // positive direction
        for (int s = 0; s < 8000; s++)
        {
          // Makes 200 pulses for making one full cycle rotation
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(300);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(700);
        }
      }
    }
    else if (c == 'd') //this is for negative steps
    {
      digitalWrite(dirPin, HIGH); //negative direction
      //      // Makes 400 pulses for making two full cycle rotation
      for (int s = 0; s < 8000; s++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(300);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(700);
      }
    }
    else if (c == 'p') //btm clamped
    {
      for (; valr >= 45 && vall <= 120; valr--, vall++) //ensure and put clamp down
      {
        servoRight.write(valr);
        servoLeft.write(vall);
        delay(15);                           // waits for the servo to get there
      }
    }
    else if (c == 'b')
    {
      for (; vall >= 45 && valr <= 135; vall--, valr++) //ensure and unclamp
      {
        servoRight.write(valr);
        servoLeft.write(vall);
        delay(15);                           // waits for the servo to get there
      }
    }
    else if (c == 'f')
    {
      delay(1000);
      digitalWrite(dirPin, HIGH); //negative direction contract,starting state open
      //      // Makes 400 pulses for making two full cycle rotation
      for (int s = 0; s < 8000; s++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(300);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(700);
      }
      valr=100;
      vall=70;
      servoRight.write(valr);
      servoLeft.write(vall);
      digitalWrite(dirPin, LOW); // positive direction
      for (int s = 0; s < 8000; s++)
      {
        // Makes 200 pulses for making one full cycle rotation
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(300);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(700);
      }
      for (; vall >= 45 && valr <= 135; vall--, valr++) //ensure and unclamp
      {
        servoRight.write(valr);
        servoLeft.write(vall);
        delay(15);                           // waits for the servo to get there
      }
    }
    else if (c == 'r')
    {

      valr =100;
      vall=70;
      servoRight.write(valr);
      servoLeft.write(vall);
      digitalWrite(dirPin, HIGH); //negative direction
      //      // Makes 400 pulses for making two full cycle rotation
      for (int s = 0; s < 8000; s++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(300);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(700);
      }
      for (; vall >= 45 && valr <= 135; vall--, valr++) //ensure and unclamp
      {
        servoRight.write(valr);
        servoLeft.write(vall);
        delay(15);                           // waits for the servo to get there
      }
      digitalWrite(dirPin, LOW); // positive direction
      for (int s = 0; s < 8000; s++)
      {
        // Makes 200 pulses for making one full cycle rotation
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(300);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(700);
      }
      
    }
    else if (c == 'g'){
        delay(1000);
        digitalWrite(dirPin, LOW); // positive direction
        for (int s = 0; s < 8000; s++)
        {
          // Makes 200 pulses for making one full cycle rotation
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(300);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(700);
        }
        delay(2000);
        for (; vall >= 45 && valr <= 135; vall--, valr++) //ensure and unclamp
      {
        servoRight.write(valr);
        servoLeft.write(vall);
        delay(15);                           // waits for the servo to get there
      }
       digitalWrite(dirPin, HIGH); //negative direction
      //      // Makes 400 pulses for making two full cycle rotation
      for (int s = 0; s < 8000; s++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(300);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(700);
      }
      for (; valr >= 45 && vall <= 120; valr--, vall++) //ensure and put clamp down
      {
        servoRight.write(valr);
        servoLeft.write(vall);
        delay(15);                           // waits for the servo to get there
      }
    }
    else if (c == 'e'){
       for (; vall >= 45 && valr <= 135; vall--, valr++) //ensure and unclamp
      {
        servoRight.write(valr);
        servoLeft.write(vall);
        delay(15);                           // waits for the servo to get there
      }
        digitalWrite(dirPin, LOW); // positive direction
        for (int s = 0; s < 8000; s++)
        {
          // Makes 200 pulses for making one full cycle rotation
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(300);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(700);
        }
       for (; valr >= 45 && vall <= 120; valr--, vall++) //ensure and put clamp down
      {
        servoRight.write(valr);
        servoLeft.write(vall);
        delay(15);                           // waits for the servo to get there
      }
      delay(1000);
      digitalWrite(dirPin, HIGH); //negative direction
      //      // Makes 400 pulses for making two full cycle rotation
      for (int s = 0; s < 8000; s++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(300);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(700);
    }
  }
}
}
