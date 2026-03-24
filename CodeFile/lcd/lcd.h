#ifndef LCD_H_
#define LCD_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

// -------- LCD CONFIG -------- //
#define LCD_DATA PORTD     // Data port
#define LCD_CTRL PORTB     // Control port

// Control pins
#define RS PB0
#define RW PB1
#define EN PB2

// -------- FUNCTIONS -------- //
void LCD_cmd(unsigned char cmd);
void LCD_write(unsigned char data);
void LCD_init(void);
void LCD_Write_String(char *str);

// -------- IMPLEMENTATION -------- //

// Send command
void LCD_cmd(unsigned char cmd)
{
    LCD_DATA = cmd;
    LCD_CTRL &= ~(1<<RS);  // RS = 0
    LCD_CTRL &= ~(1<<RW);  // RW = 0
    LCD_CTRL |= (1<<EN);
    _delay_ms(2);
    LCD_CTRL &= ~(1<<EN);
}

// Write data
void LCD_write(unsigned char data)
{
    LCD_DATA = data;
    LCD_CTRL |= (1<<RS);   // RS = 1
    LCD_CTRL &= ~(1<<RW);  // RW = 0
    LCD_CTRL |= (1<<EN);
    _delay_ms(2);
    LCD_CTRL &= ~(1<<EN);
}

// Initialize LCD
void LCD_init(void)
{
    LCD_cmd(0x38); // 8-bit mode
    _delay_ms(1);
    LCD_cmd(0x01); // Clear screen
    _delay_ms(2);
    LCD_cmd(0x02); // Return home
    _delay_ms(2);
    LCD_cmd(0x06); // Entry mode
    _delay_ms(1);
    LCD_cmd(0x0C); // Display ON
    _delay_ms(1);
}

// Print string
void LCD_Write_String(char *str)
{
    while(*str)
    {
        LCD_write(*str++);
    }
}

#endif /* LCD_H_ */

