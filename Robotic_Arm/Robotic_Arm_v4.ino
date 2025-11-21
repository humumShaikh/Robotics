#include <BluetoothSerial.h>
#include <ESP32Servo.h>

BluetoothSerial SerialBT; // Create a BluetoothSerial object

// Create an array of Servo objects
Servo myServos[6]; 
int servoPins[6] = {32, 33, 25, 26, 27, 13}; // Pins connected to servos
int servoPositions[6] = {90, 90, 90, 90, 90, 90}; // Default positions for all servos

void setup() {
  Serial.begin(115200); // Start Serial Monitor for debugging
  SerialBT.begin("ESP32ServoControl"); // Bluetooth name
  Serial.println("Bluetooth is ready to pair.");

  // Attach each servo to its respective pin
  for (int i = 0; i < 6; i++) {
    myServos[i].attach(servoPins[i]);
    myServos[i].write(servoPositions[i]); // Set initial positions
  }
}

void loop() {
  if (SerialBT.available()) { // Check if Bluetooth data is available
    String data = SerialBT.readString(); // Read the data as a string
    Serial.print("Received: ");
    Serial.println(data);

    // Expect data in the format "servoNumber:position" (e.g., "1:90")
    int separatorIndex = data.indexOf(':');
    if (separatorIndex > 0) {
      int servoNumber = data.substring(0, separatorIndex).toInt(); // Extract servo number
      int newPosition = data.substring(separatorIndex + 1).toInt(); // Extract position

      // Validate servo number and position
      if (servoNumber >= 1 && servoNumber <= 6 && newPosition >= 0 && newPosition <= 180) {
        servoPositions[servoNumber - 1] = newPosition; // Update position array
        myServos[servoNumber - 1].write(newPosition); // Move the specified servo
        Serial.print("Servo ");
        Serial.print(servoNumber);
        Serial.print(" moved to: ");
        Serial.println(newPosition);
      } else {
        Serial.println("Invalid servo number or position. Ignoring.");
      }
    } else {
      Serial.println("Invalid data format. Expected 'servoNumber:position'.");
    }
  }
}
