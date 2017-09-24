 /*
  Copyright (c) 2017 Marcelo Henrique Moraes

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3.0 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

 */


#include "CLZD01.h"

//constructor
CLZD::CLZD(uint8_t dataPin, uint8_t clockPin) {
	data = dataPin;
	clock = clockPin;
	digitalWrite(clock, LOW);
	pinMode(clock, OUTPUT);
	pinMode(data, INPUT);
}

//private
void CLZD::pulse() {
	digitalWrite(clock, HIGH);
	_delay_us(8);
	digitalWrite(clock, LOW);
}

void CLZD::com() {
	uint16_t volatile aux = 0;
	uint8_t paridade = 0;
	uint8_t j = 9;
	for (int i = 0; i < 10; i++) {
		this->pulse();
		if (digitalRead(data)) {
			_delay_us(1);
			if (digitalRead(data)) {
				aux |= (1<<j);
				paridade++;
			}
		}
		j--;
	}
	this->pulse();
	paridade %= 2;
	if (paridade == digitalRead(data)) {
		_delay_us(1);
		if (paridade == digitalRead(data))
			this->temp = aux;
	}
}

//public
float CLZD::read() {
	this->com();
	return this->temp * 0.2124;
}
