/*
 * lcd.h
 *
 *  Created on: 9 Kas 2024
 *      Author: Emre
 */

#ifndef LCD_H_
#define LCD_H_

#define LCDPORT         0x40005000
#define LCDPORTENABLE   0xf0000801
#define RS              0x40005001
#define E               0x40005002
#define D4              0x40005010
#define D5              0x40005020
#define D6              0x40005040
#define D7              0x40005080


void LCD_ayar(void);
void LCD_komut(unsigned char a);
void LCD_karakteral(unsigned char a);
void LCD_temizle(void);
void LCD_yaz(char *a,int b);
void LCD_sonrakisatiryaz(char *a);
void LCD_cursor(char a, char b);

#endif /* LCD_H_ */
