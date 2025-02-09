//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

// https://github.com/bblanchon/ArduinoJson/tree/5.x
// https://github.com/FirebaseExtended/firebase-arduino

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "testing-nodemcu-1.firebaseio.com"
#define FIREBASE_AUTH "LG9HvBGc5p7NpAzlcbfpkXk7SbVIVWEcuGCtWBzQ"
#define WIFI_SSID "Leydig"
#define WIFI_PASSWORD "94232607."

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  pinMode(2, OUTPUT);
}

int n = 0;

void loop() {

  // update value
  Firebase.setFloat("counter", n++);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
 
  // get value 
  Serial.print("number: ");
  Serial.println(Firebase.getFloat("number"));
  if(Firebase.getFloat("number")){
    digitalWrite(2, LOW);
  }else{
    digitalWrite(2, HIGH);
  }
  delay(1000);
}
