/*
*Comments in PT-BR:
*	Author: Marcelo H Moraes
*	marceloh220@hotmail.com
*	Application: Display lcd 16x2 HD44780 based with 74LS595 bit shift.
*/
#ifndef IHM595_H
#define IHM595_H
#include <Arduino.h>
#include <inttypes.h>
#include <Print.h>

#define noCURSOR 		0x0C
#define blinkCURSOR  	0x0D
#define onCURSOR	    0x0E
#define alternateCURSOR 0x0F

class IHM595 : public Print {
private:
	uint8_t _background;
	uint8_t clock, data, enable;
	uint8_t _row, _col;
	uint8_t _addressrow[4];
	void send(uint8_t d);
	void cmd(uint8_t d, uint8_t c);
	void _mode();
public:
	IHM595(uint8_t clock_, uint8_t data_, uint8_t enable_);
	virtual size_t write(uint8_t c);
	virtual size_t write(const char *s);
	virtual size_t write(const uint8_t *s, size_t l);
	void init();
	inline void config(uint8_t col, uint8_t row) {
		_col = col;
		_row = row;
		this->_mode();
	}
	void clear();
	void home();
	void cursor(uint8_t mode);
	void display(uint8_t state);
	void set(uint8_t col, uint8_t lin);
	void background(uint8_t state);
};
#endif
