#include <Arduino.h>
#include <ADNS3080.h>
#define SS 13
#define RESET 12


ADNS3080 camera(SS, RESET); 


void setup() {
  camera.begin();
}

void loop() {

}