#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdbool.h>

#include "main.h"
#include "display1602.h"

int main() {
	init();
	loop();
}

void init() {
	init_1602_pins();
	init_display();

	select_1602_line(CMD_1602_DDRAM_LINE1);
	write_1602_line(16,"Looks like it...");
	select_1602_line(CMD_1602_DDRAM_LINE2);
	write_1602_line(9, "works now");

}

void loop() {
	for(;;) {

	}
}


