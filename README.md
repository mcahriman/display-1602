# 1602 Display Library for AVR

## Usage
  - add corresponding files (display1602.c, display1602.h) to your project
  - consider the build requirements, and check id F_CPU is set,
    as library utilizes busy-wait delay_ms and delay_ns functions.
  - check wiring. Command and data should use different ports.
    * in display1602.h set CONTROL_1602_PORT CONTROL_1602_PORT_DDR to corresponding PORTX and DDRX. By default it is set to PORTC and DDRC respectively
    * in display1602.h set CONTROL_1602_RS, CONTROL_1602_E, CONTROL_1602_RW to corresponding pins. By default these are set to PC0, PC1 and PC2 respectively.
    * in display1602.h set DATA_1602_PORT and DATA_1602_PORT_DDR to corresponding PORTY and DDRY. By default it is set to   PORTD and DDRD respectively.
  - call init_display() on boot.
  
## Examples

### Example wiring for atmega8
![atmega8 wiring](https://raw.githubusercontent.com/mcahriman/display-1602/master/doc_assets/wiring.png "PortC is used for commands definition, PORTD for data. Unfortunately you cannot  break the data to different ports")

### Initialize and write some text
```C
void init() {
  init_1602_pins();
  init_display();
  write_some_text();
}

void write_some_text() {
  select_1602_line(CMD_1602_DDRAM_LINE1);
  write_1602_line(16,"Looks like it...");
  select_1602_line(CMD_1602_DDRAM_LINE2);
  write_1602_line(9, "works now");
}
```
### Write some text at certain position at line
```C
  select_1602_line(CMD_1602_DDRAM_LINE1);
  write_1602_line(16,"Let it blink!   ");


  for(;;) {
  
    _delay_ms(500);
    //add 7 symbols offset

    select_1602_line(CMD_1602_DDRAM_LINE1 + 7);
    write_1602_line(5,"poops");

    //repeat last action
    _delay_ms(500);
    //add 7 symbols offset

    select_1602_line(CMD_1602_DDRAM_LINE1 + 7);
    write_1602_line(5,"blink");
}
```

## Limitations:

For now:
  - 4 bit transfer mode is not implemented at the moment
  - Display write is totaly sinchronous and takes not less than several milliseconds
  - You cannot divide data pins to several ports (by design)
  - You cannod divide command pins to several ports (design)
