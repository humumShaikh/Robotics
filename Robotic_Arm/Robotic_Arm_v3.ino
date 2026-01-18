//#include <Arduino.h> //uncomment this line if using platformIo
#include <ESP32Servo.h>			
#include <BluetoothSerial.h>

#define servoPin 32

BluetoothSerial SerialBT;			//object SerialBT of class BluetoothSerial

Servo myservo;						//object myservo of class Servo

int servoPosition = 90;

void setup() {
	// Allow allocation of all timers
  Serial.begin(115200);
  SerialBT.begin("ARM32");
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	myservo.setPeriodHertz(50);
	myservo.attach(servoPin, 1000, 2000);

}

void loop() {

  if (SerialBT.available()) { // Check if Bluetooth data is available
    String data = SerialBT.readString(); // Read the data as a string
    int newPosition = data.toInt(); // Convert data to an integer
    
    // Validate the received position (between 0 and 180 degrees)
    if (newPosition >= 0 && newPosition <= 180) {
      servoPosition = newPosition; // Update the servo position
      myservo.write(servoPosition); // Move the servo to the new position
      Serial.print("Servo moved to: ");
      Serial.println(servoPosition);
    } else {
      Serial.println("Invalid position received. Ignoring.");
    }
  }
}

