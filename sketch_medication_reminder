#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//source for display information: https://www.youtube.com/watch?v=SHORUnKgpKE&t=394s


// defining pin connections
// HX711 dout will be in A4 pin and sck in A5 pin
const int HX711_dout = 4;       
const int HX711_sck = 5;

// led pin will be in digitial pin 6
const int led_pin = 6;           

// first line starts at address 0x27, display has 16 columns and 4 rows
LiquidCrystal_I2C lcd(0x27, 16, 4); 

//scale from HX711 library
HX711 scale;

//to keep track of when the weight was first detected to trigger led turn on
float timer = 0; 
//track whether a weight is detected
bool weight_detected = false; 

bool led_on = false;                

void setup() {
    //serial monitor baud will be 9600
    Serial.begin(9600);
    scale.begin(HX711_dout, HX711_sck);
    //through tests found the scale value was 1000 times too high.
    scale.set_scale(1000.0);    
    //tare scale
    scale.tare();                    
    // set the led pin as an output
    pinMode(led_pin, OUTPUT);   
    // initialize lcd, turning on back light, and clear      
    lcd.init();                     
    lcd.backlight();                 
    lcd.clear();
}

void loop() {
    //this will get average weight over the past 10 readings
    float weight = scale.get_units(10);
    // found that it can range from -1 to 1 when there is no weight present through testing
    float lower_limit = 1.0;     
    // anything over 5.0 grams we can be sure there is a weight present
    float upper_limit = 5.0;

    //clear lcd on every beat    
    lcd.clear();
    
    //in the case a weight is detected
    if (weight > upper_limit) {
        // in the case the weight has not been detected before
        if (!weight_detected) {
            //first start the timer
            timer = millis(); // Record the time when weight was added
            //set weight detected to true
            weight_detected = true;
            //debug print weight was detected and the timer has started
            Serial.println("weight was detected and timer has begun");
        }

        //at every beat we need to check if the timer has exceeded 10 seconds since a weight was detected
        if (!led_on && millis() - timer >= 10000) {
            //turn the led on if 10 seconds has passed
            digitalWrite(led_pin, HIGH);
            //set led_on to true
            led_on = true;
            //debug print to serial that led is on 
            Serial.println("led is on");
        }

        //show the weight on display
        //goes to first line and first column
        lcd.setCursor(0, 0);
        //print out weight
        lcd.print("weight: ");
        lcd.print(weight);
        lcd.print(" grams");

    } else if (weight < lower_limit) {
        //if no weight is detected, everything gets reset
        weight_detected = false;
        led_on = false;
        //turn off the led
        digitalWrite(led_pin, LOW); 
        //debug print to serial there is no weight and we are resetting
        Serial.println("reset because there is no weight");
        //show on display there is no weight detected
        lcd.setCursor(0, 0);
        lcd.print("no weight detected");
    }
    //update every half second
    delay(500); 
}
