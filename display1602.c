#include <inttypes.h>
#include <avr/io.h>
#include <stdbool.h>
#include "display1602.h"
#include <util/delay.h>

static struct display_configuration {
	bool is_8_bit;
} display_configuration;

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

/**
 * use_8_bit - use 8 bit interface if true, 4 bit if false
 */
void init_display(bool use_8_bit) {
	_delay_ms(15); //wait for display initialization

	display_configuration.is_8_bit = use_8_bit;

	write_1602_command(CMD_1602_FUNC_SET_BIT | CMD_1602_FUNC_N | (use_8_bit ? CMD_1602_FUNC_DL : 0) );
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


void write_1602_command(uint8_t command) {
	if(display_configuration.is_8_bit) {
		write_1602_command_8_bit(command);
	} else {
		write_1602_command_4_bit(command);
	}
}

void write_1602_char(uint8_t data) {
	if(display_configuration.is_8_bit) {
		write_1602_char_8_bit(data);
	} else {
		write_1602_char_4_bit(data);
	}
}

/**
 * 0 - write
 * 1 - read
 */
void write_1602_command_8_bit(uint8_t command) {

	//enable command
	CMD_1602_CMD_MODE_BEGIN;
	DATA_1602_PORT = command;
	_delay_us(5);
	CMD_1602_CTRL_RELEASE;
}

void write_1602_char_8_bit(uint8_t data) {
	CMD_1602_DATA_MODE_BEGIN;
	DATA_1602_PORT = data;
	_delay_us(5);
	CMD_1602_CTRL_RELEASE;

}

//assume 1st 4 bits of port are used
void write_1602_command_4_bit(uint8_t command) {
	CMD_1602_CMD_MODE_BEGIN;
	DATA_1602_PORT |= (DATA_1602_PORT & ~CMD_MASK) | (command & CMD_MASK);
	_delay_us(5);
	CMD_1602_CTRL_RELEASE;
	_delay_us(5);
	CMD_1602_CMD_MODE_BEGIN;
	DATA_1602_PORT |= (DATA_1602_PORT & ~CMD_MASK) | (command >> 4 & CMD_MASK);
	_delay_us(5);
	CMD_1602_CTRL_RELEASE;
	_delay_us(5);
}

void write_1602_char_4_bit(uint8_t data) {
	CMD_1602_DATA_MODE_BEGIN;
	DATA_1602_PORT |= (DATA_1602_PORT & ~CMD_MASK) | (data & CMD_MASK);
	_delay_us(5);
	CMD_1602_CTRL_RELEASE;
	_delay_us(5);
	CMD_1602_CMD_MODE_BEGIN;
	DATA_1602_PORT |= (DATA_1602_PORT & ~CMD_MASK) | (data >> 4 & CMD_MASK);
	_delay_us(5);
	CMD_1602_CTRL_RELEASE;
	_delay_us(5);
}
