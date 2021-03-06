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

#include <avr/io.h>
#include <inttypes.h>

#ifndef TWI_H
#define TWI_H

#define NACK		0
#define ACK			1
#define SLAVE		0
#define MASTER		1
#define FAST		3
#define SLOW		0

extern uint8_t mode_twi;

class TWI {
private:
	inline uint8_t status() { return TWSR & 0xF8;}
	void address(uint8_t _address);
public:
	//initialize
	TWI(uint8_t mode = MASTER, uint8_t speed = FAST);
	~TWI() { PRR |= (1<<PRTWI); }
	
	//to communication
	inline void start() {
		TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
		while (!(TWCR & (1<<TWINT)));
	}
	inline void stop() { TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);}
	void send(uint8_t data);
	uint8_t recive(uint8_t ack = ACK);
	
	//to access data
	inline uint8_t get() { return TWDR;	}
	inline void put(uint8_t data) { TWDR = data; }
	
//to checks
	
	//in master mode

	uint8_t ifstart();
	
	//in master and slave mode
	
	uint8_t ifack() {
		uint8_t aux = status();
#if mode_twi == MASTER
		//master
		return aux==0x18||aux==0x28;
#elif mode_twi == SLAVE
		//slave
		return aux==0xB8;
#endif	
	}
	
	uint8_t ifnack() {
		uint8_t aux = status();
#if mode_twi == MASTER
		//master
		return aux==0x20||aux==30;
#elif mode_twi == SLAVE
		//slave
		return aux==0xC0;
#endif
	}
	
};



#endif
