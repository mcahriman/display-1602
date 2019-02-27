
#ifndef DISPLAY1602_H_
#define DISPLAY1602_H_

//Set your data port configuration

#define CONTROL_1602_PORT		PORTC
#define CONTROL_1602_PORT_DDR	DDRC
#define CONTROL_1602_RS		PC0
#define CONTROL_1602_E		PC1
#define CONTROL_1602_RW		PC2

#define DATA_1602_PORT PORTD
#define DATA_1602_PORT_DDR DDRD

//Clear display
#define CMD_1602_CLS 0b00000001
//Move cursor home
#define CMD_1602_HOME 0b00000010
//Set Cursor moving direction

#define CMD_1602_DIRECTION_RIGHT 0b00000110
#define CMD_1602_DIRECTION_LEFT  0b00000100

#define CMD_1602_DIRECTION_RIGHT_SHIFT 0b00000111
#define CMD_1602_DIRECTION_LEFT_SHIFT  0b00000101

//Display mode
#define CMD_1602_MODE_OFF 0b00001000
#define CMD_1602_MODE_ON 0b00001100
#define CMD_1602_MODE_ON_CURSOR 0b00001110
#define CMD_1602_MODE_ON_CURSOR_BLNK 0b00001111

//Shift cursor
#define CMD_1602_CURSOR_SHIFT_LEFT  0b00010000
#define CMD_1602_CURSOR_SHIFT_RIGHT 0b00010100
#define CMD_1602_CURSOR_SHIFT_LEFT_DISPLAY 0b00011000
#define CMD_1602_CURSOR_SHIFT_RIGHT_DISPLAY 0b00011100

//Function Set
#define CMD_1602_FUNC_SET_BIT _BV(5)

//DL: DATA LENGTH - High: 8 bit LOW:4 bit
#define CMD_1602_FUNC_DL _BV(4)

//N: Number of lines: High: 2, Low: 1
#define CMD_1602_FUNC_N _BV(3)

//D: Font Size Low: (5x8) High: 5x11
#define CMD_1602_FUNC_F _BV(2)

#define CMD_1602_DDRAM_SET _BV(7)
#define CMD_1602_DDRAM_LINE1 0x00
#define CMD_1602_DDRAM_LINE2 0x40

#define CMD_MASK (_BV(CONTROL_1602_E) | _BV(CONTROL_1602_RS) | _BV(CONTROL_1602_RW))
#define DATA_MASK_4_BIT 0x0f;

#define CMD_1602_CMD_MODE_BEGIN  CONTROL_1602_PORT = (CONTROL_1602_PORT & ~CMD_MASK) | _BV(CONTROL_1602_E);
#define CMD_1602_DATA_MODE_BEGIN CONTROL_1602_PORT = (CONTROL_1602_PORT & ~CMD_MASK) \
			| _BV(CONTROL_1602_RS) \
			| _BV(CONTROL_1602_E)

#define CMD_1602_CTRL_RELEASE CONTROL_1602_PORT &= ~CMD_MASK


//TODO: Add 4 bit control mode
//TODO: Add PWM control for V0


#if  F_CPU != 16000000UL
#warning Currently I try to make it work assuming 16MHz. Please keep it in mind
#endif /* F_CPU WARNING */

void init_1602_pins();
void init_display(bool);

void write_1602_command(uint8_t command);
void write_1602_char(uint8_t data);

void write_1602_command_8_bit(uint8_t command);
void write_1602_char_8_bit(uint8_t data);

void write_1602_command_4_bit(uint8_t command);
void write_1602_char_4_bit(uint8_t data);


void select_1602_line(uint8_t address);
void write_1602_line(int length, char* buf);

#endif /* DISPLAY1602_H_ */
