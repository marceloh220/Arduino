#include <clzd01.h>

#define dataPin   2
#define clockPin  3

Serial monitor(9600);
CLZD temperatura(dataPin, clockPin);

void setup() {



  
}



void loop() {

  monitor.print(temperatura.read());
  minitor.println("° C");

  
}

