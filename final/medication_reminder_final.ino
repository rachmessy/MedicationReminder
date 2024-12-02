#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//source for display information: https://www.youtube.com/watch?v=SHORUnKgpKE&t=394s

//defining pins for weight sensors 
const int HX711_1_dout = 4;
const int HX711_2_dout = 3; 
const int HX711_3_dout = 2; 
const int HX711_sck = 5;  

//defining pins for leds
const int led_1 = 6; 
const int led_2 = 7; 
const int led_3 = 8; 

//configure the LCD
LiquidCrystal_I2C lcd(0x27, 16, 4);

//create the HX711 objects
HX711 scale_1;
HX711 scale_2;
HX711 scale_3;

//setup timers for each weight sensor 
unsigned long timer1 = 0;
unsigned long timer2 = 0; 
unsigned long timer3 = 0; 

//setup led variables for each weight sensor
bool led_on_1 = false; 
bool led_on_2 = false; 
bool led_on_3 = false;  

void setup() {
    //set the serial monitor to baud 9600
    Serial.begin(9600);

    //initialize HX711
    scale_1.begin(HX711_1_dout, HX711_sck);
    scale_2.begin(HX711_2_dout, HX711_sck);
    scale_3.begin(HX711_3_dout, HX711_sck);

    //adjust the scale on the weight sensors
    scale_1.set_scale(1000.0);
    scale_2.set_scale(1000.0);
    scale_3.set_scale(1000.0);

    //tare the scales
    scale_1.tare();
    scale_2.tare();
    scale_3.tare();

    //setup the pinouts of leds
    pinMode(led_1, OUTPUT);
    pinMode(led_2, OUTPUT);
    pinMode(led_3, OUTPUT);

    //turn on LCD
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Medication Tracker");
}

void loop() {
    //read the weights from all scales
    float weight1 = scale_1.get_units(1);
    float weight2 = scale_2.get_units(1);
    float weight3 = scale_3.get_units(1);

    //set a lower threshold for what counts as a weight
    float upper_limit = 5.0;

    //handle each sensor
    handle_sensor(1, weight1, upper_limit, led_1, timer1, led_on_1, 1);
    handle_sensor(2, weight2, upper_limit, led_2, timer2, led_on_2, 2);
    handle_sensor(3, weight3, upper_limit, led_3, timer3, led_on_3, 3);

    //set delay to 1000 so this happens every second
    delay(1000);
}

void handle_sensor(int sensor, float weight, float upper_limit, int led_pin, unsigned long &timer, bool &led_on, int lcd_row) {
    //if the a weight is detected
    if (weight > upper_limit) {
        //if stopwatch has not begun, begin.
        if (timer == 0) {
            timer = millis(); 
        }

        //calculate the time that has passed
        unsigned long passed_time = millis() - timer;
        unsigned int seconds = (passed_time/1000) % 60;
        unsigned int minutes = (passed_time/60000) % 60;

        //show the time that has passed on the display
        lcd.setCursor(0, lcd_row);
        lcd.print("Slot ");
        lcd.print(sensor);
        lcd.print(": ");
        lcd.print(display_time(minutes,seconds));

        //check if ten seconds has passed
        if (!led_on && passed_time >= 10000) {
            digitalWrite(led_pin, HIGH);
            led_on = true;
            // Serial.print("sensor ");
            // Serial.print(sensor);
            // Serial.println(":LED should have turned on.");
        }
    } else {
        //If a weight wasn't detected
        //reset to inital state

        //reset the timer to 0
        timer = 0; 
        //turn off the led
        led_on = false; 

        digitalWrite(led_pin, LOW);
        lcd.setCursor(0, lcd_row);
        lcd.print("Slot ");
        lcd.print(sensor);
        lcd.print(": 00:00");
        // Serial.print("sensor ");
        // Serial.print(sensor);
        // Serial.println(": weight not detected so reestting.");
    }
}

String display_time(unsigned int minutes, unsigned int seconds) {
    //need to display MM:SS format
    String formatted_time = "";
    if (minutes < 10) formatted_time += "0";
    formatted_time += String(minutes) + ":";
    if (seconds < 10) formatted_time += "0";
    formatted_time += String(seconds);
    return formatted_time;
}

