//set led pin to 6
const int led_pin = 6;

//counters for # of times on & # of times off
int on = 0;
int off = 0;

void setup() {
  //set the output pin
  pinMode(led_pin, OUTPUT);
  //serial monitor baud 9600
  Serial.begin(9600);
  Serial.println("starting test");
}

void loop() {
  //turn on led
  digitalWrite(led_pin, HIGH);
  //increment on count
  on++;
  //print to serial monitor
  Serial.print("LED on: ");
  Serial.println(on);
  //delay for a second
  delay(1000);
  //turn off led
  digitalWrite(led_pin, LOW);
  //increment off count and print
  off++;
  Serial.print("LED off: ");
  Serial.println(off);
  //delay for another second
  delay(1000);
}
