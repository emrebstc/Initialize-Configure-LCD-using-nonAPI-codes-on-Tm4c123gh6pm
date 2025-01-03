/*
 * lcd.c
 *
 *  Created on: 9 Kas 2024
 *      Author: Emre
 */

#include "stdint.h"
#include "stdbool.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/gpio.h"
#include "driverlib/gpio.c"
#include "driverlib/sysctl.h"
#include "driverlib/sysctl.c"
#include "math.h"
#include "inc/hw_gpio.h"
#include "string.h"
#include "lcd.h"

int sayac=0;

void HWREGLCD(uint8_t a,uint8_t b){

    ASSERT(_GPIOBaseValid(LCDPORT))

    HWREG(LCDPORT + (GPIO_O_DATA + ((a) << 2))) = b;
    SysCtlDelay(100000);
}

void otuzhex(){
         int i;
         for (i=1;i<=3;i++){
         SysCtlDelay(100000);
         GPIO_PORTB_DATA_R &= 0x0FE;
         GPIO_PORTB_DATA_R |= 0x0F0;
         GPIO_PORTB_DATA_R |= 0x02;
         SysCtlDelay(1000);
         GPIO_PORTB_DATA_R |= 0x0F0;
         }
}

void LCD_komut(unsigned char a) {


    HWREG(LCDPORT + 4*(240)) = (a & 0xf0); // (4*(D4|D5|D6|D7)) calismiyor

    HWREGLCD(1,(0x00));                   // (4*(1)) calismiyor , HWREG(0x40005001) ve PIO_PORTB_DATA_BITS_R[0] ve calismiyor

    HWREG(LCDPORT + 4*(2)) = 0x02;

    SysCtlDelay(10);

    HWREG(LCDPORT + 4*(2)) = 0x00;

    SysCtlDelay(50000);

    HWREG(LCDPORT + 4*(240)) = ((a & 0x0f)<<4);

    HWREGLCD(1,(0x00));

    HWREG(LCDPORT + 4*(2)) = 0x02;

    SysCtlDelay(10);

    HWREG(LCDPORT + 4*(2)) = 0x00;

    SysCtlDelay(50000);

}


void LCD_ayar() {
    SYSCTL_RCGCGPIO_R |= 0x02; // Port B için aktifleþtirme
    while((SYSCTL_PRGPIO_R & 0x02) == 0) {} // portB etkinleþtirilene kadar beklemek için
    GPIO_PORTB_DIR_R |= 0x0F3;  // I/O secimi
    GPIO_PORTB_DEN_R |= 0x0F3;  // pullup

    otuzhex();

    SysCtlDelay(100000);

        LCD_komut(0x0F); //LCDyi ac (ekran ac/kapa komutu) ekran acýk kursor acýk kursor blink acik
        LCD_temizle();

}

void LCD_karakteral(unsigned char a) {

    HWREG(LCDPORT + 4*(240)) = (a & 0xf0);

    HWREGLCD(1,(0x01));

    HWREG(LCDPORT + 4*(2)) = 0x02;

    SysCtlDelay(10);

    HWREG(LCDPORT + 4*(2)) = 0x00;

    SysCtlDelay(50000);

    HWREG(LCDPORT + 4*(240)) = ((a & 0x0f)<<4);

    HWREGLCD(1,(0x01));

    HWREG(LCDPORT + 4*(2)) = 0x02;

    SysCtlDelay(10);

    HWREG(LCDPORT + 4*(2)) = 0x00;

    SysCtlDelay(50000);

}

void LCD_yaz(char *a,int b) {
    int i;
    if(b==0){
    for (i=0; i<16; i++) {
        if (i<strlen(a)) {
            LCD_cursor(0,i);
            LCD_karakteral(a[i]);
            sayac=0;
        }

    }
    LCD_komut(0xC0 + 16); //Cursor gozukmesin
}
    else if (b==1) {
        for (i=0; i<16; i++) {
                if (i<strlen(a)) {
                    LCD_cursor(1,i);
                    LCD_karakteral(a[i]);
                    sayac=1;
                }

            }
            LCD_komut(0xC0 + 16);
    }

}


void LCD_cursor(char a, char b){

    if (a==0) {
        LCD_komut(0x80 + (b % 16)); //kursor 1. satir + b kadar sutun
    }
    else {
        LCD_komut(0xC0 + (b % 16)); //kursor 2.satir + b kadar sutun
    }
}

void LCD_temizle(void){
        LCD_komut(0x01);
        SysCtlDelay(50);
        LCD_cursor(0,0);
        SysCtlDelay(50);
}

void LCD_sonrakisatiryaz(char *a) {
    int i;
    if(sayac==0){
    for (i=0; i<16; i++) {
        if (i<strlen(a)) {
            LCD_cursor(1,i);
            LCD_karakteral(a[i]);
            sayac=1;
        }

    }
    LCD_komut(0xC0 + 16);
}
    else if (sayac==1) {
        for (i=0; i<16; i++) {
                if (i<strlen(a)) {
                    LCD_cursor(0,i);
                    LCD_karakteral(a[i]);
                    sayac=0;
                }

            }
            LCD_komut(0xC0 + 16);
    }
}
