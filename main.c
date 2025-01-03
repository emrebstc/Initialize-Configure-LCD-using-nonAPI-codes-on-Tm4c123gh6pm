#include "stdint.h"
#include "stdbool.h"
#include "driverlib/sysctl.h"
#include "inc/tm4c123gh6pm.h"
#include "lcd.h"

void clockayar();

int main(void) {
                           //For other functions, check out lcd.c
    clockayar();
    LCD_ayar();

        while (1) {

            LCD_yaz("ileri-mikro",0);  // "0" For print on first line

            SysCtlDelay(30000000);

            LCD_temizle(); // Clear LCD

            LCD_sonrakisatiryaz("15123121"); // for print on different line

            SysCtlDelay(30000000);

            LCD_temizle();

            LCD_sonrakisatiryaz("emrebstc");

            SysCtlDelay(30000000);

            LCD_temizle();

            LCD_sonrakisatiryaz("4.....");

            SysCtlDelay(30000000);

            LCD_temizle();

            LCD_yaz("LCDbaslat",1);

            SysCtlDelay(30000000);

            LCD_temizle();

        }


}

void clockayar(){
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
}
