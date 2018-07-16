#include <inttypes.h>
#include <avr/io.h>
#include <stdbool.h>
#include "display1602.h"
#include <util/delay.h>

void init_1602_pins() {
	CONTROL_1602_PORT_DDR |= _BV(CONTROL_1602_E) | _BV(CONTROL_1602_RS) | _BV(CONTROL_1602_RW);
	DATA_1602_PORT_DDR |= 0xFF; //TODO: 4-bit mode enable;
}

/**
 * accepts line numbers
 * valid arguments are
 * CMD_1602_DDRAM_LINE1
 * CMD_1602_DDRAM_LINE2
 *
 */
void select_1602_line(uint8_t line) {
	write_1602_command(CMD_1602_DDRAM_SET | line);
	_delay_ms(2);

}

void write_1602_line(int count, char* buf) {
	for(int i=0; i<count; i++) {
		write_1602_char((uint8_t) buf[i]);
		_delay_us(37);
	}
}

//TODO: move cursor, etc

void init_display() {
	_delay_ms(15); //wait for display initialization

	write_1602_command(CMD_1602_FUNC_SET_BIT | CMD_1602_FUNC_DL | CMD_1602_FUNC_N);
	_delay_ms(1);

	// Turn on display
	write_1602_command(CMD_1602_MODE_ON);
	_delay_us(37);

	// Clear screen
	write_1602_command(CMD_1602_CLS);
	_delay_ms(2);

	//Home
	write_1602_command(CMD_1602_HOME);
	_delay_ms(2);

	//Set Direction to Right
	write_1602_command(CMD_1602_DIRECTION_RIGHT);
	_delay_ms(1);
}

/**
 * 0 - write
 * 1 - read
 */
void write_1602_command(uint8_t command) {

	//enable command
	CONTROL_1602_PORT = (CONTROL_1602_PORT & ~CMD_MASK) | _BV(CONTROL_1602_E);
	DATA_1602_PORT = command;
	_delay_us(5);
	CONTROL_1602_PORT &= ~CMD_MASK;
}

void write_1602_char(uint8_t data) {
	CONTROL_1602_PORT = (CONTROL_1602_PORT & ~CMD_MASK)
			| _BV(CONTROL_1602_RS)
			| _BV(CONTROL_1602_E);
	DATA_1602_PORT = data;
	_delay_us(5);
	CONTROL_1602_PORT &= ~CMD_MASK;

}
