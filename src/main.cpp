#include <Arduino.h>
const uint8_t powerpin = 3;
const uint8_t switchpin = 11;
const uint16_t timereq = 1000;
bool previous_switch_state = 1;
bool current_switch_state;
unsigned long timepassed;
unsigned long baseline;
void setup() {
 pinMode(switchpin, INPUT_PULLUP);
 pinMode(powerpin, OUTPUT);
 analogWrite(powerpin, 0);
}

void loop() {
 current_switch_state = digitalRead(switchpin);
 if(current_switch_state != previous_switch_state){
  if(current_switch_state == LOW){
        // just pressed — record start
        baseline = millis();
    }
     else{
        // just released — measure duration
        timepassed = millis();
        if(timepassed - baseline >= timereq){
            for(uint16_t i = 0; i<=255; i+=25){
              analogWrite(powerpin, i);
              delay(75);
            }
        }
        else{
          for(int16_t i = 255; i>=0; i-=25){
              analogWrite(powerpin, i);
              delay(75);
            }
            analogWrite(powerpin, 0);
        }
      }
 }
 previous_switch_state = current_switch_state;
}