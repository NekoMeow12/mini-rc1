#include <SoftwareSerial.h>

// Define custom RX and TX pins for Bluetooth communication
#define BT_RX_PIN 2
#define BT_TX_PIN 3

// Define pins for motor control
#define LEFT_FORWARD 13
#define LEFT_REVERSE 12
#define RIGHT_FORWARD 11
#define RIGHT_REVERSE 10

// Define LED pin
#define LED_PIN 9

SoftwareSerial BTSerial(BT_RX_PIN, BT_TX_PIN); // RX, TX (swapped pins for Bluetooth)

char t; // Variable to store received command

void setup() {
  // Set motor control pins and LED pin as outputs
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(LEFT_REVERSE, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(RIGHT_REVERSE, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  
  // Begin serial communication for debugging
  Serial.begin(9600);
  
  // Begin Bluetooth serial communication
  BTSerial.begin(9600);
}

void loop() {
  // Check if data is available on Bluetooth serial
  if (BTSerial.available()) {
    // Read the incoming character
    t = BTSerial.read();
    
    // Print the received character for debugging
    Serial.println(t); 
    
    // Perform actions based on the received command
    if (t == 'F') { // Move forward (all motors rotate in forward direction)
      digitalWrite(LEFT_FORWARD, HIGH);
      digitalWrite(RIGHT_FORWARD, HIGH);
    } else if (t == 'B') { // Move reverse (all motors rotate in reverse direction)
      digitalWrite(LEFT_REVERSE, HIGH);
      digitalWrite(RIGHT_REVERSE, HIGH);
    } else if (t == 'L') { // Turn right (left side motors rotate in forward direction, right side motors don't rotate)
      digitalWrite(RIGHT_FORWARD, HIGH);
    } else if (t == 'R') { // Turn left (right side motors rotate in forward direction, left side motors don't rotate)
      digitalWrite(LEFT_FORWARD, HIGH);
    } else if (t == 'W') { // Turn LED on
      digitalWrite(LED_PIN, HIGH);
    } else if (t == 'w') { // Turn LED off
      digitalWrite(LED_PIN, LOW);
    } else if (t == 'S') { // Stop (all motors stop)
      digitalWrite(LEFT_FORWARD, LOW);
      digitalWrite(LEFT_REVERSE, LOW);
      digitalWrite(RIGHT_FORWARD, LOW);
      digitalWrite(RIGHT_REVERSE, LOW);
    }
  }
  
  // Delay for stability
  delay(100);
}

