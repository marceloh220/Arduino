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
 

#include "Bits16.h"

Bits16::Bits16(uint8_t clock, uint8_t data) {
	_clock = clock;
	_data  = data;
}

void Bits16::send(uint16_t dado) {
    uint8_t aux;
    for(aux=0; aux<16; aux++) {
    	if(dado&0x01) digitalWrite(_data,HIGH);
    	else  digitalWrite(_data,LOW);
    	digitalWrite(_clock,HIGH);
    	digitalWrite(_clock,LOW);
    	dado=dado>>1;
	}
}

void Bits16::begin() {
	digitalWrite(_clock,LOW);
	digitalWrite(_data,LOW);
	pinMode(_clock,OUTPUT);
	pinMode(_data,OUTPUT);
}

uint16_t Bits16::out(uint8_t port, uint8_t state) {
	if(state)
		_ports|=(1<<port);
	else
		_ports&=~(1<<port);
	send(_ports);
	return _ports;
}

void Bits16::print(uint16_t number) {
	uint16_t _send;
	_send=segments[number/10]<<8;
	_send|=segments[number%10];
	send(_send);
	_ports=_send;
}

void Bits16::dot(uint8_t pos) {
	if(pos)
		_ports&=~(1<<15);
	else
		_ports&=~(1<<7);
	send(_ports);
}
