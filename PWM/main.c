#include <REGX52.H>
#include "Timer0.h"
#include "Key.h"
#include "Leds.h"

sbit M = P1^0;
sbit LED = P2^0;
unsigned int Count,Compare;
void main()
{
    unsigned char K;
    unsigned char SPEED = 0;
    Timer0_Init();
    Compare = 0;
    while(1)
    {
        K = Key();
        if(K == 1)
        {
            SPEED++;
            if(SPEED > 4)
            {
                SPEED = 0;
            }

        }
        if(K == 2)
        {
            SPEED = 0;
        }
        if(SPEED == 0)
        {
            Compare = 0;
        }
        else if (SPEED == 1)
        {
            Compare = 35;
        }
        else if (SPEED == 2)
        {
            Compare = 50;
        }
        else if (SPEED == 3)
        {
            Compare = 75;
        }
        else if (SPEED == 4)
        {
            Compare = 100;
        }
        Leds(1,SPEED);
    }
}



void Timer0() interrupt 1
{
    TL0 = 0xA4;
	TH0 = 0xFF;
    Count++;
    if(Count >= 100)
    {
        Count = 0;
    }
    if(Count < Compare)
    {
        M = 1;
    }
    else if (Count >= Compare)
    {
        M = 0;
    }

}