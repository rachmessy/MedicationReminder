#include "HX711.h"

//source: https://www.youtube.com/watch?v=sxzoAGf1kOo&t=398s

//define pins
const int HX711_dout = 4; 
const int HX711_sck = 5;

//using HX711 library 
HX711 scale;

void setup() {
  //serial monitor will be on 9600 baud
  Serial.begin(9600);
  //set the scale to the correct pins
  scale.begin(HX711_dout, HX711_sck);
  //tare the scale
  scale.tare();
  Serial.println("begin test");
}

void loop() {
  //read the weight without calibration
  float weight = scale.get_units();
  //print out weight to serial monitor
  Serial.print("weight: ");
  Serial.println(weight);
  //no weight ranges from -inf to around 50.0.
  if (weight > 100.0) {
    Serial.println("weight was detected.");
  } else {
    Serial.println("no weight detected.");
  }
  //1 second delay
  delay(1000);
}
