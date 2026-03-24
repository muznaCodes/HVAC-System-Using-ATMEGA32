#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

// -------- DHT CONFIG -------- //
#define DHT_PIN PB3

#define SET_PIN_HIGH(port,pin) ((port) |= (1<<(pin)))
#define SET_PIN_LOW(port,pin)  ((port) &= ~(1<<(pin)))
#define READ_PIN(pin)          ((PINB & (1<<(pin))) != 0)

// -------- DHT FUNCTIONS -------- //

void DHT_Request(void)
{
    DDRB |= (1<<DHT_PIN);      // Output
    SET_PIN_LOW(PORTB,DHT_PIN);
    _delay_ms(20);
    SET_PIN_HIGH(PORTB,DHT_PIN);
    DDRB &= ~(1<<DHT_PIN);     // Input
}

uint8_t DHT_ReadByte(void)
{
    uint8_t i, byte = 0;

    for(i=0; i<8; i++)
    {
        while(!READ_PIN(DHT_PIN));
        _delay_us(60);

        if(READ_PIN(DHT_PIN))
            byte |= (1<<(7-i));

        while(READ_PIN(DHT_PIN));
    }
    return byte;
}

uint8_t DHT_Read(uint8_t *humidity, uint8_t *temperature)
{
    uint8_t rh_int, rh_dec, t_int, t_dec, checksum;

    DHT_Request();

    while(READ_PIN(DHT_PIN));
    while(!READ_PIN(DHT_PIN));
    while(READ_PIN(DHT_PIN));

    rh_int   = DHT_ReadByte();
    rh_dec   = DHT_ReadByte();
    t_int    = DHT_ReadByte();
    t_dec    = DHT_ReadByte();
    checksum = DHT_ReadByte();

    if((rh_int + rh_dec + t_int + t_dec) != checksum)
        return 1;

    *humidity = rh_int;
    *temperature = t_int;

    return 0;
}

// -------- HELPER -------- //
void LCD_print_number(uint8_t num)
{
    LCD_write((num/10) + '0');
    LCD_write((num%10) + '0');
}

// -------- MAIN -------- //
int main(void)
{
    uint8_t temp, hum;

    DDRD = 0xFF;                               // LCD data
    DDRB |= (1<<RS)|(1<<RW)|(1<<EN);           // LCD control
    DDRC |= (1<<PC0) | (1<<PC1);               // Output pins

    LCD_init();

    while(1)
    {
        if(!DHT_Read(&hum, &temp))
        {
            // Display humidity
            LCD_cmd(0x80);
            LCD_Write_String("H:");
            LCD_print_number(hum);
            LCD_Write_String("%   ");

            // Display temperature
            LCD_cmd(0xC0);
            LCD_Write_String("T:");
            LCD_print_number(temp);
            LCD_Write_String(" C   ");

            // TEMP control
            if(temp >= 30)
                PORTC |= (1<<PC0);
            else
                PORTC &= ~(1<<PC0);

            // HUMIDITY control
            if(hum >= 70)
                PORTC |= (1<<PC1);
            else
                PORTC &= ~(1<<PC1);
        }
        else
        {
            LCD_cmd(0x80);
            LCD_Write_String("DHT Error      ");
            PORTC &= ~((1<<PC0)|(1<<PC1));
        }

        _delay_ms(1000);
    }
}