#include <SoftwareSerial.h>
#include <Servo.h>
#include <Wire.h>

#define RxD 2
#define TxD 3

char recvChar;
int sensorPin = A2;
int sensorState = 0; // initial start value of the sensor status
int vall = 45; //120
int valr = 135;//60
char sendState[4];

Servo ServoLeft, ServoRight; // create servo object to control a servo

SoftwareSerial blueToothSerial(RxD, TxD);             //bluetooth device acts as a serial communication device
//receive and transmit with respect to the Arduino board

void setup() {
  pinMode(sensorPin, INPUT);   // define pin as input
  Wire.begin(9); // Start the I2C Bus as Slave on address 9
  //  Wire.onRequest(requestprox); // Attach a function to trigger when a request is received
  Wire.onRequest(requestEvent);
  //Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  pinMode(RxD, INPUT);                              //set mode of receive pin (from bluetooth)
  pinMode(TxD, OUTPUT);                             //set mode of transmit pin (to bluetooth)
  blueToothSerial.begin(9600);                      //start the bluetooth serial "port"
  ServoLeft.attach(7);
  ServoRight.attach(9);

  ServoLeft.write(vall);                  // sets the initial servo position
  ServoRight.write(valr);

}

void loop()
{

  sensorState = analogRead(sensorPin);    // read the input pin
  if (recvChar == 'n'){
    //starting position for walking
     vall = 45; //120
     valr = 135;//60
     ServoRight.write(valr);
     ServoLeft.write(vall);
  }
  else if (recvChar == 'l'){
    //starting position for climbing
     vall = 120; 
     valr = 60;
     ServoRight.write(valr);
     ServoLeft.write(vall);
  }
  else if (recvChar == 'c')
  {
    for (; valr >= 55 && vall <= 120; valr--, vall++) //ensure and put clamp down
    {
      ServoRight.write(valr);
      ServoLeft.write(vall);
      delay(15);                           // waits for the servo to get there
    }
  }
  else if (recvChar == 't')
  {
    for (; vall >= 45 && valr <= 135; vall--, valr++) //ensure and put clamp up
    {
      ServoRight.write(valr);
      ServoLeft.write(vall);
      delay(15);                           // waits for the servo to get there
    }
  }
  else if (recvChar == 'f')
  {
    ServoRight.write(110);
    ServoLeft.write(70);
    delay(8500);
    for (; vall >= 45 && valr <= 135; vall--, valr++) //ensure and put clamp up
    {
      ServoRight.write(valr);
      ServoLeft.write(vall);
      delay(15);                           // waits for the servo to get there
    }
  }
  else if (recvChar == 'r')
  {
      delay(9000);
      ServoRight.write(110);
      ServoLeft.write(70);
      delay(8500);
      for (; vall >= 45 && valr <= 135; vall--, valr++) //ensure and put clamp up
    {
      ServoRight.write(valr);
      ServoLeft.write(vall);
      delay(15);                           // waits for the servo to get there
    }
  }
  else if (recvChar == 'g'){
    //climb up
     for (; vall >= 45 && valr <= 135; vall--, valr++) //ensure and put clamp up
    {
      ServoRight.write(valr);
      ServoLeft.write(vall);
      delay(15);                           // waits for the servo to get there
    }
    delay(8500);
    for (; valr >= 55 && vall <= 120; valr--, vall++) //ensure and put clamp down
    {
      ServoRight.write(valr);
      ServoLeft.write(vall);
      delay(15);                           // waits for the servo to get there
    }
    delay(8500);
    for (; valr >= 55 && vall <= 120; valr--, vall++) //ensure and put clamp down
    {
      ServoRight.write(valr);
      ServoLeft.write(vall);
      delay(15);                           // waits for the servo to get there
    }
  }
  else if (c == 'e'){
     delay (9500);
     for (; vall >= 45 && valr <= 135; vall--, valr++) //ensure and put clamp up
    {
      ServoRight.write(valr);
      ServoLeft.write(vall);
      delay(15);                           // waits for the servo to get there
    }
    delay(8500);
    for (; valr >= 55 && vall <= 120; valr--, vall++) //ensure and put clamp down
    {
      ServoRight.write(valr);
      ServoLeft.write(vall);
      delay(15);                           // waits for the servo to get there
    }
  }
}
//void requestprox() {
//  sensorState = digitalRead(sensorPin);    // read the digital input pin and store status value
//  Wire.write(sensorState);
//}
void requestEvent() {
  if (blueToothSerial.available())                    //if data is available from the bluetooth device
  {
    recvChar = blueToothSerial.read();              //store character received
    Serial.print(recvChar);  //display character received on the serial monitor
    if (sensorState > 100 && recvChar == 'u')
      recvChar = 0;
    Wire.write(recvChar);
  }
}

//void receiveEvent(int bytes){
//  sensorState = analogRead(sensorPin);    // read the input pin
//  int i;
//for (i=0; i<3; i++) sendState[i] =
// itoa(sensorState,sendState,10);
// Wire.write(sendState);
// Wire.write(sensorState,sizeof(sensorState));
// Serial.print(sensorState);
//}




