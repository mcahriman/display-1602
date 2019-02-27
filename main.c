#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdbool.h>

#include "main.h"
#include "display1602.h"

int main() {
	init();
	for(;;) {
		loop();
	}
}

void init() {
	init_1602_pins();
	init_display(false);

	select_1602_line(CMD_1602_DDRAM_LINE1);
	write_1602_line(16,"It works!       ");

}

/**
 * Example displays the font on the second line
 */
void loop() {
	static uint8_t symbols[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	_delay_ms(1000);
	for (int i = 0; i < 16; i++) {
		symbols[i]+=16;
	}
	select_1602_line(CMD_1602_DDRAM_LINE2);
	write_1602_line(16, (char*) symbols);


}


