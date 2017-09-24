#include <CLZD01.h>

#define dataPin   2
#define clockPin  3

CLZD temperature(dataPin, clockPin);

void setup() {

	Serial.begin(9600);

}



void loop() {

  Serial.print(temperature.read());
  Serial.println("° C");
  
}

