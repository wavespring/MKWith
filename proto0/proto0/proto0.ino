#include <M5Atom.h>
#include <ArduinoJson.h>
#include "BluetoothSerial.h"
#include "AtomMotion.h"
#include <Unit_Sonic.h>

SONIC_IO sensor;
AtomMotion Atom;

BluetoothSerial bts;
DynamicJsonDocument doc(1024);
StaticJsonDocument<100> stm, rec;
int distCnt = 0;
int openFlag = 1;
  
void setup() {
  M5.begin(true, true, true);
  bts.begin("M5Stack Atom Lite");
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 32, 26);
  Atom.Init();
  sensor.begin(33, 23);
  stm["function"] = "Camera Stream";
  stm["args"] = "";
  rec["function"] = "Object Recognition";
  rec["args"] = '["yolo_20class"]';
}

void loop(){
  M5.update();

  static float Distance = 0;
  Distance = sensor.getDistance();
  Serial.println(Distance);
  if(distCnt == 100){
    if (Distance <100) {
      if (openFlag){
        Atom.SetMotorSpeed(2, 0);
        serializeJson(stm, Serial2);
        openFlag = 0;
      }
    }else {
      if (!openFlag){
        Atom.SetMotorSpeed(2, 80);
        serializeJson(rec, Serial2);
        openFlag = 1;
      }
    }
    distCnt=0;
  }
  
  
  if(Serial2.available()) {
    String receiveString = Serial2.readStringUntil('\n');
    //if(receiveString[0] == '{'){
    //  Serial.println(receiveString);
    //}
    deserializeJson(doc, receiveString);

    String x = doc["obj"][0]["x"];
    String y = doc["obj"][0]["y"];
    String type = doc["obj"][0]["type"];
//    Serial.print(x);
//    Serial.print(",");
//    Serial.print(y);
//    Serial.print(",");
//    Serial.println(type);
    bts.println(x+","+y+","+type);
  }

  distCnt++;
  delay(10);
}
