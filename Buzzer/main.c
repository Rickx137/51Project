#include <REG52.H>
#include "Delay.h"
#include "Buzzer.h"
#include "Key.h"
#include "Leds.h"

void main()
{
    unsigned char KeyNum;
    Leds(1,10);
    while(1)
    {
        KeyNum = Key();
        if (KeyNum){Buzzer_Time(50);Leds(1,KeyNum);}

    }

}