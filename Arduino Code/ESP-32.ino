/****************************************************************************
   Example of the OOCSI-ESP library connecting to WiFi and receiving messages
   over OOCSI. Designed to work with the Processing OOCSI sender example
   that is provided in the same directory
 ****************************************************************************/

#include "OOCSI.h"

#define MOTOR_1_PIN_1    32
#define MOTOR_1_PIN_2    33
#define MOTOR_2_PIN_1    26
#define MOTOR_2_PIN_2    25

int LDRsensor = A0;


const char* ssid = "iPhone";
const char* password = "smartflow";

const char* OOCSIName = "PLANT-ESP32";
const char* hostserver = "oocsi.id.tue.nl";

OOCSI oocsi = OOCSI();
String control = "stop";

void setup() {
  Serial.begin(115200);
  pinMode(MOTOR_1_PIN_1, OUTPUT);
  pinMode(MOTOR_1_PIN_2, OUTPUT);
  pinMode(MOTOR_2_PIN_1, OUTPUT);
  pinMode(MOTOR_2_PIN_2, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  oocsi.setActivityLEDPin(LED_BUILTIN);

  oocsi.connect(OOCSIName, hostserver, ssid, password, processOOCSI);

  Serial.println("subscribing to esp-testchannel");
  oocsi.subscribe("PLANT-testchannel");

  Serial.print("is ");
  Serial.print(OOCSIName);
  Serial.print(" a client? --> ");
  Serial.println(oocsi.containsClient(OOCSIName));

}

void loop() {
  oocsi.check();
  

  int LDRreading = map(analogRead(LDRsensor),0,4095,0,255);
  Serial.println(LDRreading);
  
  oocsi.newMessage("PLANT-testchannel");
  oocsi.addInt("ldr", LDRreading);
  oocsi.sendMessage();
    // oocsi.printSendMessage();

  oocsi.check();
  delay(100);
}

// function which OOCSI calls when an OOCSI message is received
void processOOCSI() {
  control = oocsi.getString("movement", 0);
  Serial.println(control);
  if(control=="forward") {
    Serial.println("Forward");
    digitalWrite(MOTOR_1_PIN_1, 1);
    digitalWrite(MOTOR_1_PIN_2, 0);
    digitalWrite(MOTOR_2_PIN_1, 1);
    digitalWrite(MOTOR_2_PIN_2, 0);
  }
  else if(control=="left") {
    Serial.println("Left");
    digitalWrite(MOTOR_1_PIN_1, 0);
    digitalWrite(MOTOR_1_PIN_2, 1);
    digitalWrite(MOTOR_2_PIN_1, 1);
    digitalWrite(MOTOR_2_PIN_2, 0);
  }
  else if(control=="right") {
    Serial.println("Right");
    digitalWrite(MOTOR_1_PIN_1, 1);
    digitalWrite(MOTOR_1_PIN_2, 0);
    digitalWrite(MOTOR_2_PIN_1, 0);
    digitalWrite(MOTOR_2_PIN_2, 1);
  }
  else if(control=="backward") {
    Serial.println("Backward");
    digitalWrite(MOTOR_1_PIN_1, 0);
    digitalWrite(MOTOR_1_PIN_2, 1);
    digitalWrite(MOTOR_2_PIN_1, 0);
    digitalWrite(MOTOR_2_PIN_2, 1);
  }
  else if(control=="stop") {
    Serial.println("Stop");
    digitalWrite(MOTOR_1_PIN_1, 0);
    digitalWrite(MOTOR_1_PIN_2, 0);
    digitalWrite(MOTOR_2_PIN_1, 0);
    digitalWrite(MOTOR_2_PIN_2, 0);
  }
  
  

}
