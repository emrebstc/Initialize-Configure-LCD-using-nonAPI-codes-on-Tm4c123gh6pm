#include "stdint.h"
#include "stdbool.h"
#include "driverlib/sysctl.h"
#include "inc/tm4c123gh6pm.h"
#include "lcd.h"

void clockayar();

int main(void) {

    clockayar();
    LCD_ayar();

        while (1) {

            LCD_yaz("ileri-mikro",0);

            SysCtlDelay(30000000);

            LCD_temizle();

            LCD_sonrakisatiryaz("g220100351"); //diger satýra gecip yazýyor sonraki yazýlacak kelime yine bir sonraki satýrdan baslýyor

            SysCtlDelay(30000000);

            LCD_temizle();

            LCD_sonrakisatiryaz("emrebstc");

            SysCtlDelay(30000000);

            LCD_temizle();

            LCD_sonrakisatiryaz("4.sinif");

            SysCtlDelay(30000000);

            LCD_temizle();

            LCD_yaz("LCDodev",1);

            SysCtlDelay(30000000);

            LCD_temizle();

        }


}

void clockayar(){
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
}
